#include "machinestats.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QFrame>
#include <QDate>
#include <QPainter>
#include <QFont>

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

static const QString S_BG     = "#0a0f0a";
static const QString S_CARD   = "#0d1f0d";
static const QString S_GREEN  = "#00e676";
static const QString S_BORDER = "#00e676";
static const QString S_TEXT   = "#ccddee";
static const QList<QColor> PALETTE = {
    QColor("#1a9e8f"), QColor("#1465a4"), QColor("#0d7bc4"),
    QColor("#0a4f7a"), QColor("#16c79a"), QColor("#f4a261")
};

static QLabel* makeCard(const QString &title, const QString &value)
{
    QLabel *card = new QLabel();
    card->setStyleSheet(QString(
                            "background:%1; border:1px solid %2; border-radius:8px; padding:12px;")
                            .arg(S_CARD).arg(S_BORDER));
    card->setText(QString(
                      "<div style='color:%1;font-size:11px;'>%2</div>"
                      "<div style='color:%3;font-size:20px;font-weight:bold;'>%4</div>")
                      .arg(S_TEXT).arg(title).arg(S_GREEN).arg(value));
    card->setTextFormat(Qt::RichText);
    card->setAlignment(Qt::AlignCenter);
    card->setMinimumSize(140, 80);
    return card;
}

static QChartView* makePieChart(const QString &title, const QMap<QString,int> &data)
{
    QPieSeries *series = new QPieSeries();
    int i = 0;
    for (auto it = data.constBegin(); it != data.constEnd(); ++it, ++i) {
        QPieSlice *sl = series->append(
            it.key() + " (" + QString::number(it.value()) + ")", it.value());
        sl->setLabelVisible(true);
        sl->setLabelColor(QColor(S_TEXT));
        sl->setBrush(PALETTE[i % PALETTE.size()]);
        sl->setPen(QPen(QColor(S_BG), 2));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->setTitleFont(QFont("Arial", 10, QFont::Bold));
    chart->setTitleBrush(QBrush(QColor(S_TEXT)));
    chart->setBackgroundBrush(QBrush(QColor(S_CARD)));
    chart->setBackgroundPen(QPen(QColor(S_BORDER), 1));
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setLabelColor(QColor(S_TEXT));
    chart->legend()->setBackgroundVisible(false);
    chart->setMargins(QMargins(8,8,8,8));

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumSize(400, 300);
    return view;
}

static QChartView* makeBarChart(const QString &title,
                                const QMap<QString,int> &data,
                                const QColor &color)
{
    QBarSet *set = new QBarSet("");
    set->setColor(color);
    set->setBorderColor(color.darker(120));
    set->setLabelColor(QColor(S_TEXT));
    QStringList cats;
    int maxVal = 0;
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        *set << it.value();
        cats << it.key();
        maxVal = qMax(maxVal, it.value());
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(cats);
    axisX->setLabelsColor(QColor(S_TEXT));
    axisX->setGridLineColor(QColor(S_BORDER));
    axisX->setLinePen(QPen(QColor(S_BORDER)));

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxVal + 1);
    axisY->setTickCount(maxVal + 2);
    axisY->setLabelFormat("%d");
    axisY->setLabelsColor(QColor(S_TEXT));
    axisY->setGridLineColor(QColor(S_BORDER));
    axisY->setLinePen(QPen(QColor(S_BORDER)));

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->setTitleFont(QFont("Arial", 10, QFont::Bold));
    chart->setTitleBrush(QBrush(QColor(S_TEXT)));
    chart->setBackgroundBrush(QBrush(QColor(S_CARD)));
    chart->setBackgroundPen(QPen(QColor(S_BORDER), 1));
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    chart->legend()->hide();
    chart->setMargins(QMargins(8,8,8,8));

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumSize(400, 300);
    return view;
}

// ── MachineGlobalStats ────────────────────────────────────────────────────────

MachineGlobalStats::MachineGlobalStats(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Machine Fleet Statistics");
    setMinimumSize(1000, 800);
    setStyleSheet(QString("background-color:%1; color:%2;").arg(S_BG).arg(S_TEXT));

    QSqlQuery q(QSqlDatabase::database("myConnection"));

    int total = 0, active = 0, maintenance = 0, outOfService = 0;
    QMap<QString,int> statusMap, typeMap, yearMap;

    q.exec("SELECT STATUS, COUNT(*) FROM Machine GROUP BY STATUS");
    while (q.next()) {
        QString s = q.value(0).toString();
        int cnt   = q.value(1).toInt();
        statusMap[s] = cnt;
        total += cnt;
        if      (s == "Active")            active       += cnt;
        else if (s == "Under Maintenance") maintenance  += cnt;
        else if (s == "Out of Service")    outOfService += cnt;
    }

    q.exec("SELECT TYPE, COUNT(*) FROM Machine GROUP BY TYPE");
    while (q.next())
        typeMap[q.value(0).toString()] = q.value(1).toInt();

    q.exec("SELECT TO_CHAR(PURCHASE_DATE,'YYYY'), COUNT(*) FROM Machine "
           "GROUP BY TO_CHAR(PURCHASE_DATE,'YYYY') ORDER BY 1");
    while (q.next())
        yearMap[q.value(0).toString()] = q.value(1).toInt();

    int availPct = total > 0 ? (active * 100 / total) : 0;

    QVBoxLayout *root = new QVBoxLayout(this);
    root->setSpacing(14);
    root->setContentsMargins(20,20,20,20);

    QLabel *titleLbl = new QLabel("Machine Fleet Statistics");
    titleLbl->setStyleSheet(QString("color:%1; font-size:18px; font-weight:bold;").arg(S_GREEN));
    root->addWidget(titleLbl);

    QHBoxLayout *cards = new QHBoxLayout();
    cards->addWidget(makeCard("TOTAL MACHINES", QString::number(total)));
    cards->addWidget(makeCard("ACTIVE",         QString::number(active)));
    cards->addWidget(makeCard("MAINTENANCE",    QString::number(maintenance)));
    cards->addWidget(makeCard("OUT OF SERVICE", QString::number(outOfService)));
    root->addLayout(cards);

    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(12);
    grid->setRowStretch(0, 1);
    grid->setRowStretch(1, 1);
    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 1);

    auto *pieChart  = makePieChart("Status Breakdown", statusMap);
    auto *typeChart = makeBarChart("Machines by Type", typeMap, QColor("#1a9e8f"));
    auto *yearChart = makeBarChart("Machines by Year", yearMap, QColor("#1465a4"));
    pieChart->setMinimumSize(400, 300);
    typeChart->setMinimumSize(400, 300);
    yearChart->setMinimumSize(400, 300);
    pieChart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    typeChart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    yearChart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    grid->addWidget(pieChart,  0, 0);
    grid->addWidget(typeChart, 0, 1);
    grid->addWidget(yearChart, 1, 0);

    // Gauge card — expands to fill the same grid cell as yearChart
    QFrame *gaugeCard = new QFrame();
    gaugeCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gaugeCard->setMinimumSize(400, 300);
    gaugeCard->setStyleSheet(QString(
                                 "background:%1; border:1px solid %2; border-radius:8px;").arg(S_CARD).arg(S_BORDER));

    QVBoxLayout *gv = new QVBoxLayout(gaugeCard);
    gv->setContentsMargins(20, 0, 20, 0);
    gv->setSpacing(12);

    QLabel *gTitle = new QLabel("Fleet Availability Rate");
    gTitle->setStyleSheet(QString("color:%1; font-size:11px; font-weight:bold; border:none;").arg(S_TEXT));
    gTitle->setAlignment(Qt::AlignCenter);

    QLabel *gPct = new QLabel(QString::number(availPct) + "%");
    gPct->setStyleSheet(QString("color:%1; font-size:48px; font-weight:bold; border:none;").arg(S_GREEN));
    gPct->setAlignment(Qt::AlignCenter);

    QProgressBar *gBar = new QProgressBar();
    gBar->setRange(0, 100);
    gBar->setValue(availPct);
    gBar->setTextVisible(false);
    gBar->setFixedHeight(18);
    gBar->setStyleSheet(QString(
                            "QProgressBar { background:%1; border-radius:9px; border:1px solid %2; }"
                            "QProgressBar::chunk { background:%3; border-radius:9px; }")
                            .arg(S_BG).arg(S_BORDER).arg(S_GREEN));

    gv->addStretch(1);
    gv->addWidget(gTitle);
    gv->addWidget(gPct);
    gv->addWidget(gBar);
    gv->addStretch(1);

    grid->addWidget(gaugeCard, 1, 1);
    grid->setRowMinimumHeight(0, 300);
    grid->setRowMinimumHeight(1, 300);

    root->addLayout(grid, 1);
}

// ── MachineSingleStats ────────────────────────────────────────────────────────

MachineSingleStats::MachineSingleStats(const QString &id,
                                       const QString &name,
                                       const QString &type,
                                       const QString &location,
                                       const QString &purchaseDate,
                                       const QString &status,
                                       QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Machine Performance — " + name);
    setMinimumSize(600, 650);
    setStyleSheet(QString("background-color:%1; color:%2;").arg(S_BG).arg(S_TEXT));

    QDate purchase = QDate::fromString(purchaseDate, "yyyy-MM-dd");
    QDate today    = QDate::currentDate();
    int years  = 0, months = 0;
    if (purchase.isValid()) {
        years = purchase.daysTo(today) / 365;
        months = today.month() + today.year() * 12
                 - purchase.month() - purchase.year() * 12;
        months = months % 12;
    }
    QString ageStr = purchase.isValid()
                         ? QString("%1y %2m").arg(years).arg(months) : "N/A";

    int availPct = 0;
    QString statusColor = "#f44336";
    if      (status == "Active")            { availPct = 100; statusColor = "#00e676"; }
    else if (status == "Under Maintenance") { availPct = 50;  statusColor = "#ff9800"; }

    QVBoxLayout *root = new QVBoxLayout(this);
    root->setSpacing(14);
    root->setContentsMargins(20,20,20,20);

    QLabel *hdr = new QLabel(name + "  <span style='color:" + S_TEXT +
                             ";font-size:13px;font-weight:normal;'>ID: " + id + "</span>");
    hdr->setStyleSheet(QString("color:%1; font-size:20px; font-weight:bold;").arg(S_GREEN));
    hdr->setTextFormat(Qt::RichText);
    root->addWidget(hdr);

    QHBoxLayout *cards = new QHBoxLayout();
    cards->addWidget(makeCard("TYPE",          type));
    cards->addWidget(makeCard("LOCATION",      location));
    cards->addWidget(makeCard("PURCHASE DATE", purchaseDate));
    cards->addWidget(makeCard("AGE",           ageStr));
    root->addLayout(cards);

    QLabel *badge = new QLabel(status);
    badge->setAlignment(Qt::AlignCenter);
    badge->setStyleSheet(QString(
                             "background:%1; color:#0a1628; border-radius:8px;"
                             " font-size:16px; font-weight:bold; padding:10px;").arg(statusColor));
    root->addWidget(badge);

    QLabel *availLabel = new QLabel(QString("Availability: %1%").arg(availPct));
    availLabel->setStyleSheet(QString("color:%1; font-size:13px;").arg(S_TEXT));
    QProgressBar *bar = new QProgressBar();
    bar->setRange(0, 100);
    bar->setValue(availPct);
    bar->setTextVisible(false);
    bar->setFixedHeight(22);
    bar->setStyleSheet(QString(
                           "QProgressBar { background:%1; border-radius:11px; border:1px solid %2; }"
                           "QProgressBar::chunk { background:%3; border-radius:11px; }")
                           .arg(S_BG).arg(S_BORDER).arg(statusColor));
    root->addWidget(availLabel);
    root->addWidget(bar);

    QMap<QString,int> pieData;
    pieData["Operational"] = availPct;
    if (availPct < 100)
        pieData["Downtime"] = 100 - availPct;
    root->addWidget(makePieChart("Operational vs Downtime", pieData));

    QPushButton *btn = new QPushButton("Close");
    btn->setStyleSheet(QString(
                           "QPushButton { background:%1; color:#0a1628; border-radius:6px;"
                           " padding:8px 24px; font-weight:bold; font-size:13px; }"
                           "QPushButton:hover { background:#00ff8a; }").arg(S_GREEN));
    btn->setFixedWidth(120);
    connect(btn, &QPushButton::clicked, this, &QDialog::accept);
    QHBoxLayout *btnRow = new QHBoxLayout();
    btnRow->addStretch();
    btnRow->addWidget(btn);
    btnRow->addStretch();
    root->addLayout(btnRow);
}
