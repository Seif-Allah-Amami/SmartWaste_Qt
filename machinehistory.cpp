/*  machinehistory.cpp
 *
 *  Machine History dialog — dashboard-grade UI.
 *
 *  DB tables used
 *  ──────────────
 *    Machine        : ID_MACHINE, FULL_NAME, TYPE, LOCATION,
 *                     PURCHASE_DATE, STATUS
 *    machine_history: history_id, machine_id (FK→ID_MACHINE),
 *                     changed_at TIMESTAMP, field_name, old_value, new_value
 *
 *  Changes from previous version
 *  ──────────────────────────────
 *    • "Creation Date" replaced with "Purchase Date" (from Machine.PURCHASE_DATE)
 *    • MIN(changed_at) removed; purchase date comes from Machine table directly
 *    • CSV export removed; only PDF export remains
 *    • onExportCSV() slot and writeCSV() removed
 *    • MachineInfo.creationDate → MachineInfo.purchaseDate
 */

#include "machinehistory.h"

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QToolTip>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPageLayout>
#include <QPageSize>
#include <QFontMetrics>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVariant>
#include <QApplication>

// ─────────────────────────────────────────────────────────────────────────────
//  Theme tokens — mirrors the main window's dark dashboard palette
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
//  Status colour helper
// ─────────────────────────────────────────────────────────────────────────────
static QColor statusColor(const QString &s)
{
    QString l = s.toLower();
    if (l.contains("active"))      return QColor(Th::SUCCESS);
    if (l.contains("maintenance")) return QColor(Th::WARN);
    if (l.contains("service"))     return QColor(Th::DANGER);
    static const QList<QColor> extra = {
        {0x58,0xa6,0xff}, {0xbc,0x8c,0xff}, {0xff,0x7b,0x72},
        {0xfb,0xa8,0x00}, {0x26,0xcd,0x4d}
    };
    int idx = qAbs(qHashBits(s.constData(),
                             static_cast<size_t>(s.size() * sizeof(QChar)),
                             0)) % extra.size();
    return extra[idx];
}

// ─────────────────────────────────────────────────────────────────────────────
//  Utility formatters
// ─────────────────────────────────────────────────────────────────────────────
static QString fmtDuration(qint64 sec)
{
    if (sec <= 0) return "0s";
    qint64 d = sec / 86400, h = (sec % 86400) / 3600,
        m = (sec % 3600) / 60;
    QStringList parts;
    if (d) parts << QString::number(d) + "d";
    if (h) parts << QString::number(h) + "h";
    if (m) parts << QString::number(m) + "m";
    if (parts.isEmpty()) parts << QString::number(sec % 60) + "s";
    return parts.join(" ");
}

// ─────────────────────────────────────────────────────────────────────────────
//  Style helpers
// ─────────────────────────────────────────────────────────────────────────────
QFrame *MachineHistory::makeCard(QWidget *parent)
{
    QFrame *f = new QFrame(parent);
    f->setObjectName("card");
    f->setStyleSheet(
        "QFrame#card { background:" + Th::CARD + ";"
                                                 " border:1px solid " + Th::BORDER + ";"
                       " border-radius:10px; }");
    return f;
}

QLabel *MachineHistory::makeTitle(const QString &text, QWidget *parent)
{
    QLabel *l = new QLabel(text, parent);
    l->setStyleSheet(
        "color:" + Th::T1 + ";"
                            "font-size:13px;"
                            "font-weight:600;"
                            "letter-spacing:0.4px;");
    return l;
}

QLabel *MachineHistory::makeSummaryValue(const QString &init, QWidget *parent)
{
    QLabel *l = new QLabel(init, parent);
    l->setStyleSheet(
        "color:" + Th::T1 + ";"
                            "font-size:14px;"
                            "font-weight:500;");
    return l;
}

QString MachineHistory::badgeStyle(const QString &status)
{
    QColor c  = statusColor(status);
    QColor bg = c.darker(300);
    bg.setAlpha(180);
    return QString(
               "color:%1;"
               "background:%2;"
               "border:1px solid %1;"
               "border-radius:4px;"
               "padding:2px 10px;"
               "font-size:12px;"
               "font-weight:600;")
        .arg(c.name(), bg.name());
}

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor
// ─────────────────────────────────────────────────────────────────────────────
MachineHistory::MachineHistory(const QString &machineId,
                               const QString &machineName,
                               QWidget       *parent)
    : QDialog(parent)
    , m_machineId(machineId)
    , m_machineName(machineName)
{
    setWindowTitle("Machine History — " + machineName);
    setMinimumSize(1000, 820);
    resize(1100, 900);

    // Global stylesheet — same dark-dashboard design language as main window
    setStyleSheet(QString(
                      "QDialog { background:%1; }"
                      "QWidget { background:transparent; color:%2; font-family:'Segoe UI',sans-serif; }"
                      "QScrollArea { border:none; }"
                      "QScrollBar:vertical { background:%3; width:8px; border-radius:4px; }"
                      "QScrollBar::handle:vertical { background:%4; border-radius:4px; min-height:30px; }"
                      "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height:0; }"
                      "QScrollBar:horizontal { background:%3; height:8px; border-radius:4px; }"
                      "QScrollBar::handle:horizontal { background:%4; border-radius:4px; min-width:30px; }"
                      "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal { width:0; }"
                      "QLineEdit, QDateTimeEdit, QComboBox {"
                      "  background:%5; color:%2; border:1px solid %4;"
                      "  border-radius:6px; padding:5px 10px; font-size:12px; }"
                      "QLineEdit:focus, QDateTimeEdit:focus, QComboBox:focus {"
                      "  border-color:%6; }"
                      "QComboBox::drop-down { border:none; padding-right:8px; }"
                      "QComboBox QAbstractItemView { background:%5; color:%2; border:1px solid %4; }"
                      "QPushButton {"
                      "  background:%7; color:#ffffff; border:none;"
                      "  border-radius:6px; padding:7px 18px;"
                      "  font-size:12px; font-weight:600; }"
                      "QPushButton:hover { background:#1f6feb; }"
                      "QPushButton:pressed { background:#388bfd; }"
                      "QPushButton#btnSecondary {"
                      "  background:transparent; color:%8; border:1px solid %4; }"
                      "QPushButton#btnSecondary:hover { border-color:%6; color:%2; }"
                      "QTableWidget {"
                      "  background:%3; color:%2; border:none;"
                      "  gridline-color:%4; font-size:13px; }"
                      "QTableWidget::item { padding:10px 12px; border-bottom:1px solid %4; }"
                      "QTableWidget::item:selected { background:%9; }"
                      "QHeaderView::section {"
                      "  background:%5; color:%8; border:none;"
                      "  border-bottom:2px solid %4; padding:10px 12px;"
                      "  font-size:12px; font-weight:600; letter-spacing:0.5px; }"
                      "QHeaderView::section:first { border-top-left-radius:8px; }"
                      "QHeaderView::section:last  { border-top-right-radius:8px; }"
                      "QLabel#sectionDivider { background:%4; max-height:1px; min-height:1px; }"
                      )
                      .arg(Th::BG,        // 1
                           Th::T1,        // 2
                           Th::CARD2,     // 3
                           Th::BORDER,    // 4
                           Th::INPUT,     // 5
                           Th::BORDER_HI, // 6
                           Th::ACCENT,    // 7
                           Th::T2,        // 8
                           Th::ROW_HOVER  // 9
                           ));

    buildUi();
    loadAll();
}

// ─────────────────────────────────────────────────────────────────────────────
//  UI construction
// ─────────────────────────────────────────────────────────────────────────────
void MachineHistory::buildUi()
{
    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(20, 20, 20, 16);
    root->setSpacing(16);

    // Page header
    QWidget *hdr = new QWidget;
    QHBoxLayout *hdrL = new QHBoxLayout(hdr);
    hdrL->setContentsMargins(0,0,0,0);
    hdrL->setSpacing(12);

    QLabel *icon = new QLabel("⏱");
    icon->setStyleSheet("font-size:26px; color:" + Th::ACCENT + ";");

    QVBoxLayout *hdrText = new QVBoxLayout;
    hdrText->setSpacing(2);
    QLabel *titleL = new QLabel("Machine History");
    titleL->setStyleSheet("color:" + Th::T1 + "; font-size:20px; font-weight:700;");
    QLabel *subtitleL = new QLabel("ID " + m_machineId + "  ·  " + m_machineName);
    subtitleL->setStyleSheet("color:" + Th::T2 + "; font-size:13px;");
    hdrText->addWidget(titleL);
    hdrText->addWidget(subtitleL);

    hdrL->addWidget(icon);
    hdrL->addLayout(hdrText);
    hdrL->addStretch();
    root->addWidget(hdr);

    // Section divider
    QLabel *div0 = new QLabel;
    div0->setObjectName("sectionDivider");
    root->addWidget(div0);

    // Scrollable content area
    QScrollArea *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QWidget *inner = new QWidget;
    inner->setStyleSheet("background:" + Th::BG + ";");
    QVBoxLayout *innerL = new QVBoxLayout(inner);
    innerL->setContentsMargins(0, 0, 4, 4);
    innerL->setSpacing(16);

    innerL->addWidget(buildSummary());
    innerL->addWidget(buildTimeline());
    innerL->addWidget(buildFilters());
    innerL->addWidget(buildTable(), 1);
    innerL->addWidget(buildExportBar());

    scroll->setWidget(inner);
    root->addWidget(scroll, 1);
}

// ── Summary card ──────────────────────────────────────────────────────────────
QFrame *MachineHistory::buildSummary()
{
    QFrame *card = makeCard();
    QVBoxLayout *vl = new QVBoxLayout(card);
    vl->setContentsMargins(20, 16, 20, 16);
    vl->setSpacing(16);

    // Heading row
    QHBoxLayout *headRow = new QHBoxLayout;
    headRow->addWidget(makeTitle("SUMMARY", card));
    headRow->addStretch();
    m_badgeFreq = new QLabel;
    m_badgeFreq->setStyleSheet("color:" + Th::T2 + "; font-size:11px; font-style:italic;");
    headRow->addWidget(m_badgeFreq);
    vl->addLayout(headRow);

    // 5-column info grid
    QGridLayout *grid = new QGridLayout;
    grid->setHorizontalSpacing(32);
    grid->setVerticalSpacing(6);

    auto addField = [&](int col, const QString &label, QLabel *&valOut) {
        QLabel *lbl = new QLabel(label, card);
        lbl->setStyleSheet("color:" + Th::T2 + "; font-size:11px;"
                                               " font-weight:600; letter-spacing:0.5px;");
        grid->addWidget(lbl, 0, col);
        valOut = makeSummaryValue("—", card);
        grid->addWidget(valOut, 1, col);
    };

    addField(0, "MACHINE ID",    m_lblId);
    addField(1, "PURCHASE DATE", m_lblPurchaseDate);   // ← changed from CREATION DATE
    addField(2, "LAST MODIFIED", m_lblModified);
    addField(3, "TOTAL CHANGES", m_lblChanges);

    // Current status badge column
    QLabel *statusLbl = new QLabel("CURRENT STATUS", card);
    statusLbl->setStyleSheet("color:" + Th::T2 + "; font-size:11px;"
                                                 " font-weight:600; letter-spacing:0.5px;");
    grid->addWidget(statusLbl, 0, 4);
    m_lblStatus = new QLabel("—", card);
    grid->addWidget(m_lblStatus, 1, 4);

    grid->setColumnStretch(5, 1);
    vl->addLayout(grid);
    return card;
}

// ── Timeline card ─────────────────────────────────────────────────────────────
QFrame *MachineHistory::buildTimeline()
{
    QFrame *card = makeCard();
    QVBoxLayout *vl = new QVBoxLayout(card);
    vl->setContentsMargins(20, 16, 20, 16);
    vl->setSpacing(12);

    QHBoxLayout *headRow = new QHBoxLayout;
    headRow->addWidget(makeTitle("STATUS TIMELINE", card));
    headRow->addStretch();
    QLabel *hint = new QLabel("Hover segments for exact timestamps", card);
    hint->setStyleSheet("color:" + Th::T3 + "; font-size:11px;");
    headRow->addWidget(hint);
    vl->addLayout(headRow);

    m_tlNoData = new QLabel(
        "No status changes recorded — showing current machine status only.",
        card);
    m_tlNoData->setStyleSheet(
        "color:" + Th::T2 + "; font-size:12px; font-style:italic;"
                            " padding:12px; background:" + Th::INPUT + ";"
                      " border-radius:6px; border:1px dashed " + Th::BORDER + ";");
    m_tlNoData->setAlignment(Qt::AlignCenter);
    m_tlNoData->hide();
    vl->addWidget(m_tlNoData);

    m_timeline = new TimelineBar(card);
    vl->addWidget(m_timeline);

    return card;
}

// ── Filters card ──────────────────────────────────────────────────────────────
QFrame *MachineHistory::buildFilters()
{
    QFrame *card = makeCard();
    QVBoxLayout *vl = new QVBoxLayout(card);
    vl->setContentsMargins(20, 16, 20, 16);
    vl->setSpacing(12);

    vl->addWidget(makeTitle("FILTERS", card));

    QGridLayout *grid = new QGridLayout;
    grid->setHorizontalSpacing(12);
    grid->setVerticalSpacing(8);

    auto hdrLbl = [&](int col, const QString &t) {
        QLabel *l = new QLabel(t, card);
        l->setStyleSheet("color:" + Th::T2 + "; font-size:11px;"
                                             " font-weight:600; letter-spacing:0.4px;");
        grid->addWidget(l, 0, col);
    };
    hdrLbl(0, "MACHINE ID");
    hdrLbl(1, "STATUS");
    hdrLbl(2, "FROM DATE");
    hdrLbl(3, "TO DATE");

    m_fId = new QLineEdit(card);
    m_fId->setPlaceholderText("Any ID…");
    m_fId->setText(m_machineId);

    m_fStatus = new QComboBox(card);
    m_fStatus->addItem("All statuses", "");
    m_fStatus->addItem("Active", "Active");
    m_fStatus->addItem("Under Maintenance", "Under Maintenance");
    m_fStatus->addItem("Out of Service", "Out of Service");

    m_fFrom = new QDateTimeEdit(
        QDateTime::currentDateTime().addYears(-5), card);
    m_fFrom->setCalendarPopup(true);
    m_fFrom->setDisplayFormat("yyyy-MM-dd HH:mm");

    m_fTo = new QDateTimeEdit(QDateTime::currentDateTime(), card);
    m_fTo->setCalendarPopup(true);
    m_fTo->setDisplayFormat("yyyy-MM-dd HH:mm");

    grid->addWidget(m_fId,     1, 0);
    grid->addWidget(m_fStatus, 1, 1);
    grid->addWidget(m_fFrom,   1, 2);
    grid->addWidget(m_fTo,     1, 3);
    grid->setColumnStretch(4, 1);
    vl->addLayout(grid);

    // Button row
    QHBoxLayout *btns = new QHBoxLayout;
    btns->setSpacing(8);
    btns->addStretch();

    QPushButton *btnClear = new QPushButton("Clear filters", card);
    btnClear->setObjectName("btnSecondary");
    connect(btnClear, &QPushButton::clicked, this, &MachineHistory::onClearFilters);

    QPushButton *btnApply = new QPushButton("Apply filters", card);
    connect(btnApply, &QPushButton::clicked, this, &MachineHistory::onApplyFilters);

    btns->addWidget(btnClear);
    btns->addWidget(btnApply);
    vl->addLayout(btns);

    return card;
}

// ── Table card ────────────────────────────────────────────────────────────────
QFrame *MachineHistory::buildTable()
{
    QFrame *card = makeCard();
    QVBoxLayout *vl = new QVBoxLayout(card);
    vl->setContentsMargins(20, 16, 20, 16);
    vl->setSpacing(12);

    vl->addWidget(makeTitle("CHANGE LOG", card));

    m_table = new QTableWidget(0, 4, card);
    m_table->setHorizontalHeaderLabels(
        {"Date & Time", "Field", "Old Value", "New Value"});
    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    m_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Interactive);
    m_table->verticalHeader()->hide();
    m_table->setShowGrid(false);
    m_table->setAlternatingRowColors(true);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSortingEnabled(true);
    m_table->sortByColumn(0, Qt::DescendingOrder);
    m_table->setMinimumHeight(340);
    m_table->setWordWrap(true);
    m_table->verticalHeader()->setDefaultSectionSize(42);
    m_table->setStyleSheet(
        "QTableWidget { alternate-background-color:" + Th::CARD2 + ";"
                                                                   " background:" + Th::CARD + "; }"
                     "QTableWidget::item:hover { background:" + Th::ROW_HOVER + "; }");

    vl->addWidget(m_table, 1);
    return card;
}

// ── Export bar — PDF only ─────────────────────────────────────────────────────
QWidget *MachineHistory::buildExportBar()
{
    QWidget *w = new QWidget;
    QHBoxLayout *hl = new QHBoxLayout(w);
    hl->setContentsMargins(0, 0, 0, 0);
    hl->setSpacing(8);
    hl->addStretch();

    QPushButton *pdf = new QPushButton("⬇  Export PDF", w);
    connect(pdf, &QPushButton::clicked, this, &MachineHistory::onExportPDF);

    hl->addWidget(pdf);
    return w;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Data loading
// ─────────────────────────────────────────────────────────────────────────────

void MachineHistory::loadAll()
{
    loadMachineInfo();
    loadTimeline();
    onApplyFilters();
}

// ── Machine summary info ──────────────────────────────────────────────────────
void MachineHistory::loadMachineInfo()
{
    QSqlQuery q(QSqlDatabase::database("myConnection"));

    // ── 1. Base machine row: ID, name, fallback status, and PURCHASE_DATE
    q.prepare(
        "SELECT ID_MACHINE, FULL_NAME, STATUS, "
        "  TO_CHAR(PURCHASE_DATE, 'YYYY-MM-DD') "
        "FROM Machine WHERE ID_MACHINE = :id");
    q.bindValue(":id", m_machineId.toInt());

    QString fallbackStatus;
    if (q.exec() && q.next()) {
        m_info.id            = q.value(0).toString();
        m_info.name          = q.value(1).toString();
        fallbackStatus       = q.value(2).toString();
        m_info.purchaseDate  = q.value(3).toString();
    } else {
        m_info.id   = m_machineId;
        m_info.name = m_machineName;
    }

    // Handle null purchase date gracefully
    if (m_info.purchaseDate.isEmpty())
        m_info.purchaseDate = "Not available";

    // ── 2. Aggregate history: MAX(changed_at) and COUNT(*)
    //       NOTE: MIN(changed_at) intentionally removed — purchase date is
    //             fetched from Machine table (see step 1 above).
    q.prepare(
        "SELECT "
        "  TO_CHAR(MAX(changed_at), 'YYYY-MM-DD HH24:MI'), "
        "  COUNT(*) "
        "FROM machine_history "
        "WHERE machine_id = :id");
    q.bindValue(":id", m_machineId.toInt());
    if (q.exec() && q.next()) {
        m_info.lastModified  = q.value(0).toString();
        m_info.totalChanges  = q.value(1).toInt();
    }
    if (m_info.lastModified.isEmpty())
        m_info.lastModified = "No history";

    // ── 3. Current status = latest new_value for STATUS field in history,
    //       fallback to Machine.STATUS if no history exists
    q.prepare(
        "SELECT new_value FROM machine_history "
        "WHERE machine_id = :id AND UPPER(field_name) = 'STATUS' "
        "ORDER BY changed_at DESC "
        "FETCH FIRST 1 ROWS ONLY");
    q.bindValue(":id", m_machineId.toInt());
    if (q.exec() && q.next() && !q.value(0).toString().isEmpty())
        m_info.currentStatus = q.value(0).toString();
    else
        m_info.currentStatus = fallbackStatus.isEmpty() ? "Unknown" : fallbackStatus;

    // ── 4. Most frequent status (informational)
    q.prepare(
        "SELECT new_value, COUNT(*) cnt "
        "FROM machine_history "
        "WHERE machine_id = :id AND UPPER(field_name) = 'STATUS' "
        "GROUP BY new_value "
        "ORDER BY cnt DESC "
        "FETCH FIRST 1 ROWS ONLY");
    q.bindValue(":id", m_machineId.toInt());
    if (q.exec() && q.next())
        m_info.mostFreqStatus = q.value(0).toString();

    // ── Populate summary labels
    m_lblId->setText(m_info.id.isEmpty() ? m_machineId : m_info.id);
    m_lblPurchaseDate->setText(m_info.purchaseDate);
    m_lblModified->setText(m_info.lastModified);
    m_lblChanges->setText(QString::number(m_info.totalChanges));

    m_lblStatus->setText(m_info.currentStatus);
    m_lblStatus->setStyleSheet(badgeStyle(m_info.currentStatus));

    if (!m_info.mostFreqStatus.isEmpty()) {
        m_badgeFreq->setText("Most frequent:  " + m_info.mostFreqStatus);
        m_badgeFreq->setStyleSheet("color:" + Th::T2 + "; font-size:11px;");
    }
}

// ── Timeline segments ─────────────────────────────────────────────────────────
void MachineHistory::loadTimeline()
{
    QSqlQuery q(QSqlDatabase::database("myConnection"));
    q.prepare(
        "SELECT new_value, changed_at "
        "FROM machine_history "
        "WHERE machine_id = :id AND UPPER(field_name) = 'STATUS' "
        "ORDER BY changed_at ASC");
    q.bindValue(":id", m_machineId.toInt());

    QList<QPair<QString,QDateTime>> rows;
    if (q.exec())
        while (q.next())
            rows << qMakePair(q.value(0).toString(),
                              q.value(1).toDateTime());

    m_segments.clear();

    if (rows.isEmpty()) {
        // No history: single segment from purchase date to now
        QDateTime start = QDateTime::currentDateTime().addYears(-1);
        QSqlQuery pq(QSqlDatabase::database("myConnection"));
        pq.prepare("SELECT PURCHASE_DATE FROM Machine WHERE ID_MACHINE = :id");
        pq.bindValue(":id", m_machineId.toInt());
        if (pq.exec() && pq.next() && !pq.value(0).isNull())
            start = pq.value(0).toDateTime();

        StatusSegment seg;
        seg.status      = m_info.currentStatus;
        seg.from        = start;
        seg.to          = QDateTime();
        seg.durationSec = start.secsTo(QDateTime::currentDateTime());
        seg.pct         = 100.0;
        m_segments << seg;

        m_tlNoData->show();
        m_timeline->setSegments(m_segments);
        return;
    }

    m_tlNoData->hide();

    QDateTime now = QDateTime::currentDateTime();
    qint64 totalSec = 0;

    for (int i = 0; i < rows.size(); ++i) {
        StatusSegment seg;
        seg.status = rows[i].first;
        seg.from   = rows[i].second;
        seg.to     = (i + 1 < rows.size()) ? rows[i+1].second : QDateTime();
        QDateTime effectiveTo = seg.to.isNull() ? now : seg.to;
        seg.durationSec = seg.from.secsTo(effectiveTo);
        if (seg.durationSec < 0) seg.durationSec = 0;
        totalSec += seg.durationSec;
        m_segments << seg;
    }

    for (auto &seg : m_segments)
        seg.pct = (totalSec > 0) ? (100.0 * seg.durationSec / totalSec) : 0.0;

    m_timeline->setSegments(m_segments);
}

// ── Change-log table ──────────────────────────────────────────────────────────
void MachineHistory::loadTable(const QString &idF,
                               const QString &statusF,
                               const QDateTime &from,
                               const QDateTime &to)
{
    m_table->setSortingEnabled(false);
    m_table->setRowCount(0);

    QSqlQuery q(QSqlDatabase::database("myConnection"));

    QString sql =
        "SELECT "
        "  TO_CHAR(changed_at,'YYYY-MM-DD HH24:MI:SS'), "
        "  field_name, old_value, new_value "
        "FROM machine_history "
        "WHERE machine_id = :id "
        "  AND changed_at >= :from "
        "  AND changed_at <= :to ";

    if (!statusF.isEmpty())
        sql += "  AND UPPER(field_name) = 'STATUS' "
               "  AND UPPER(new_value) = UPPER(:status) ";

    sql += "ORDER BY changed_at DESC";

    q.prepare(sql);
    q.bindValue(":id",   idF.isEmpty() ? m_machineId.toInt()
                                     : idF.trimmed().toInt());
    q.bindValue(":from", from);
    q.bindValue(":to",   to);
    if (!statusF.isEmpty())
        q.bindValue(":status", statusF);

    if (!q.exec()) {
        m_table->setSortingEnabled(true);
        return;
    }

    while (q.next()) {
        int row = m_table->rowCount();
        m_table->insertRow(row);

        auto makeItem = [](const QString &v) {
            auto *it = new QTableWidgetItem(v);
            it->setFlags(it->flags() & ~Qt::ItemIsEditable);
            return it;
        };

        m_table->setItem(row, 0, makeItem(q.value(0).toString()));
        m_table->setItem(row, 1, makeItem(q.value(1).toString()));

        // Old value — muted colour
        auto *oldIt = makeItem(q.value(2).toString().isEmpty()
                                   ? "—" : q.value(2).toString());
        oldIt->setForeground(QColor(Th::T2));
        m_table->setItem(row, 2, oldIt);

        // New value — coloured for STATUS field
        QString field  = q.value(1).toString().toUpper();
        QString newVal = q.value(3).toString();
        auto *newIt = makeItem(newVal.isEmpty() ? "—" : newVal);
        if (field == "STATUS" && !newVal.isEmpty())
            newIt->setForeground(statusColor(newVal));
        m_table->setItem(row, 3, newIt);
    }

    m_table->setSortingEnabled(true);

    // Empty-state row when no results
    if (m_table->rowCount() == 0) {
        m_table->insertRow(0);
        QTableWidgetItem *it = new QTableWidgetItem("No changes recorded for the selected filters.");
        it->setForeground(QColor(Th::T3));
        it->setTextAlignment(Qt::AlignCenter);
        it->setFlags(it->flags() & ~Qt::ItemIsEditable);
        m_table->setItem(0, 0, it);
        m_table->setSpan(0, 0, 1, 4);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Slots
// ─────────────────────────────────────────────────────────────────────────────
void MachineHistory::onApplyFilters()
{
    loadTable(m_fId->text().trimmed(),
              m_fStatus->currentData().toString(),
              m_fFrom->dateTime(),
              m_fTo->dateTime());
}

void MachineHistory::onClearFilters()
{
    m_fId->setText(m_machineId);
    m_fStatus->setCurrentIndex(0);
    m_fFrom->setDateTime(QDateTime::currentDateTime().addYears(-5));
    m_fTo->setDateTime(QDateTime::currentDateTime());
    onApplyFilters();
}

// ─────────────────────────────────────────────────────────────────────────────
//  PDF export — white background, black text, professional layout
// ─────────────────────────────────────────────────────────────────────────────
void MachineHistory::onExportPDF()
{
    QString path = QFileDialog::getSaveFileName(
        this, "Export History PDF",
        "machine_" + m_machineId + "_history.pdf",
        "PDF Files (*.pdf)");
    if (path.isEmpty()) return;
    writePDF(path);
}

void MachineHistory::writePDF(const QString &path)
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

    // Page-break guard
    auto newPageIfNeeded = [&](int neededH) {
        if (y + neededH > writer.height() - 60) {
            writer.newPage();
            y = 0;
        }
    };

    // Horizontal rule helper
    auto hRule = [&]() {
        p.setPen(QPen(QColor("#cccccc"), 1));
        p.drawLine(0, y, W, y);
        p.setPen(Qt::black);
        y += lh / 2;
    };

    // ── Title block ────────────────────────────────────────────────────────
    p.setFont(QFont("Arial", 18, QFont::Bold));
    p.setPen(QColor("#111111"));
    p.drawText(QRect(0, y, W, 50), Qt::AlignLeft | Qt::AlignVCenter,
               "Machine History Report");
    y += 54;

    p.setFont(QFont("Arial", 10));
    p.setPen(QColor("#555555"));
    p.drawText(0, y,
               "Machine: " + m_machineName
                   + "   |   ID: " + m_machineId
                   + "   |   Exported: "
                   + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"));
    y += lh;
    hRule();

    // ── Summary section ────────────────────────────────────────────────────
    p.setFont(QFont("Arial", 12, QFont::Bold));
    p.setPen(QColor("#111111"));
    p.drawText(0, y, "Summary");
    y += lh;
    hRule();

    p.setFont(QFont("Arial", 10));
    p.setPen(Qt::black);

    auto pdfRow = [&](const QString &label, const QString &val) {
        newPageIfNeeded(lh);
        p.setPen(QColor("#666666"));
        p.drawText(QRect(0, y, 200, lh), Qt::AlignRight | Qt::AlignVCenter, label);
        p.setPen(Qt::black);
        p.drawText(QRect(210, y, W - 210, lh), Qt::AlignLeft | Qt::AlignVCenter, val);
        y += lh;
    };

    pdfRow("Machine ID:",     m_info.id.isEmpty() ? m_machineId : m_info.id);
    pdfRow("Purchase Date:",  m_info.purchaseDate);   // ← Purchase Date (not creation)
    pdfRow("Current Status:", m_info.currentStatus);
    pdfRow("Last Modified:",  m_info.lastModified);
    pdfRow("Total Changes:",  QString::number(m_info.totalChanges));

    if (!m_info.mostFreqStatus.isEmpty())
        pdfRow("Most Frequent Status:", m_info.mostFreqStatus);

    y += lh / 2;

    // ── Timeline text summary ──────────────────────────────────────────────
    newPageIfNeeded(lh * 3);
    p.setFont(QFont("Arial", 12, QFont::Bold));
    p.setPen(QColor("#111111"));
    p.drawText(0, y, "Status Timeline");
    y += lh;
    hRule();

    p.setFont(QFont("Arial", 10));
    p.setPen(Qt::black);

    if (m_segments.isEmpty()) {
        p.setPen(QColor("#999999"));
        p.drawText(0, y, "No timeline data available.");
        y += lh;
    } else {
        QDateTime now = QDateTime::currentDateTime();
        for (const auto &seg : m_segments) {
            newPageIfNeeded(lh);
            QString toStr = seg.to.isNull()
                                ? "Now (" + now.toString("yyyy-MM-dd HH:mm") + ")"
                                : seg.to.toString("yyyy-MM-dd HH:mm");
            QString line = QString("  %-22 1  —  %2  →  %3   (%4,  %5%)")
                               .arg(seg.status)
                               .arg(seg.from.toString("yyyy-MM-dd HH:mm"))
                               .arg(toStr)
                               .arg(fmtDuration(seg.durationSec))
                               .arg(QString::number(seg.pct, 'f', 1));
            p.drawText(0, y, line);
            y += lh;
        }
    }
    y += lh / 2;

    // ── Change log table ───────────────────────────────────────────────────
    newPageIfNeeded(lh * 4);
    p.setFont(QFont("Arial", 12, QFont::Bold));
    p.setPen(QColor("#111111"));
    p.drawText(0, y, "Change Log");
    y += lh;
    hRule();

    // Column widths
    const int cw[4] = { 200, 160, (W - 360) / 2, (W - 360) / 2 };
    const QString headers[4] = { "Date & Time", "Field", "Old Value", "New Value" };

    // Header row with grey background
    p.setFont(QFont("Arial", 9, QFont::Bold));
    p.fillRect(QRect(0, y, W, lh), QColor("#f0f0f0"));
    int x = 0;
    for (int c = 0; c < 4; ++c) {
        p.setPen(QColor("#333333"));
        p.drawText(QRect(x + 4, y, cw[c] - 8, lh),
                   Qt::AlignLeft | Qt::AlignVCenter, headers[c]);
        x += cw[c];
    }
    y += lh;
    hRule();

    p.setFont(QFont("Arial", 9));
    bool alt = false;
    int rowCount = m_table->rowCount();

    if (rowCount == 0) {
        p.setPen(QColor("#999999"));
        p.drawText(QRect(0, y, W, lh), Qt::AlignCenter | Qt::AlignVCenter,
                   "No changes recorded.");
        y += lh;
    } else {
        for (int r = 0; r < rowCount; ++r) {
            newPageIfNeeded(lh);
            if (alt) p.fillRect(QRect(0, y, W, lh), QColor("#f9f9f9"));
            alt = !alt;
            x = 0;
            for (int c = 0; c < 4; ++c) {
                QTableWidgetItem *it = m_table->item(r, c);
                QString txt = it ? it->text() : "";
                // Field column gets a subtle blue tint in PDF
                p.setPen(c == 1 ? QColor("#1a6dba") : Qt::black);
                p.drawText(QRect(x + 4, y, cw[c] - 8, lh),
                           Qt::AlignLeft | Qt::AlignVCenter, txt);
                x += cw[c];
            }
            y += lh;
        }
    }

    p.end();
    QMessageBox::information(this, "PDF Exported",
                             "Report saved successfully:\n" + path);
}

// ─────────────────────────────────────────────────────────────────────────────
//  TimelineBar implementation
// ─────────────────────────────────────────────────────────────────────────────
QColor TimelineBar::colorForStatus(const QString &s) { return statusColor(s); }

TimelineBar::TimelineBar(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setMinimumHeight(80);
    setAttribute(Qt::WA_Hover);
}

void TimelineBar::setSegments(const QList<StatusSegment> &segs)
{
    m_segs     = segs;
    m_hoverIdx = -1;
    update();
}

QList<QRectF> TimelineBar::segRects() const
{
    const qreal BAR_TOP = 28, BAR_H = 28;
    const qreal W = width() - 2, X0 = 1;

    QList<QRectF> rects;
    qreal x = X0;
    for (const auto &seg : m_segs) {
        qreal w = W * (seg.pct / 100.0);
        if (w < 1) w = 1;
        rects << QRectF(x, BAR_TOP, w, BAR_H);
        x += w;
    }
    return rects;
}

void TimelineBar::paintEvent(QPaintEvent *)
{
    if (m_segs.isEmpty()) return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    auto rects = segRects();

    // Draw segments
    for (int i = 0; i < m_segs.size(); ++i) {
        const auto  &seg = m_segs[i];
        const QRectF &r  = rects[i];
        QColor base = colorForStatus(seg.status);

        if (i == m_hoverIdx) base = base.lighter(130);

        QPainterPath pp;
        qreal rad = 5;
        bool isFirst = (i == 0), isLast = (i == m_segs.size() - 1);
        QRectF inset = r.adjusted(isFirst ? 0 : 1, 0, isLast ? 0 : -1, 0);

        if (isFirst && isLast) {
            pp.addRoundedRect(inset, rad, rad);
        } else if (isFirst) {
            pp.moveTo(inset.right(), inset.top());
            pp.lineTo(inset.left() + rad, inset.top());
            pp.quadTo(inset.topLeft(), QPointF(inset.left(), inset.top() + rad));
            pp.lineTo(inset.bottomLeft() + QPointF(0, -rad));
            pp.quadTo(inset.bottomLeft(), QPointF(inset.left() + rad, inset.bottom()));
            pp.lineTo(inset.bottomRight());
            pp.closeSubpath();
        } else if (isLast) {
            pp.moveTo(inset.topLeft());
            pp.lineTo(inset.right() - rad, inset.top());
            pp.quadTo(inset.topRight(), QPointF(inset.right(), inset.top() + rad));
            pp.lineTo(inset.right(), inset.bottom() - rad);
            pp.quadTo(inset.bottomRight(), QPointF(inset.right() - rad, inset.bottom()));
            pp.lineTo(inset.bottomLeft());
            pp.closeSubpath();
        } else {
            pp.addRect(inset);
        }
        p.fillPath(pp, base);

        // Percentage label (only if segment is wide enough)
        if (r.width() > 40) {
            p.setPen(Qt::white);
            QFont f = p.font();
            f.setPixelSize(11);
            f.setBold(true);
            p.setFont(f);
            p.drawText(r, Qt::AlignCenter, QString::number(seg.pct, 'f', 1) + "%");
        }
    }

    // Status name labels above the bar
    for (int i = 0; i < m_segs.size(); ++i) {
        const QRectF &r = rects[i];
        if (r.width() < 36) continue;
        QFont f = p.font();
        f.setPixelSize(11);
        f.setBold(false);
        p.setFont(f);
        p.setPen(QColor(Th::T2));
        QRectF lblR(r.left(), 4, r.width(), 20);
        p.drawText(lblR, Qt::AlignCenter,
                   QFontMetrics(p.font()).elidedText(
                       m_segs[i].status, Qt::ElideRight,
                       static_cast<int>(r.width() - 6)));
    }

    // Duration labels below the bar
    for (int i = 0; i < m_segs.size(); ++i) {
        const QRectF &r = rects[i];
        if (r.width() < 48) continue;
        QFont f = p.font();
        f.setPixelSize(10);
        f.setBold(false);
        p.setFont(f);
        p.setPen(QColor(Th::T3));
        QRectF durR(r.left(), r.bottom() + 4, r.width(), 14);
        p.drawText(durR, Qt::AlignCenter, fmtDuration(m_segs[i].durationSec));
    }
}

void TimelineBar::mouseMoveEvent(QMouseEvent *e)
{
    auto rects = segRects();
    int found = -1;
    for (int i = 0; i < rects.size(); ++i) {
        if (rects[i].contains(e->pos())) { found = i; break; }
    }
    if (found != m_hoverIdx) { m_hoverIdx = found; update(); }

    if (found >= 0) {
        const auto &seg = m_segs[found];
        QDateTime now = QDateTime::currentDateTime();
        QString toStr = seg.to.isNull()
                            ? "Now (" + now.toString("yyyy-MM-dd HH:mm") + ")"
                            : seg.to.toString("yyyy-MM-dd HH:mm");
        QToolTip::showText(e->globalPosition().toPoint(),
                           QString("<b>%1</b><br>"
                                   "From: %2<br>"
                                   "To:   %3<br>"
                                   "Duration: %4<br>"
                                   "Share: %5%")
                               .arg(seg.status,
                                    seg.from.toString("yyyy-MM-dd HH:mm"),
                                    toStr,
                                    fmtDuration(seg.durationSec),
                                    QString::number(seg.pct, 'f', 1)),
                           this);
    } else {
        QToolTip::hideText();
    }
}

void TimelineBar::leaveEvent(QEvent *)
{
    m_hoverIdx = -1;
    update();
    QToolTip::hideText();
}