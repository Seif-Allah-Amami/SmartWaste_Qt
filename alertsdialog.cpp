/*  alertsdialog.cpp
 *
 *  Machine Alerts & Predictions Dashboard
 *  ───────────────────────────────────────
 *
 *  Prediction algorithm (step by step)
 *  ─────────────────────────────────────────────────────────────────────────
 *  Step 1  Load every STATUS field-change ordered by changed_at ASC.
 *  Step 2  Walk the list; build consecutive periods:
 *            period[i] = { status[i], start = changedAt[i],
 *                          end = changedAt[i+1]  (or NOW for last) }
 *  Step 3  Collect every "Active" period whose NEXT status is a failure
 *            ("Under Maintenance" or "Out of Service").
 *            These are "active→failure" durations.
 *  Step 4  avg_active_duration = mean of those durations.
 *  Step 5  predicted_failure = current_active_period_start
 *                            + avg_active_duration
 *            (only computed when machine is currently Active)
 *  Step 6  Collect timestamps of every "Under Maintenance" event.
 *          avg_maintenance_interval = mean gap between consecutive events.
 *          next_maintenance = last_maintenance_time + avg_maintenance_interval
 *          If only one maintenance event → use 30-day default interval.
 *  ─────────────────────────────────────────────────────────────────────────
 */

#include "alertsdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QProgressBar>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVariant>
#include <QtMath>
#include <algorithm>
#include <QFileDialog>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QPageLayout>
#include <QPageSize>

// ─────────────────────────────────────────────────────────────────────────────
//  Theme tokens — exact copy from machinehistory.cpp
// ─────────────────────────────────────────────────────────────────────────────
namespace Th {
const QString BG        = "#0e1117";
const QString CARD      = "#161b22";
const QString CARD2     = "#1c2128";
const QString INPUT     = "#21262d";
const QString BORDER    = "#30363d";
const QString BORDER_HI = "#388bfd";
const QString T1        = "#e6edf3";
const QString T2        = "#8b949e";
const QString T3        = "#6e7681";
const QString ACCENT    = "#388bfd";
const QString SUCCESS   = "#3fb950";
const QString WARN      = "#d29922";
const QString DANGER    = "#f85149";
const QString ROW_HOVER = "#1f2937";
}

// ─────────────────────────────────────────────────────────────────────────────
//  Static helpers
// ─────────────────────────────────────────────────────────────────────────────

QColor AlertsDialog::statusColor(const QString &s)
{
    const QString l = s.toLower();
    if (l.contains("active"))      return QColor(Th::SUCCESS);
    if (l.contains("maintenance")) return QColor(Th::WARN);
    if (l.contains("service"))     return QColor(Th::DANGER);
    // deterministic fallback colour for unknown statuses
    static const QList<QColor> extra = {
        {0x58,0xa6,0xff}, {0xbc,0x8c,0xff}, {0xff,0x7b,0x72},
        {0xfb,0xa8,0x00}, {0x26,0xcd,0x4d}
    };
    int idx = qAbs(qHashBits(s.constData(),
                             static_cast<size_t>(s.size() * sizeof(QChar)),
                             0)) % extra.size();
    return extra[idx];
}

QString AlertsDialog::statusBadgeStyle(const QString &status)
{
    const QColor c  = statusColor(status);
    QColor       bg = c.darker(300);
    bg.setAlpha(180);
    return QString("color:%1; background:%2; border:1px solid %1;"
                   " border-radius:4px; padding:2px 10px;"
                   " font-size:12px; font-weight:600;")
        .arg(c.name(), bg.name());
}

QString AlertsDialog::confidenceText(Confidence c)
{
    switch (c) {
    case Confidence::High:         return "High";
    case Confidence::Medium:       return "Medium";
    case Confidence::Low:          return "Low";
    case Confidence::Insufficient: return "Insufficient data";
    }
    return "Unknown";
}

QString AlertsDialog::confidenceBadgeStyle(Confidence c)
{
    QString fg, bg;
    switch (c) {
    case Confidence::High:
        fg = Th::SUCCESS; bg = "#0d2016"; break;
    case Confidence::Medium:
        fg = Th::WARN;    bg = "#1f1800"; break;
    case Confidence::Low:
    case Confidence::Insufficient:
        fg = Th::T2;      bg = Th::INPUT; break;
    }
    return QString("color:%1; background:%2; border:1px solid %1;"
                   " border-radius:4px; padding:2px 10px;"
                   " font-size:11px; font-weight:600;")
        .arg(fg, bg);
}

// Red < 14 days  |  Yellow < 45 days  |  Green otherwise
QString AlertsDialog::urgencyDateStyle(const QDateTime &dt)
{
    if (!dt.isValid())
        return "color:" + Th::T2 + "; font-size:20px; font-weight:700;";

    const qint64 days = QDateTime::currentDateTime().daysTo(dt);
    QString fg, bg;
    if (days < 14)      { fg = Th::DANGER;  bg = "#1a0000"; }
    else if (days < 45) { fg = Th::WARN;    bg = "#1f1800"; }
    else                { fg = Th::SUCCESS; bg = "#0d2016"; }

    return QString("color:%1; background:%2; border:1px solid %1;"
                   " border-radius:6px; padding:4px 14px;"
                   " font-size:20px; font-weight:700;")
        .arg(fg, bg);
}

// ── Card / label factories ────────────────────────────────────────────────────
QFrame *AlertsDialog::makeCard(QWidget *parent)
{
    QFrame *f = new QFrame(parent);
    f->setObjectName("card");
    f->setStyleSheet(
        "QFrame#card { background:" + Th::CARD + ";"
                                                 " border:1px solid " + Th::BORDER + ";"
                       " border-radius:10px; }");
    return f;
}

QLabel *AlertsDialog::makeTitle(const QString &text, QWidget *parent)
{
    QLabel *l = new QLabel(text, parent);
    l->setStyleSheet("color:" + Th::T1 + "; font-size:13px;"
                                         " font-weight:600; letter-spacing:0.4px;");
    return l;
}

QLabel *AlertsDialog::makeFieldLabel(const QString &text, QWidget *parent)
{
    QLabel *l = new QLabel(text, parent);
    l->setStyleSheet("color:" + Th::T2 + "; font-size:11px;"
                                         " font-weight:600; letter-spacing:0.5px;");
    return l;
}

QLabel *AlertsDialog::makeValueLabel(const QString &text, QWidget *parent)
{
    QLabel *l = new QLabel(text, parent);
    l->setStyleSheet("color:" + Th::T1 + "; font-size:14px; font-weight:500;");
    return l;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor
// ─────────────────────────────────────────────────────────────────────────────
AlertsDialog::AlertsDialog(const QString &machineId,
                           const QString &machineName,
                           QWidget       *parent)
    : QDialog(parent)
    , m_machineId(machineId)
    , m_machineName(machineName)
{
    setWindowTitle("Alerts & Predictions — " + machineName);
    setMinimumSize(860, 680);
    resize(940, 760);

    // Global stylesheet — identical structure to MachineHistory
    setStyleSheet(QString(
                      "QDialog { background:%1; }"
                      "QWidget { background:transparent; color:%2;"
                      "  font-family:'Segoe UI',sans-serif; }"
                      "QScrollArea { border:none; }"
                      "QScrollBar:vertical { background:%3; width:8px; border-radius:4px; }"
                      "QScrollBar::handle:vertical { background:%4;"
                      "  border-radius:4px; min-height:30px; }"
                      "QScrollBar::add-line:vertical,"
                      "QScrollBar::sub-line:vertical { height:0; }"
                      "QPushButton { background:%5; color:#ffffff; border:none;"
                      "  border-radius:6px; padding:7px 18px;"
                      "  font-size:12px; font-weight:600; }"
                      "QPushButton:hover  { background:#1f6feb; }"
                      "QPushButton:pressed{ background:#388bfd; }"
                      "QLabel#divider { background:%4; max-height:1px; min-height:1px; }"
                      ).arg(Th::BG, Th::T1, Th::CARD2, Th::BORDER, Th::ACCENT));

    // ── Fetch fallback status from Machine table
    QString fallbackStatus;
    {
        QSqlQuery q(QSqlDatabase::database("myConnection"));
        q.prepare("SELECT STATUS FROM Machine WHERE ID_MACHINE = :id");
        q.bindValue(":id", m_machineId.toInt());
        if (q.exec() && q.next())
            fallbackStatus = q.value(0).toString();
    }

    // ── Run data pipeline
    const QList<StatusEvent> events = loadStatusHistory();
    m_result = computePredictions(events, fallbackStatus);

    // ── Build and populate UI
    buildUi();
    populateUi();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Data: load STATUS history ordered by time
// ─────────────────────────────────────────────────────────────────────────────
QList<StatusEvent> AlertsDialog::loadStatusHistory()
{
    QList<StatusEvent> events;
    QSqlQuery q(QSqlDatabase::database("myConnection"));
    q.prepare(
        "SELECT new_value, changed_at "
        "FROM machine_history "
        "WHERE machine_id = :id "
        "  AND UPPER(field_name) = 'STATUS' "
        "ORDER BY changed_at ASC");
    q.bindValue(":id", m_machineId.toInt());

    if (q.exec()) {
        while (q.next()) {
            StatusEvent e;
            e.status    = q.value(0).toString().trimmed();
            e.changedAt = q.value(1).toDateTime();
            if (!e.status.isEmpty() && e.changedAt.isValid())
                events << e;
        }
    }
    return events;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Prediction engine
// ─────────────────────────────────────────────────────────────────────────────
PredictionResult AlertsDialog::computePredictions(
    const QList<StatusEvent> &events,
    const QString             &fallbackStatus)
{
    PredictionResult r;
    r.totalEvents = events.size();

    if (events.isEmpty()) {
        r.currentStatus = fallbackStatus.isEmpty() ? "Unknown" : fallbackStatus;
        return r;
    }

    const QDateTime now = QDateTime::currentDateTime();

    // Current status = last recorded event
    r.currentStatus      = events.last().status;
    r.currentStatusStart = events.last().changedAt;

    // ── Walk consecutive periods ─────────────────────────────────────────────
    QList<qint64>    activeDursBeforeFailure;
    QList<QDateTime> maintenanceTimes;

    for (int i = 0; i < events.size(); ++i) {
        const StatusEvent &ev  = events[i];
        const QDateTime    end = (i + 1 < events.size())
                                  ? events[i + 1].changedAt : now;
        qint64 durSec = ev.changedAt.secsTo(end);
        if (durSec < 0) durSec = 0;

        // Accumulate per-status totals for insights
        r.statusDurationSec[ev.status] += durSec;
        r.statusCount[ev.status]++;

        // Active period that ended in a failure transition?
        if (ev.status.toLower().contains("active") && i + 1 < events.size()) {
            const QString nextL = events[i + 1].status.toLower();
            if (nextL.contains("maintenance") || nextL.contains("service"))
                activeDursBeforeFailure << durSec;
        }

        // Record every "Under Maintenance" timestamp
        if (ev.status.toLower().contains("maintenance"))
            maintenanceTimes << ev.changedAt;
    }

    // ── Most frequent status
    {
        int best = 0;
        for (auto it = r.statusCount.cbegin(); it != r.statusCount.cend(); ++it) {
            if (it.value() > best) {
                best = it.value();
                r.mostFrequentStatus = it.key();
            }
        }
    }

    // ── Failure prediction ────────────────────────────────────────────────────
    r.activePeriodCount = activeDursBeforeFailure.size();

    if (r.activePeriodCount > 0) {
        qint64 total = 0;
        for (qint64 d : activeDursBeforeFailure) total += d;
        r.avgActiveDurationSec = total / r.activePeriodCount;

        if      (r.activePeriodCount >= 5) r.failureConfidence = Confidence::High;
        else if (r.activePeriodCount >= 3) r.failureConfidence = Confidence::Medium;
        else                               r.failureConfidence = Confidence::Low;

        // Only project forward when machine is currently Active
        if (r.currentStatus.toLower().contains("active")) {
            r.predictedFailureDate =
                r.currentStatusStart.addSecs(r.avgActiveDurationSec);
            r.failurePredicted = true;
        }
    } else {
        r.failureConfidence = Confidence::Insufficient;
    }

    // ── Maintenance prediction ────────────────────────────────────────────────
    r.maintenanceEventCount = maintenanceTimes.size();

    if (r.maintenanceEventCount >= 2) {
        qint64 totalGap = 0;
        for (int i = 1; i < maintenanceTimes.size(); ++i)
            totalGap += maintenanceTimes[i - 1].secsTo(maintenanceTimes[i]);
        r.avgMaintenanceIntervalSec = totalGap / (maintenanceTimes.size() - 1);
        r.nextMaintenanceDate =
            maintenanceTimes.last().addSecs(r.avgMaintenanceIntervalSec);
        r.maintenancePredicted = true;

    } else if (r.maintenanceEventCount == 1) {
        // Single event — assume 30-day default interval
        r.avgMaintenanceIntervalSec = 30LL * 86400;
        r.nextMaintenanceDate =
            maintenanceTimes.last().addSecs(r.avgMaintenanceIntervalSec);
        r.maintenancePredicted = true;
    }

    return r;
}

// ─────────────────────────────────────────────────────────────────────────────
//  UI construction
// ─────────────────────────────────────────────────────────────────────────────
void AlertsDialog::buildUi()
{
    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(20, 20, 20, 16);
    root->setSpacing(16);

    root->addWidget(buildHeader());

    // Section divider
    QLabel *div = new QLabel;
    div->setObjectName("divider");
    root->addWidget(div);

    // Scrollable body
    QScrollArea *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QWidget *inner = new QWidget;
    inner->setStyleSheet("background:" + Th::BG + ";");
    QVBoxLayout *innerL = new QVBoxLayout(inner);
    innerL->setContentsMargins(0, 0, 4, 4);
    innerL->setSpacing(16);

    innerL->addWidget(buildFailureCard());
    innerL->addWidget(buildMaintenanceCard());
    innerL->addWidget(buildInsightsCard());
    innerL->addWidget(buildMethodologyCard());
    innerL->addStretch();

    scroll->setWidget(inner);
    root->addWidget(scroll, 1);

    // Footer buttons
    QHBoxLayout *footer = new QHBoxLayout;
    footer->addStretch();
    QPushButton *btnExport = new QPushButton("\u2b07  Export PDF", this);
    connect(btnExport, &QPushButton::clicked, this, &AlertsDialog::onExportPDF);
    footer->addWidget(btnExport);
    QPushButton *btnClose = new QPushButton("Close", this);
    connect(btnClose, &QPushButton::clicked, this, &QDialog::accept);
    footer->addWidget(btnClose);
    root->addLayout(footer);
}

// ── Page header ───────────────────────────────────────────────────────────────
QFrame *AlertsDialog::buildHeader()
{
    QFrame *hdr = new QFrame;
    hdr->setStyleSheet("background:transparent;");
    QHBoxLayout *hl = new QHBoxLayout(hdr);
    hl->setContentsMargins(0, 0, 0, 0);
    hl->setSpacing(12);

    QLabel *icon = new QLabel("\xF0\x9F\x94\x94");   // 🔔 UTF-8
    icon->setStyleSheet("font-size:26px;");

    QVBoxLayout *textL = new QVBoxLayout;
    textL->setSpacing(2);

    QLabel *titleL = new QLabel("Alerts & Predictions");
    titleL->setStyleSheet(
        "color:" + Th::T1 + "; font-size:20px; font-weight:700;");

    QLabel *subL = new QLabel("ID " + m_machineId + "  \xC2\xB7  " + m_machineName);
    subL->setStyleSheet("color:" + Th::T2 + "; font-size:13px;");

    textL->addWidget(titleL);
    textL->addWidget(subL);

    hl->addWidget(icon);
    hl->addLayout(textL);
    hl->addStretch();
    return hdr;
}

// ── Failure Prediction card ───────────────────────────────────────────────────
QFrame *AlertsDialog::buildFailureCard()
{
    QFrame *card = makeCard();
    QVBoxLayout *vl = new QVBoxLayout(card);
    vl->setContentsMargins(20, 16, 20, 16);
    vl->setSpacing(14);

    // Title row
    QHBoxLayout *titleRow = new QHBoxLayout;
    titleRow->setSpacing(8);
    QLabel *dot = new QLabel("\xE2\x97\x8F");   // ● red dot
    dot->setStyleSheet("font-size:10px; color:" + Th::DANGER + ";");
    titleRow->addWidget(dot);
    titleRow->addWidget(makeTitle("FAILURE PREDICTION", card));
    titleRow->addStretch();
    m_lblFailureConfBadge = new QLabel("—", card);
    titleRow->addWidget(m_lblFailureConfBadge);
    vl->addLayout(titleRow);

    // Thin divider inside card
    QLabel *sep = new QLabel(card);
    sep->setObjectName("divider");
    vl->addWidget(sep);

    // Content grid
    QGridLayout *grid = new QGridLayout;
    grid->setHorizontalSpacing(32);
    grid->setVerticalSpacing(6);
    grid->setColumnStretch(3, 1);

    // Column 0 – Predicted failure date
    grid->addWidget(makeFieldLabel("PREDICTED FAILURE DATE", card), 0, 0);
    m_lblFailureDate = new QLabel("—", card);
    m_lblFailureDate->setWordWrap(true);
    grid->addWidget(m_lblFailureDate, 1, 0, 1, 2);  // spans 2 cols

    // Column 2 – Confidence
    grid->addWidget(makeFieldLabel("CONFIDENCE", card),   0, 2);
    m_lblAvgActive = makeValueLabel("—", card);
    grid->addWidget(m_lblAvgActive, 1, 2);

    // Row 2
    grid->addWidget(makeFieldLabel("DATA POINTS",   card), 2, 0);
    grid->addWidget(makeFieldLabel("CURRENT STATUS",card), 2, 2);

    m_lblDataPoints   = makeValueLabel("—", card);
    m_lblCurrentStatus = new QLabel("—", card);

    grid->addWidget(m_lblDataPoints,    3, 0);
    grid->addWidget(m_lblCurrentStatus, 3, 2);

    vl->addLayout(grid);

    QLabel *hint = new QLabel(
        "Based on average duration of Active periods before a failure transition.",
        card);
    hint->setStyleSheet(
        "color:" + Th::T3 + "; font-size:11px; font-style:italic;");
    hint->setWordWrap(true);
    vl->addWidget(hint);

    return card;
}

// ── Maintenance Reminder card ─────────────────────────────────────────────────
QFrame *AlertsDialog::buildMaintenanceCard()
{
    QFrame *card = makeCard();
    QVBoxLayout *vl = new QVBoxLayout(card);
    vl->setContentsMargins(20, 16, 20, 16);
    vl->setSpacing(14);

    QHBoxLayout *titleRow = new QHBoxLayout;
    titleRow->setSpacing(8);
    QLabel *dot = new QLabel("\xE2\x97\x8F");   // ● yellow dot
    dot->setStyleSheet("font-size:10px; color:" + Th::WARN + ";");
    titleRow->addWidget(dot);
    titleRow->addWidget(makeTitle("MAINTENANCE REMINDER", card));
    titleRow->addStretch();
    vl->addLayout(titleRow);

    QLabel *sep = new QLabel(card);
    sep->setObjectName("divider");
    vl->addWidget(sep);

    QGridLayout *grid = new QGridLayout;
    grid->setHorizontalSpacing(32);
    grid->setVerticalSpacing(6);
    grid->setColumnStretch(3, 1);

    grid->addWidget(makeFieldLabel("NEXT MAINTENANCE RECOMMENDED", card), 0, 0, 1, 2);
    m_lblMaintenanceDate = new QLabel("—", card);
    m_lblMaintenanceDate->setWordWrap(true);
    grid->addWidget(m_lblMaintenanceDate, 1, 0, 1, 2);

    grid->addWidget(makeFieldLabel("EVENTS RECORDED", card), 0, 2);
    grid->addWidget(makeFieldLabel("AVG INTERVAL",    card), 2, 0);

    m_lblMaintenanceCount    = makeValueLabel("—", card);
    m_lblMaintenanceInterval = makeValueLabel("—", card);
    grid->addWidget(m_lblMaintenanceCount,    1, 2);
    grid->addWidget(m_lblMaintenanceInterval, 3, 0);

    vl->addLayout(grid);

    QLabel *hint = new QLabel(
        "Average gap between 'Under Maintenance' events. "
        "If fewer than 2 events exist, a 30-day default is used.",
        card);
    hint->setStyleSheet(
        "color:" + Th::T3 + "; font-size:11px; font-style:italic;");
    hint->setWordWrap(true);
    vl->addWidget(hint);

    return card;
}

// ── Status Insights card ──────────────────────────────────────────────────────
QFrame *AlertsDialog::buildInsightsCard()
{
    QFrame *card = makeCard();
    QVBoxLayout *vl = new QVBoxLayout(card);
    vl->setContentsMargins(20, 16, 20, 16);
    vl->setSpacing(14);

    QHBoxLayout *titleRow = new QHBoxLayout;
    titleRow->setSpacing(8);
    QLabel *dot = new QLabel("\xE2\x97\x8F");   // ● green dot
    dot->setStyleSheet("font-size:10px; color:" + Th::SUCCESS + ";");
    titleRow->addWidget(dot);
    titleRow->addWidget(makeTitle("STATUS INSIGHTS", card));
    titleRow->addStretch();
    vl->addLayout(titleRow);

    QLabel *sep = new QLabel(card);
    sep->setObjectName("divider");
    vl->addWidget(sep);

    // Populated dynamically in populateUi()
    m_insightsContainer = new QWidget(card);
    m_insightsContainer->setStyleSheet("background:transparent;");
    QVBoxLayout *cl = new QVBoxLayout(m_insightsContainer);
    cl->setContentsMargins(0, 0, 0, 0);
    cl->setSpacing(8);

    QLabel *placeholder = new QLabel("Loading\xE2\x80\xA6", m_insightsContainer);
    placeholder->setStyleSheet("color:" + Th::T3 + ";");
    cl->addWidget(placeholder);

    vl->addWidget(m_insightsContainer);
    return card;
}

// ── Methodology card ──────────────────────────────────────────────────────────
QFrame *AlertsDialog::buildMethodologyCard()
{
    QFrame *card = new QFrame;
    card->setObjectName("card");
    card->setStyleSheet(
        "QFrame#card { background:" + Th::CARD2 + ";"
                                                  " border:1px solid " + Th::BORDER + ";"
                       " border-radius:10px; }");

    QVBoxLayout *vl = new QVBoxLayout(card);
    vl->setContentsMargins(20, 14, 20, 14);
    vl->setSpacing(6);

    QLabel *title = new QLabel(
        "\xE2\x84\xB9  How predictions are calculated", card);
    title->setStyleSheet(
        "color:" + Th::T2 + "; font-size:12px; font-weight:600;");
    vl->addWidget(title);

    const QStringList lines = {
        "\xE2\x80\xA2  Failure: average duration of Active periods that ended in "
        "a failure transition (Maintenance or Out of Service).",
        "\xE2\x80\xA2  Confidence: High \xE2\x89\xA5 5 data points | "
        "Medium 3\xE2\x80\x934 | Low 1\xE2\x80\x932 | Insufficient 0.",
        "\xE2\x80\xA2  Maintenance: average gap between recorded "
        "'Under Maintenance' events.",
        "\xE2\x80\xA2  If fewer than 2 maintenance events exist, "
        "a 30-day default interval is assumed.",
        "\xE2\x80\xA2  Urgency colour: "
        "\xF0\x9F\x94\xB4 red < 14 days | "
        "\xF0\x9F\x9F\xA1 yellow < 45 days | "
        "\xF0\x9F\x9F\xA2 green \xE2\x89\xA5 45 days.",
        "\xE2\x80\xA2  All timestamps from machine_history.changed_at."
    };

    for (const QString &line : lines) {
        QLabel *l = new QLabel(line, card);
        l->setStyleSheet("color:" + Th::T3 + "; font-size:11px;");
        l->setWordWrap(true);
        vl->addWidget(l);
    }
    return card;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Populate all UI widgets with computed data
// ─────────────────────────────────────────────────────────────────────────────
static QString fmtDur(qint64 sec)
{
    if (sec <= 0) return "0s";
    const qint64 d = sec / 86400, h = (sec % 86400) / 3600,
        m = (sec % 3600)  / 60;
    QStringList p;
    if (d) p << QString::number(d) + "d";
    if (h) p << QString::number(h) + "h";
    if (m) p << QString::number(m) + "m";
    if (p.isEmpty()) p << QString::number(sec % 60) + "s";
    return p.join(" ");
}

void AlertsDialog::populateUi()
{
    const PredictionResult &r = m_result;

    // ── Failure card ─────────────────────────────────────────────────────────
    m_lblFailureConfBadge->setText(confidenceText(r.failureConfidence));
    m_lblFailureConfBadge->setStyleSheet(confidenceBadgeStyle(r.failureConfidence));

    if (r.failurePredicted && r.predictedFailureDate.isValid()) {
        const qint64 days = QDateTime::currentDateTime()
        .daysTo(r.predictedFailureDate);
        const QString suffix = (days >= 0)
                                   ? QString("  (%1 days from now)").arg(days)
                                   : QString("  (%1 days overdue)").arg(qAbs(days));
        m_lblFailureDate->setText(
            r.predictedFailureDate.toString("yyyy-MM-dd") + suffix);
        m_lblFailureDate->setStyleSheet(urgencyDateStyle(r.predictedFailureDate));
    } else {
        m_lblFailureDate->setText("Not enough data for prediction");
        m_lblFailureDate->setStyleSheet(
            "color:" + Th::T2 + "; font-size:14px;");
    }

    m_lblAvgActive->setText(
        r.activePeriodCount > 0
            ? "avg " + fmtDur(r.avgActiveDurationSec) + " active"
            : "\xE2\x80\x94");

    m_lblDataPoints->setText(
        r.activePeriodCount > 0
            ? QString::number(r.activePeriodCount) + " transition(s)"
            : "No active\xE2\x86\x92failure transitions");

    m_lblCurrentStatus->setText(r.currentStatus);
    m_lblCurrentStatus->setStyleSheet(statusBadgeStyle(r.currentStatus));

    // ── Maintenance card ──────────────────────────────────────────────────────
    if (r.maintenancePredicted && r.nextMaintenanceDate.isValid()) {
        const qint64 days = QDateTime::currentDateTime()
        .daysTo(r.nextMaintenanceDate);
        const QString suffix = (days >= 0)
                                   ? QString("  (%1 days from now)").arg(days)
                                   : QString("  (%1 days overdue)").arg(qAbs(days));
        m_lblMaintenanceDate->setText(
            r.nextMaintenanceDate.toString("yyyy-MM-dd") + suffix);
        m_lblMaintenanceDate->setStyleSheet(
            urgencyDateStyle(r.nextMaintenanceDate));
    } else {
        m_lblMaintenanceDate->setText("No maintenance history recorded");
        m_lblMaintenanceDate->setStyleSheet(
            "color:" + Th::T2 + "; font-size:14px;");
    }

    m_lblMaintenanceCount->setText(
        r.maintenanceEventCount > 0
            ? QString::number(r.maintenanceEventCount) + " event(s)"
            : "None recorded");

    m_lblMaintenanceInterval->setText(
        r.avgMaintenanceIntervalSec > 0
            ? fmtDur(r.avgMaintenanceIntervalSec)
            : (r.maintenanceEventCount == 1 ? "30d (default)" : "\xE2\x80\x94"));

    // ── Status Insights ───────────────────────────────────────────────────────
    // Clear placeholder, then build one row per status
    QLayout *cl = m_insightsContainer->layout();
    while (QLayoutItem *item = cl->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    if (r.totalEvents == 0) {
        QLabel *noData = new QLabel(
            "No status history available.", m_insightsContainer);
        noData->setStyleSheet(
            "color:" + Th::T2 + "; font-size:13px; font-style:italic;");
        cl->addWidget(noData);
        return;
    }

    // Column header row
    {
        QWidget *hdrRow = new QWidget(m_insightsContainer);
        hdrRow->setStyleSheet("background:transparent;");
        QHBoxLayout *hh = new QHBoxLayout(hdrRow);
        hh->setContentsMargins(0, 0, 0, 4);
        hh->setSpacing(0);

        auto col = [&](const QString &t, int stretch) {
            QLabel *l = new QLabel(t, hdrRow);
            l->setStyleSheet(
                "color:" + Th::T2 + "; font-size:11px;"
                                    " font-weight:600; letter-spacing:0.4px;");
            hh->addWidget(l, stretch);
        };
        col("STATUS",         3);
        col("EVENTS",         1);
        col("TOTAL DURATION", 2);
        col("TIME SHARE",     3);
        cl->addWidget(hdrRow);
    }

    // Compute total duration for percentage bars
    qint64 totalDurSec = 0;
    for (auto it = r.statusDurationSec.cbegin();
         it != r.statusDurationSec.cend(); ++it)
        totalDurSec += it.value();

    // Sort statuses by duration descending
    QList<QPair<QString, qint64>> sorted;
    for (auto it = r.statusDurationSec.cbegin();
         it != r.statusDurationSec.cend(); ++it)
        sorted << qMakePair(it.key(), it.value());
    std::sort(sorted.begin(), sorted.end(),
              [](const QPair<QString,qint64> &a,
                 const QPair<QString,qint64> &b){ return a.second > b.second; });

    for (const auto &pair : sorted) {
        const QString &status = pair.first;
        const qint64   dur    = pair.second;
        const int      cnt    = r.statusCount.value(status, 0);
        const double   pct    = (totalDurSec > 0)
                               ? (100.0 * dur / totalDurSec) : 0.0;

        QWidget *row = new QWidget(m_insightsContainer);
        row->setStyleSheet(
            "background:" + Th::CARD2 + ";"
                                        " border-radius:6px;"
                                        " border:1px solid " + Th::BORDER + ";");
        QHBoxLayout *rl = new QHBoxLayout(row);
        rl->setContentsMargins(12, 8, 12, 8);
        rl->setSpacing(0);

        // Status badge
        QLabel *badge = new QLabel(status, row);
        badge->setStyleSheet(statusBadgeStyle(status));
        rl->addWidget(badge, 3);

        // Event count
        QLabel *cntL = new QLabel(QString::number(cnt), row);
        cntL->setStyleSheet("color:" + Th::T1 + "; font-size:13px;");
        rl->addWidget(cntL, 1);

        // Duration
        QLabel *durL = new QLabel(fmtDur(dur), row);
        durL->setStyleSheet("color:" + Th::T1 + "; font-size:13px;");
        rl->addWidget(durL, 2);

        // Progress bar + percentage
        QWidget *barCell = new QWidget(row);
        barCell->setStyleSheet("background:transparent;");
        QHBoxLayout *bl = new QHBoxLayout(barCell);
        bl->setContentsMargins(0, 0, 0, 0);
        bl->setSpacing(8);

        QProgressBar *bar = new QProgressBar(barCell);
        bar->setRange(0, 100);
        bar->setValue(static_cast<int>(pct));
        bar->setTextVisible(false);
        bar->setFixedHeight(8);
        const QColor barCol = statusColor(status);
        bar->setStyleSheet(
            QString("QProgressBar { background:%1; border-radius:4px; border:none; }"
                    "QProgressBar::chunk { background:%2; border-radius:4px; }")
                .arg(Th::BORDER, barCol.name()));
        bl->addWidget(bar, 1);

        QLabel *pctL = new QLabel(
            QString::number(pct, 'f', 1) + "%", barCell);
        pctL->setStyleSheet("color:" + Th::T2 + "; font-size:11px;");
        pctL->setFixedWidth(42);
        bl->addWidget(pctL);

        rl->addWidget(barCell, 3);
        cl->addWidget(row);
    }

    // Summary line
    if (!r.mostFrequentStatus.isEmpty()) {
        QLabel *sumL = new QLabel(
            "Most frequent: " + r.mostFrequentStatus
                + "  \xC2\xB7  Total events analysed: "
                + QString::number(r.totalEvents),
            m_insightsContainer);
        sumL->setStyleSheet(
            "color:" + Th::T2 + "; font-size:11px; font-style:italic;");
        cl->addWidget(sumL);
    }
}
// ─────────────────────────────────────────────────────────────────────────────
//  PDF Export  (mirrors MachineHistory::writePDF style)
// ─────────────────────────────────────────────────────────────────────────────

void AlertsDialog::onExportPDF()
{
    const QString path = QFileDialog::getSaveFileName(
        this, "Export Alerts PDF",
        "machine_" + m_machineId + "_alerts.pdf",
        "PDF Files (*.pdf)");
    if (path.isEmpty()) return;
    writePDF(path);
}

void AlertsDialog::writePDF(const QString &path)
{
    QPdfWriter writer(path);
    writer.setPageSize(QPageSize::A4);
    writer.setPageMargins(QMarginsF(18, 18, 18, 18), QPageLayout::Millimeter);
    writer.setResolution(150);

    QPainter p(&writer);
    if (!p.isActive()) {
        QMessageBox::critical(this, "Export failed", "Could not open file for writing.");
        return;
    }

    const int W  = writer.width();
    const int lh = 32;   // line height units
    int y = 0;

    // ── Helpers ───────────────────────────────────────────────────────────
    auto newPageIfNeeded = [&](int neededH) {
        if (y + neededH > writer.height() - 60) {
            writer.newPage();
            y = 0;
        }
    };

    auto hRule = [&]() {
        p.setPen(QPen(QColor("#cccccc"), 1));
        p.drawLine(0, y, W, y);
        p.setPen(Qt::black);
        y += lh / 2;
    };

    auto pdfRow = [&](const QString &label, const QString &val) {
        newPageIfNeeded(lh);
        p.setFont(QFont("Arial", 10));
        p.setPen(QColor("#666666"));
        p.drawText(QRect(0, y, 220, lh), Qt::AlignRight | Qt::AlignVCenter, label);
        p.setPen(Qt::black);
        p.drawText(QRect(230, y, W - 230, lh), Qt::AlignLeft | Qt::AlignVCenter, val);
        y += lh;
    };

    // local duration formatter (mirrors fmtDur in populateUi)
    auto fmtDur = [](qint64 sec) -> QString {
        if (sec <= 0) return "0s";
        const qint64 d = sec / 86400, h = (sec % 86400) / 3600,
            m = (sec % 3600)  / 60;
        QStringList parts;
        if (d) parts << QString::number(d) + "d";
        if (h) parts << QString::number(h) + "h";
        if (m) parts << QString::number(m) + "m";
        if (parts.isEmpty()) parts << QString::number(sec % 60) + "s";
        return parts.join(" ");
    };

    const PredictionResult &r = m_result;

    // ── Title block ────────────────────────────────────────────────────────
    p.setFont(QFont("Arial", 18, QFont::Bold));
    p.setPen(QColor("#111111"));
    p.drawText(QRect(0, y, W, 50), Qt::AlignLeft | Qt::AlignVCenter,
               "Machine Alerts & Predictions Report");
    y += 54;

    p.setFont(QFont("Arial", 10));
    p.setPen(QColor("#555555"));
    p.drawText(0, y, "Machine: " + m_machineName
                         + "   |   ID: " + m_machineId
                         + "   |   Exported: "
                         + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"));
    y += lh;
    hRule();

    // ── Failure Prediction ─────────────────────────────────────────────────
    p.setFont(QFont("Arial", 12, QFont::Bold));
    p.setPen(QColor("#111111"));
    newPageIfNeeded(lh * 2);
    p.drawText(0, y, "Failure Prediction");
    y += lh;
    hRule();

    pdfRow("Current Status:", r.currentStatus.isEmpty() ? "Unknown" : r.currentStatus);
    pdfRow("Confidence:",     confidenceText(r.failureConfidence));

    if (r.failurePredicted && r.predictedFailureDate.isValid()) {
        const qint64 days = QDateTime::currentDateTime().daysTo(r.predictedFailureDate);
        const QString suffix = (days >= 0)
                                   ? QString("  (%1 days from now)").arg(days)
                                   : QString("  (%1 days overdue)").arg(qAbs(days));
        pdfRow("Predicted Failure Date:",
               r.predictedFailureDate.toString("yyyy-MM-dd") + suffix);
    } else {
        pdfRow("Predicted Failure Date:", "Not enough data for prediction");
    }

    if (r.activePeriodCount > 0) {
        pdfRow("Avg Active Duration:", fmtDur(r.avgActiveDurationSec));
        pdfRow("Data Points:",         QString::number(r.activePeriodCount) + " transition(s)");
    } else {
        pdfRow("Data Points:", "No active \u2192 failure transitions recorded");
    }

    y += lh / 2;

    // ── Maintenance Reminder ───────────────────────────────────────────────
    newPageIfNeeded(lh * 3);
    p.setFont(QFont("Arial", 12, QFont::Bold));
    p.setPen(QColor("#111111"));
    p.drawText(0, y, "Maintenance Reminder");
    y += lh;
    hRule();

    if (r.maintenancePredicted && r.nextMaintenanceDate.isValid()) {
        const qint64 days = QDateTime::currentDateTime().daysTo(r.nextMaintenanceDate);
        const QString suffix = (days >= 0)
                                   ? QString("  (%1 days from now)").arg(days)
                                   : QString("  (%1 days overdue)").arg(qAbs(days));
        pdfRow("Next Recommended:",
               r.nextMaintenanceDate.toString("yyyy-MM-dd") + suffix);
    } else {
        pdfRow("Next Recommended:", "No maintenance history recorded");
    }

    pdfRow("Events Recorded:", r.maintenanceEventCount > 0
                                   ? QString::number(r.maintenanceEventCount) + " event(s)"
                                   : "None recorded");

    if (r.avgMaintenanceIntervalSec > 0) {
        pdfRow("Avg Interval:", fmtDur(r.avgMaintenanceIntervalSec)
               + (r.maintenanceEventCount == 1 ? "  (30-day default)" : ""));
    }

    y += lh / 2;

    // ── Status Insights ────────────────────────────────────────────────────
    newPageIfNeeded(lh * 4);
    p.setFont(QFont("Arial", 12, QFont::Bold));
    p.setPen(QColor("#111111"));
    p.drawText(0, y, "Status Insights");
    y += lh;
    hRule();

    if (r.totalEvents == 0) {
        p.setFont(QFont("Arial", 10));
        p.setPen(QColor("#999999"));
        p.drawText(0, y, "No status history available.");
        y += lh;
    } else {
        // Column widths: Status | Events | Total Duration | Time Share
        const int cw[4] = { 240, 80, 180, W - 500 };
        const QString hdrs[4] = { "Status", "Events", "Total Duration", "Time Share" };

        // Header row
        p.setFont(QFont("Arial", 9, QFont::Bold));
        p.fillRect(QRect(0, y, W, lh), QColor("#f0f0f0"));
        int x = 0;
        for (int c = 0; c < 4; ++c) {
            p.setPen(QColor("#333333"));
            p.drawText(QRect(x + 4, y, cw[c] - 8, lh),
                       Qt::AlignLeft | Qt::AlignVCenter, hdrs[c]);
            x += cw[c];
        }
        y += lh;
        hRule();

        // Compute total duration for percentages
        qint64 totalDurSec = 0;
        for (auto it = r.statusDurationSec.cbegin();
             it != r.statusDurationSec.cend(); ++it)
            totalDurSec += it.value();

        // Sort by duration descending
        QList<QPair<QString, qint64>> sorted;
        for (auto it = r.statusDurationSec.cbegin();
             it != r.statusDurationSec.cend(); ++it)
            sorted << qMakePair(it.key(), it.value());
        std::sort(sorted.begin(), sorted.end(),
                  [](const QPair<QString,qint64> &a,
                     const QPair<QString,qint64> &b){ return a.second > b.second; });

        p.setFont(QFont("Arial", 9));
        bool alt = false;
        for (const auto &pair : sorted) {
            newPageIfNeeded(lh);
            const double pct = (totalDurSec > 0)
                                   ? (100.0 * pair.second / totalDurSec) : 0.0;

            if (alt) p.fillRect(QRect(0, y, W, lh), QColor("#f9f9f9"));
            alt = !alt;

            const QString cols[4] = {
                pair.first,
                QString::number(r.statusCount.value(pair.first, 0)),
                fmtDur(pair.second),
                QString::number(pct, 'f', 1) + "%"
            };
            x = 0;
            for (int c = 0; c < 4; ++c) {
                p.setPen(c == 0 ? QColor("#1a6dba") : Qt::black);
                p.drawText(QRect(x + 4, y, cw[c] - 8, lh),
                           Qt::AlignLeft | Qt::AlignVCenter, cols[c]);
                x += cw[c];
            }
            y += lh;
        }

        // Summary line
        if (!r.mostFrequentStatus.isEmpty()) {
            y += lh / 2;
            newPageIfNeeded(lh);
            p.setFont(QFont("Arial", 9));
            p.setPen(QColor("#555555"));
            p.drawText(0, y, "Most frequent status: " + r.mostFrequentStatus
                                 + "   |   Total events analysed: "
                                 + QString::number(r.totalEvents));
            y += lh;
        }
    }

    p.end();
    QMessageBox::information(this, "PDF Exported",
                             "Report saved successfully:\n" + path);
}