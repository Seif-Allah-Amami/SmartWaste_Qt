#include "advancedfeatures.h"

#include <algorithm>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QFrame>
#include <QGridLayout>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollArea>
#include <QSplitter>
#include <QSizePolicy>
#include <QStyle>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>
#include <QtGlobal>

namespace {
QList<Customer> g_autoExportCustomers;
bool g_autoExportHookInstalled = false;

void writeAutoBackupCsv(const QList<Customer> &customers)
{
    const QString filePath = QString("reports_backup_%1.csv").arg(QDate::currentDate().toString("yyyyMMdd"));
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << "customer_id,name,email,phone,address,report_type,report_date,status\n";
    for (const Customer &c : customers) {
        out << c.customerId() << ","
            << '"' << c.name().replace('"', "''") << "\","
            << '"' << c.email().replace('"', "''") << "\","
            << '"' << c.phone().replace('"', "''") << "\","
            << '"' << c.address().replace('"', "''") << "\","
            << '"' << c.reportType().replace('"', "''") << "\","
            << c.reportDate().toString("yyyy-MM-dd") << ","
            << c.status()
            << "\n";
    }
}
}

AdvancedFeatures::AdvancedFeatures(const QList<Customer> &customers, QWidget *parent)
    : QDialog(parent)
    , customers_(customers)
    , totalReportsValueLabel_(nullptr)
    , resolvedPercentValueLabel_(nullptr)
    , pendingPercentValueLabel_(nullptr)
    , commonTypeValueLabel_(nullptr)
    , avgResolutionValueLabel_(nullptr)
    , statusBadgeLabel_(nullptr)
    , statusSuggestionLabel_(nullptr)
    , resolvedProgressBar_(nullptr)
    , pendingProgressBar_(nullptr)
    , searchFilterEdit_(nullptr)
    , statusFilterCombo_(nullptr)
    , typeFilterCombo_(nullptr)
    , fromDateFilterEdit_(nullptr)
    , toDateFilterEdit_(nullptr)
    , reportsTable_(nullptr)
    , smartSortButton_(nullptr)
    , deleteButton_(nullptr)
    , chatDisplay_(nullptr)
    , messageInput_(nullptr)
    , sendButton_(nullptr)
    , priorityButton_(nullptr)
    , predictiveButton_(nullptr)
    , titleLabel_(nullptr)
    , prioritySortEnabled_(false)
    , overdueThresholdDays_(5)
{
    setupUI();
    g_autoExportCustomers = customers_;
    if (!g_autoExportHookInstalled && QCoreApplication::instance()) {
        QObject::connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, QCoreApplication::instance(), []() {
            writeAutoBackupCsv(g_autoExportCustomers);
        });
        g_autoExportHookInstalled = true;
    }

    refreshDashboardAndTable();
    showOverduePendingAlert();

    addMessage("Hello! I'm your AI Assistant for SmartWaste. I can help you with:<br><br>"
               "<b>&#128202; AI Priority Detection</b> - Analyze reports and assign priority levels<br>"
               "<b>&#128302; Predictive Analytics</b> - Forecast next week's reports and trends<br>"
               "<b>&#9888; Escalation Alerts</b> - Identify reports likely to become critical<br>"
               "<b>&#128203; Actionable Recommendations</b> - Get proactive measures for admins<br><br>"
               "Click the buttons below or type your question!", false);
}

AdvancedFeatures::~AdvancedFeatures()
{
}

void AdvancedFeatures::closeEvent(QCloseEvent *event)
{
    onAutoExportCsvBackup();
    QDialog::closeEvent(event);
}

void AdvancedFeatures::setupUI()
{
    setWindowTitle("AI Assistant - SmartWaste");
    setMinimumSize(980, 700);
    resize(1240, 840);

    setStyleSheet(
        "QDialog {"
        "    background-color: #0D1117;"
        "    color: #66ffcc;"
        "}"
        "QLabel {"
        "    color: #00ff9c;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    padding: 2px;"
        "}"
        "QFrame#panel {"
        "    background-color: #081713;"
        "    border: 1px solid #00ff9c;"
        "    border-radius: 10px;"
        "}"
        "QTextEdit {"
        "    background-color: #081713;"
        "    color: #66ffcc;"
        "    border: 1px solid #00ff9c;"
        "    border-radius: 10px;"
        "    padding: 8px;"
        "    font-size: 13px;"
        "}"
        "QLineEdit {"
        "    background-color: #081713;"
        "    color: #66ffcc;"
        "    border: 1px solid #00ff9c;"
        "    border-radius: 8px;"
        "    padding: 8px;"
        "    font-size: 13px;"
        "}"
        "QComboBox, QDateEdit {"
        "    background-color: #081713;"
        "    color: #66ffcc;"
        "    border: 1px solid #00ff9c;"
        "    border-radius: 8px;"
        "    padding: 6px;"
        "}"
        "QPushButton {"
        "    background-color: #0a1f18;"
        "    border: 1px solid #00ff9c;"
        "    border-radius: 8px;"
        "    padding: 10px 20px;"
        "    color: #00ff9c;"
        "    font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(0, 255, 156, 0.15);"
        "}"
        "QPushButton#primaryBtn {"
        "    background-color: #00ff9c;"
        "    color: #050d0a;"
        "}"
        "QPushButton#primaryBtn:hover {"
        "    background-color: #33ffcc;"
        "}"
        "QProgressBar {"
        "    border: 1px solid #1e4b3d;"
        "    border-radius: 6px;"
        "    background: #081713;"
        "    text-align: center;"
        "    color: #d5ffee;"
        "}"
        "QProgressBar::chunk {"
        "    border-radius: 6px;"
        "    background: #00ff9c;"
        "}"
        );

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(8, 8, 8, 8);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *contentWidget = new QWidget(scrollArea);
    scrollArea->setWidget(contentWidget);
    outerLayout->addWidget(scrollArea);

    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    titleLabel_ = new QLabel("AI Assistant", this);
    titleLabel_->setAlignment(Qt::AlignCenter);
    titleLabel_->setStyleSheet("QLabel { font-size: 24px; color:#ffffff; padding: 4px; }");
    mainLayout->addWidget(titleLabel_);

    QFrame *analyticsPanel = new QFrame(this);
    analyticsPanel->setObjectName("panel");
    QGridLayout *analyticsLayout = new QGridLayout(analyticsPanel);
    analyticsLayout->setContentsMargins(12, 12, 12, 12);
    analyticsLayout->setHorizontalSpacing(20);

    totalReportsValueLabel_ = new QLabel("0", analyticsPanel);
    resolvedPercentValueLabel_ = new QLabel("0%", analyticsPanel);
    pendingPercentValueLabel_ = new QLabel("0%", analyticsPanel);
    commonTypeValueLabel_ = new QLabel("-", analyticsPanel);
    avgResolutionValueLabel_ = new QLabel("0 day(s)", analyticsPanel);
    statusBadgeLabel_ = new QLabel("Pending (0) | In Progress (0) | Solved (0) | Rejected (0)", analyticsPanel);
    statusSuggestionLabel_ = new QLabel("Suggested Status: -", analyticsPanel);

    resolvedProgressBar_ = new QProgressBar(analyticsPanel);
    pendingProgressBar_ = new QProgressBar(analyticsPanel);
    resolvedProgressBar_->setRange(0, 100);
    pendingProgressBar_->setRange(0, 100);

    analyticsLayout->addWidget(new QLabel("Total Reports", analyticsPanel), 0, 0);
    analyticsLayout->addWidget(totalReportsValueLabel_, 0, 1);
    analyticsLayout->addWidget(new QLabel("% Resolved", analyticsPanel), 0, 2);
    analyticsLayout->addWidget(resolvedPercentValueLabel_, 0, 3);
    analyticsLayout->addWidget(new QLabel("% Pending", analyticsPanel), 1, 0);
    analyticsLayout->addWidget(pendingPercentValueLabel_, 1, 1);
    analyticsLayout->addWidget(new QLabel("Most Common Type", analyticsPanel), 1, 2);
    analyticsLayout->addWidget(commonTypeValueLabel_, 1, 3);
    analyticsLayout->addWidget(new QLabel("Avg Resolution Time", analyticsPanel), 2, 0);
    analyticsLayout->addWidget(avgResolutionValueLabel_, 2, 1);
    analyticsLayout->addWidget(statusSuggestionLabel_, 2, 2, 1, 2);
    analyticsLayout->addWidget(new QLabel("Resolved Progress", analyticsPanel), 3, 0);
    analyticsLayout->addWidget(resolvedProgressBar_, 3, 1, 1, 3);
    analyticsLayout->addWidget(new QLabel("Pending Progress", analyticsPanel), 4, 0);
    analyticsLayout->addWidget(pendingProgressBar_, 4, 1, 1, 3);
    analyticsLayout->addWidget(statusBadgeLabel_, 5, 0, 1, 4);
    mainLayout->addWidget(analyticsPanel);

    QFrame *filterPanel = new QFrame(this);
    filterPanel->setObjectName("panel");
    QHBoxLayout *filterLayout = new QHBoxLayout(filterPanel);
    filterLayout->setContentsMargins(10, 10, 10, 10);
    filterLayout->setSpacing(8);

    searchFilterEdit_ = new QLineEdit(filterPanel);
    searchFilterEdit_->setPlaceholderText("Search by Name / Email / Phone...");

    statusFilterCombo_ = new QComboBox(filterPanel);
    statusFilterCombo_->addItems({"All Status", "pending", "in progress", "solved", "rejected"});

    typeFilterCombo_ = new QComboBox(filterPanel);
    typeFilterCombo_->addItems({"All Types", "Illegal Dumping", "Garbage Overflow", "Missed Waste Collection", "Recycling Issue"});

    fromDateFilterEdit_ = new QDateEdit(filterPanel);
    fromDateFilterEdit_->setDisplayFormat("yyyy-MM-dd");
    fromDateFilterEdit_->setCalendarPopup(true);
    fromDateFilterEdit_->setDate(QDate::currentDate().addYears(-5));

    toDateFilterEdit_ = new QDateEdit(filterPanel);
    toDateFilterEdit_->setDisplayFormat("yyyy-MM-dd");
    toDateFilterEdit_->setCalendarPopup(true);
    toDateFilterEdit_->setDate(QDate::currentDate().addYears(1));

    smartSortButton_ = new QPushButton("Smart Sort by Priority", filterPanel);
    deleteButton_ = new QPushButton("Delete Selected", filterPanel);

    filterLayout->addWidget(searchFilterEdit_, 2);
    filterLayout->addWidget(statusFilterCombo_);
    filterLayout->addWidget(typeFilterCombo_);
    filterLayout->addWidget(fromDateFilterEdit_);
    filterLayout->addWidget(toDateFilterEdit_);
    filterLayout->addWidget(smartSortButton_);
    filterLayout->addWidget(deleteButton_);
    mainLayout->addWidget(filterPanel);

    QTabWidget *workspaceTabs = new QTabWidget(this);
    workspaceTabs->setDocumentMode(true);
    workspaceTabs->setStyleSheet(
        "QTabWidget::pane { border: 1px solid #00ff9c; border-radius: 8px; }"
        "QTabBar::tab { background: #0a1f18; color: #66ffcc; padding: 8px 16px; margin-right: 4px; }"
        "QTabBar::tab:selected { background: #00ff9c; color: #050d0a; font-weight: 700; }");

    QWidget *reportsTab = new QWidget(workspaceTabs);
    QVBoxLayout *reportsTabLayout = new QVBoxLayout(reportsTab);
    reportsTabLayout->setContentsMargins(8, 8, 8, 8);

    reportsTable_ = new QTableWidget(reportsTab);
    reportsTable_->setColumnCount(9);
    reportsTable_->setHorizontalHeaderLabels({
        "Report ID", "Customer", "Email", "Type", "Status", "Date", "Days", "Priority", "Flags"
    });
    reportsTable_->setSelectionBehavior(QAbstractItemView::SelectRows);
    reportsTable_->setSelectionMode(QAbstractItemView::SingleSelection);
    reportsTable_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    reportsTable_->horizontalHeader()->setStretchLastSection(true);
    reportsTable_->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    reportsTable_->setMinimumHeight(320);
    reportsTabLayout->addWidget(reportsTable_);

    QWidget *chatTab = new QWidget(workspaceTabs);
    QVBoxLayout *chatTabLayout = new QVBoxLayout(chatTab);
    chatTabLayout->setContentsMargins(8, 8, 8, 8);

    QFrame *chatPanel = new QFrame(chatTab);
    chatPanel->setObjectName("panel");
    chatPanel->setMinimumHeight(220);
    chatPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *chatLayout = new QVBoxLayout(chatPanel);
    chatLayout->setContentsMargins(10, 10, 10, 10);
    chatLayout->setSpacing(8);

    QHBoxLayout *actionLayout = new QHBoxLayout();
    priorityButton_ = new QPushButton("Priority Analysis", chatPanel);
    predictiveButton_ = new QPushButton("Predictive Analytics", chatPanel);
    priorityButton_->setMinimumHeight(36);
    predictiveButton_->setMinimumHeight(36);
    actionLayout->addWidget(priorityButton_);
    actionLayout->addWidget(predictiveButton_);
    chatLayout->addLayout(actionLayout);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    messageInput_ = new QLineEdit(chatPanel);
    messageInput_->setPlaceholderText("Type your message here...");
    sendButton_ = new QPushButton("Send", chatPanel);
    sendButton_->setObjectName("primaryBtn");
    sendButton_->setMinimumHeight(36);
    inputLayout->addWidget(messageInput_);
    inputLayout->addWidget(sendButton_);
    chatLayout->addLayout(inputLayout);

    chatDisplay_ = new QTextEdit(chatPanel);
    chatDisplay_->setReadOnly(true);
    chatDisplay_->setMinimumHeight(180);
    chatDisplay_->setLineWrapMode(QTextEdit::WidgetWidth);
    chatDisplay_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chatLayout->addWidget(chatDisplay_, 1);

    chatLayout->setStretch(0, 0);
    chatLayout->setStretch(1, 0);
    chatLayout->setStretch(2, 1);

    chatTabLayout->addWidget(chatPanel);

    workspaceTabs->addTab(reportsTab, "Reports Overview");
    workspaceTabs->addTab(chatTab, "AI Chat");
    workspaceTabs->setCurrentIndex(1);

    mainLayout->addWidget(workspaceTabs, 1);
    messageInput_->setFocus();

    connect(sendButton_, &QPushButton::clicked, this, &AdvancedFeatures::onSendMessage);
    connect(messageInput_, &QLineEdit::returnPressed, this, &AdvancedFeatures::onSendMessage);
    connect(priorityButton_, &QPushButton::clicked, this, &AdvancedFeatures::onShowPriorityAnalysis);
    connect(predictiveButton_, &QPushButton::clicked, this, &AdvancedFeatures::onShowPredictiveAnalysis);
    connect(searchFilterEdit_, &QLineEdit::textChanged, this, &AdvancedFeatures::onFilterChanged);
    connect(statusFilterCombo_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AdvancedFeatures::onFilterChanged);
    connect(typeFilterCombo_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AdvancedFeatures::onFilterChanged);
    connect(fromDateFilterEdit_, &QDateEdit::dateChanged, this, &AdvancedFeatures::onFilterChanged);
    connect(toDateFilterEdit_, &QDateEdit::dateChanged, this, &AdvancedFeatures::onFilterChanged);
    connect(smartSortButton_, &QPushButton::clicked, this, &AdvancedFeatures::onSmartSortByPriority);
    connect(deleteButton_, &QPushButton::clicked, this, &AdvancedFeatures::onDeleteSelectedReport);
    connect(reportsTable_, &QTableWidget::itemSelectionChanged, this, [this]() {
        const int row = reportsTable_->currentRow();
        if (row < 0) {
            statusSuggestionLabel_->setText("Suggested Status: -");
            return;
        }
        const int id = reportsTable_->item(row, 0) ? reportsTable_->item(row, 0)->text().toInt() : -1;
        for (const Customer &c : customers_) {
            if (c.customerId() == id) {
                statusSuggestionLabel_->setText("Suggested Status: " + suggestedStatusFor(c));
                break;
            }
        }
    });
}

void AdvancedFeatures::onFilterChanged()
{
    refreshDashboardAndTable();
}

void AdvancedFeatures::onSmartSortByPriority()
{
    prioritySortEnabled_ = !prioritySortEnabled_;
    smartSortButton_->setText(prioritySortEnabled_ ? "Smart Sort: ON" : "Smart Sort by Priority");
    refreshReportsTable();
}

void AdvancedFeatures::onDeleteSelectedReport()
{
    const int row = reportsTable_->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Delete Report", "Select a report first.");
        return;
    }

    const int id = reportsTable_->item(row, 0) ? reportsTable_->item(row, 0)->text().toInt() : -1;
    Customer selected;
    bool found = false;
    for (const Customer &c : customers_) {
        if (c.customerId() == id) {
            selected = c;
            found = true;
            break;
        }
    }
    if (!found) {
        QMessageBox::warning(this, "Delete Report", "Unable to find selected report.");
        return;
    }

    QString details = QString("ID: %1\nName: %2\nEmail: %3\nType: %4\nStatus: %5\nDate: %6")
                          .arg(selected.customerId())
                          .arg(selected.name())
                          .arg(selected.email())
                          .arg(selected.reportType())
                          .arg(selected.status())
                          .arg(selected.reportDate().toString("yyyy-MM-dd"));

    const auto confirm = QMessageBox::question(this,
                                               "Confirm Delete",
                                               "Delete this report?\n\n" + details,
                                               QMessageBox::Yes | QMessageBox::No,
                                               QMessageBox::No);
    if (confirm != QMessageBox::Yes) {
        return;
    }

    QString error;
    if (!Customer::remove(selected.customerId(), &error)) {
        QMessageBox::warning(this, "Delete Report", "Failed to delete report.\n" + error);
        return;
    }

    customers_.erase(std::remove_if(customers_.begin(), customers_.end(), [id](const Customer &c) {
                         return c.customerId() == id;
                     }),
                     customers_.end());

    refreshDashboardAndTable();
    QMessageBox::information(this, "Delete Report", "Report deleted successfully.");
}

void AdvancedFeatures::onAutoExportCsvBackup()
{
    const QString filePath = QString("reports_backup_%1.csv").arg(QDate::currentDate().toString("yyyyMMdd"));
    writeCsvBackup(filePath);
}

void AdvancedFeatures::writeCsvBackup(const QString &filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << "customer_id,name,email,phone,address,report_type,report_date,status,priority\n";
    for (const Customer &c : customers_) {
        out << c.customerId() << ","
            << '"' << c.name().replace('"', "''") << "\","
            << '"' << c.email().replace('"', "''") << "\","
            << '"' << c.phone().replace('"', "''") << "\","
            << '"' << c.address().replace('"', "''") << "\","
            << '"' << c.reportType().replace('"', "''") << "\","
            << c.reportDate().toString("yyyy-MM-dd") << ","
            << normalizeStatus(c.status()) << ","
            << calculatePriorityLevel(c)
            << "\n";
    }
}

void AdvancedFeatures::refreshDashboardAndTable()
{
    g_autoExportCustomers = customers_;
    refreshStatisticsPanel();
    refreshStatusBadges();
    refreshReportsTable();
}

void AdvancedFeatures::refreshStatisticsPanel()
{
    const QList<Customer> filtered = getFilteredCustomers();
    const int total = filtered.size();
    int resolved = 0;
    int pending = 0;

    QMap<QString, int> typeCounts;
    int solvedDaysTotal = 0;
    int solvedCount = 0;

    for (const Customer &c : filtered) {
        const QString status = normalizeStatus(c.status());
        if (status == "solved") {
            ++resolved;
            solvedDaysTotal += calculateReportAgeDays(c);
            ++solvedCount;
        }
        if (status == "pending") {
            ++pending;
        }
        typeCounts[c.reportType()]++;
    }

    const int resolvedPct = total > 0 ? (resolved * 100) / total : 0;
    const int pendingPct = total > 0 ? (pending * 100) / total : 0;

    QString commonType = "-";
    int bestCount = -1;
    for (auto it = typeCounts.begin(); it != typeCounts.end(); ++it) {
        if (it.value() > bestCount) {
            bestCount = it.value();
            commonType = it.key();
        }
    }

    const double avgResolution = solvedCount > 0 ? static_cast<double>(solvedDaysTotal) / solvedCount : 0.0;

    totalReportsValueLabel_->setText(QString::number(total));
    resolvedPercentValueLabel_->setText(QString::number(resolvedPct) + "%");
    pendingPercentValueLabel_->setText(QString::number(pendingPct) + "%");
    commonTypeValueLabel_->setText(commonType);
    avgResolutionValueLabel_->setText(QString::number(avgResolution, 'f', 1) + " day(s)");
    resolvedProgressBar_->setValue(resolvedPct);
    pendingProgressBar_->setValue(pendingPct);
}

void AdvancedFeatures::refreshStatusBadges()
{
    int pending = 0;
    int inProgress = 0;
    int solved = 0;
    int rejected = 0;

    for (const Customer &c : customers_) {
        const QString s = normalizeStatus(c.status());
        if (s == "pending") {
            ++pending;
        } else if (s == "in progress") {
            ++inProgress;
        } else if (s == "solved") {
            ++solved;
        } else if (s == "rejected") {
            ++rejected;
        }
    }

    statusBadgeLabel_->setText(QString("Pending (%1)   In Progress (%2)   Solved (%3)   Rejected (%4)")
                                   .arg(pending)
                                   .arg(inProgress)
                                   .arg(solved)
                                   .arg(rejected));
}

QList<Customer> AdvancedFeatures::getFilteredCustomers() const
{
    QList<Customer> filtered;
    const QString text = searchFilterEdit_->text().trimmed();
    const QString statusFilter = statusFilterCombo_->currentText();
    const QString typeFilter = typeFilterCombo_->currentText();
    const QDate fromDate = fromDateFilterEdit_->date();
    const QDate toDate = toDateFilterEdit_->date();

    for (const Customer &c : customers_) {
        const QString status = normalizeStatus(c.status());
        const bool searchOk = text.isEmpty()
                              || QString::number(c.customerId()).contains(text, Qt::CaseInsensitive)
                              || c.name().contains(text, Qt::CaseInsensitive)
                              || c.email().contains(text, Qt::CaseInsensitive)
                              || c.phone().contains(text, Qt::CaseInsensitive);

        const bool statusOk = (statusFilter == "All Status") || (status == statusFilter);
        const bool typeOk = (typeFilter == "All Types") || (c.reportType() == typeFilter);

        bool dateOk = true;
        if (c.reportDate().isValid()) {
            dateOk = (c.reportDate() >= fromDate && c.reportDate() <= toDate);
        }

        if (searchOk && statusOk && typeOk && dateOk) {
            filtered.append(c);
        }
    }

    return filtered;
}

bool AdvancedFeatures::isDuplicateCustomer(const Customer &customer) const
{
    int sameName = 0;
    int sameEmail = 0;
    for (const Customer &c : customers_) {
        if (c.name().compare(customer.name(), Qt::CaseInsensitive) == 0) {
            ++sameName;
        }
        if (c.email().compare(customer.email(), Qt::CaseInsensitive) == 0) {
            ++sameEmail;
        }
    }
    return sameName > 1 || sameEmail > 1;
}

bool AdvancedFeatures::isBlacklistedCustomer(const Customer &customer) const
{
    int rejectedCount = 0;
    for (const Customer &c : customers_) {
        const bool sameIdentity = c.name().compare(customer.name(), Qt::CaseInsensitive) == 0
                                  || c.email().compare(customer.email(), Qt::CaseInsensitive) == 0;
        if (sameIdentity && normalizeStatus(c.status()) == "rejected") {
            ++rejectedCount;
        }
    }
    return rejectedCount > 3;
}

void AdvancedFeatures::refreshReportsTable()
{
    QList<Customer> rows = getFilteredCustomers();
    if (prioritySortEnabled_) {
        std::sort(rows.begin(), rows.end(), [this](const Customer &a, const Customer &b) {
            auto rank = [this](const Customer &c) {
                const QString status = normalizeStatus(c.status());
                if (status == "solved") {
                    return 5;
                }
                const QString p = calculatePriorityLevel(c);
                if (p == "CRITICAL") return 0;
                if (p == "HIGH") return 1;
                if (p == "MEDIUM") return 2;
                return 3;
            };
            const int ra = rank(a);
            const int rb = rank(b);
            if (ra != rb) {
                return ra < rb;
            }
            return calculateReportAgeDays(a) > calculateReportAgeDays(b);
        });
    }

    reportsTable_->setRowCount(0);
    for (int i = 0; i < rows.size(); ++i) {
        const Customer &c = rows.at(i);
        const QString status = normalizeStatus(c.status());
        const QString priority = calculatePriorityLevel(c);

        QString flags;
        if (isDuplicateCustomer(c)) {
            flags += "[DUPLICATE] ";
        }
        if (isBlacklistedCustomer(c)) {
            flags += "[BLACKLIST]";
        }

        reportsTable_->insertRow(i);
        const QStringList cells = {
            QString::number(c.customerId()),
            c.name(),
            c.email(),
            c.reportType(),
            status,
            c.reportDate().isValid() ? c.reportDate().toString("yyyy-MM-dd") : "N/A",
            QString::number(calculateReportAgeDays(c)),
            priority,
            flags.trimmed()
        };

        QColor rowColor = QColor("#0b1713");
        if (status == "pending") {
            rowColor = QColor("#451a1d");
        } else if (status == "in progress") {
            rowColor = QColor("#4b3f14");
        } else if (status == "solved") {
            rowColor = QColor("#143d2a");
        } else if (status == "rejected") {
            rowColor = QColor("#2d3035");
        }

        const bool needsWarning = isDuplicateCustomer(c) || isBlacklistedCustomer(c);
        for (int col = 0; col < cells.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(cells.at(col));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            item->setBackground(rowColor);
            item->setForeground(QBrush(Qt::white));
            if (col == 8 && needsWarning) {
                item->setIcon(style()->standardIcon(QStyle::SP_MessageBoxWarning));
            }
            reportsTable_->setItem(i, col, item);
        }
    }
}

QString AdvancedFeatures::suggestedStatusFor(const Customer &customer) const
{
    const QString current = normalizeStatus(customer.status());
    if (current == "solved") {
        return "solved";
    }

    const int age = calculateReportAgeDays(customer);
    if (customer.reportType() == "Illegal Dumping" && age > 1) {
        return "in progress";
    }
    if (age > 7) {
        return "in progress";
    }
    if (age <= 2) {
        return "pending";
    }
    return current;
}

void AdvancedFeatures::showOverduePendingAlert()
{
    QStringList overdueLines;
    for (const Customer &c : customers_) {
        const QString status = normalizeStatus(c.status());
        const int age = calculateReportAgeDays(c);
        if (status == "pending" && age > overdueThresholdDays_) {
            overdueLines << QString("Report #%1 pending for %2 day(s)").arg(c.customerId()).arg(age);
        }
    }

    if (overdueLines.isEmpty()) {
        return;
    }

    QMessageBox::warning(this,
                         "Overdue Pending Alert",
                         QString("%1 overdue pending report(s) found:\n\n%2")
                             .arg(overdueLines.size())
                             .arg(overdueLines.mid(0, 10).join("\n")));
}

void AdvancedFeatures::addMessage(const QString &message, bool isUser)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm");
    QString formattedMessage;

    if (isUser) {
        formattedMessage = QString(
                               "<div style='text-align: right; margin: 10px;'>"
                               "<span style='background-color: #00ff9c; color: #050d0a; padding: 8px 12px; "
                               "border-radius: 10px; display: inline-block;'>"
                               "<b>You:</b> %1</span>"
                               "<br><small style='color: #4d9977;'>%2</small>"
                               "</div>"
                               ).arg(message, timestamp);
    } else {
        formattedMessage = QString(
                               "<div style='text-align: left; margin: 10px;'>"
                               "<span style='background-color: #0a1f18; color: #66ffcc; padding: 8px 12px; "
                               "border-radius: 10px; border: 1px solid #00ff9c; display: inline-block;'>"
                               "<b>AI:</b> %1</span>"
                               "<br><small style='color: #4d9977;'>%2</small>"
                               "</div>"
                               ).arg(message, timestamp);
    }

    chatDisplay_->append(formattedMessage);
}

void AdvancedFeatures::onSendMessage()
{
    QString message = messageInput_->text().trimmed();
    if (message.isEmpty()) {
        return;
    }

    addMessage(message, true);
    messageInput_->clear();

    QString response = processUserMessage(message);
    addMessage(response, false);
}

QString AdvancedFeatures::processUserMessage(const QString &message)
{
    QString lowerMsg = message.toLower();

    // Improvement 4: quick status counters for natural chat questions.
    int pendingCount = 0;
    int inProgressCount = 0;
    int rejectedCount = 0;
    int solvedCount = 0;

    for (const Customer &c : customers_) {
        const QString normalized = normalizeStatus(c.status());
        if (normalized == "pending") {
            ++pendingCount;
        } else if (normalized == "in progress") {
            ++inProgressCount;
        } else if (normalized == "rejected") {
            ++rejectedCount;
        } else if (normalized == "solved") {
            ++solvedCount;
        }
    }

    if (lowerMsg.contains("solved") || lowerMsg.contains("resolved")) {
        return QString("<b>Solved Reports:</b> %1<br>"
                       "These are completed reports that no longer need action.")
            .arg(solvedCount);
    }

    if (lowerMsg.contains("rejected")) {
        return QString("<b>Rejected Reports:</b> %1<br>"
                       "Rejected reports usually need corrected details before resubmission.")
            .arg(rejectedCount);
    }

    if (lowerMsg.contains("in progress") || lowerMsg.contains("inprogress")) {
        return QString("<b>In Progress Reports:</b> %1<br>"
                       "These reports are currently being handled by the operations team.")
            .arg(inProgressCount);
    }

    if (lowerMsg.contains("how many") || lowerMsg.contains("total") || lowerMsg.contains("count")) {
        return QString("<b>Total Reports:</b> %1<br><br>"
                       "Pending: %2<br>"
                       "In Progress: %3<br>"
                       "Rejected: %4<br>"
                       "Solved: %5")
            .arg(customers_.size())
            .arg(pendingCount)
            .arg(inProgressCount)
            .arg(rejectedCount)
            .arg(solvedCount);
    }

    if (lowerMsg.contains("show critical reports") || lowerMsg.contains("critical reports")) {
        QString response = "<b>Critical Reports:</b><br>";
        int found = 0;
        for (const Customer &c : customers_) {
            if (calculatePriorityLevel(c) == "CRITICAL" && normalizeStatus(c.status()) != "solved") {
                response += QString("- #%1 %2 (%3 day(s))<br>")
                .arg(c.customerId())
                    .arg(c.reportType())
                    .arg(calculateReportAgeDays(c));
                ++found;
            }
        }
        if (found == 0) {
            response += "No active critical reports.";
        }
        return response;
    }

    // Predictive analytics queries
    if (lowerMsg.contains("predict") || lowerMsg.contains("forecast") ||
        lowerMsg.contains("next week") || lowerMsg.contains("future") ||
        lowerMsg.contains("trend") || lowerMsg.contains("upcoming")) {
        return generatePredictiveAnalysis();
    }

    // Escalation queries
    if (lowerMsg.contains("escalat") || lowerMsg.contains("risk") ||
        lowerMsg.contains("critical soon") || lowerMsg.contains("watch")) {
        return getEscalationRisks();
    }

    // Recommendation queries
    if (lowerMsg.contains("recommend") || lowerMsg.contains("suggest") ||
        lowerMsg.contains("action") || lowerMsg.contains("what should")) {
        return generateActionableRecommendations();
    }

    // Priority-related queries
    if (lowerMsg.contains("priority") || lowerMsg.contains("urgent") ||
        lowerMsg.contains("important") || lowerMsg.contains("critical") ||
        lowerMsg.contains("analysis") || lowerMsg.contains("overview")) {
        return generatePriorityAnalysis();
    }

    // Report type queries
    if (lowerMsg.contains("illegal") || lowerMsg.contains("dumping")) {
        return "🚨 <b>Illegal Dumping</b> reports are classified as <span style='color: #ff4444;'><b>HIGH PRIORITY</b></span>.<br><br>"
               "These require immediate attention due to environmental and legal implications. "
               "Average resolution time should be within 24-48 hours.";
    }

    if (lowerMsg.contains("overflow") || lowerMsg.contains("garbage")) {
        return "⚠️ <b>Garbage Overflow</b> reports are classified as <span style='color: #ffaa00;'><b>MEDIUM-HIGH PRIORITY</b></span>.<br><br>"
               "These need prompt attention to prevent health hazards and public complaints. "
               "Recommended resolution within 48-72 hours.";
    }

    if (lowerMsg.contains("missed") || lowerMsg.contains("collection")) {
        return "📋 <b>Missed Waste Collection</b> reports are classified as <span style='color: #ffcc00;'><b>MEDIUM PRIORITY</b></span>.<br><br>"
               "These should be scheduled for the next collection cycle. "
               "Standard resolution time is 24-48 hours.";
    }

    if (lowerMsg.contains("recycling") || lowerMsg.contains("recycle")) {
        return "♻️ <b>Recycling Issues</b> are classified as <span style='color: #00cc66;'><b>NORMAL PRIORITY</b></span>.<br><br>"
               "These can be addressed during regular operational hours. "
               "Resolution time typically within 3-5 business days.";
    }

    // Help query
    if (lowerMsg.contains("help") || lowerMsg.contains("what can you do")) {
        return "I can help you with:<br><br>"
               "&#128202; <b>Priority Analysis</b> - Current report priorities<br>"
               "&#128302; <b>Predictive Analytics</b> - Forecast next week's reports<br>"
               "&#9888; <b>Escalation Risks</b> - Reports likely to become critical<br>"
               "&#128203; <b>Recommendations</b> - Actionable admin suggestions<br>"
               "&#128230; <b>Report Types</b> - Info about specific report types<br><br>"
               "Try asking: 'What reports are predicted for next week?' or 'Show escalation risks'";
    }

    // Default response
    return "I understand you're asking about: <i>" + message + "</i><br><br>"
                                                               "I can help with:<br>"
                                                               "- Priority detection for reports<br>"
                                                               "- Predictive analytics and trends<br>"
                                                               "- Escalation risk assessment<br>"
                                                               "- Actionable recommendations<br><br>"
                                                               "Try the <b>Predictive Analytics</b> button!";
}

QString AdvancedFeatures::getPriorityForReportType(const QString &reportType)
{
    if (reportType == "Illegal Dumping") {
        return "<span style='color:#ff4444;'>&#9679;</span> CRITICAL";
    } else if (reportType == "Garbage Overflow") {
        return "<span style='color:#ffaa00;'>&#9679;</span> HIGH";
    } else if (reportType == "Missed Waste Collection") {
        return "<span style='color:#ffcc00;'>&#9679;</span> MEDIUM";
    } else if (reportType == "Recycling Issue") {
        return "<span style='color:#00cc66;'>&#9679;</span> LOW";
    }
    return "<span style='color:#ffffff;'>&#9679;</span> UNCLASSIFIED";
}

void AdvancedFeatures::onShowPriorityAnalysis()
{
    addMessage("Show me the priority analysis", true);
    addMessage(generatePriorityAnalysis(), false);
}

QString AdvancedFeatures::generatePriorityAnalysis()
{
    QString analysis = "<b>&#127919; AI PRIORITY DETECTION ANALYSIS</b><br><br>";
    analysis += QString("Total Reports: <b>%1</b><br><br>").arg(customers_.size());

    if (customers_.isEmpty()) {
        return analysis + "<i>No reports available for scoring.</i>";
    }

    // Improvement 1 + 2: score each report and apply date-based CRITICAL override.
    QMap<QString, int> levelCounts;
    levelCounts["CRITICAL"] = 0;
    levelCounts["HIGH"] = 0;
    levelCounts["MEDIUM"] = 0;
    levelCounts["LOW"] = 0;

    analysis += "<b>Per-Report Priority Scores</b><br>";
    analysis += "<table style='width: 100%; margin-top: 10px; border-collapse: collapse;'>";
    analysis += "<tr style='background-color: #0a1f18;'>"
                "<th style='text-align:left; padding: 8px;'>Customer</th>"
                "<th style='text-align:left; padding: 8px;'>Type</th>"
                "<th style='text-align:left; padding: 8px;'>Status</th>"
                "<th style='text-align:left; padding: 8px;'>Age</th>"
                "<th style='text-align:left; padding: 8px;'>Priority</th>"
                "</tr>";

    for (const Customer &c : customers_) {
        const int score = calculatePriorityScore(c);
        const int daysOld = calculateReportAgeDays(c);
        const QString level = calculatePriorityLevel(c);
        const QString levelColor = getPriorityColor(level);
        const QString levelIcon = getPriorityIcon(level);
        const QString statusNormalized = normalizeStatus(c.status());
        const QString statusDisplay = statusNormalized == "in progress"
                                          ? "In Progress"
                                          : QString(statusNormalized).replace(0, 1, statusNormalized.left(1).toUpper());

        levelCounts[level]++;

        analysis += QString("<tr>"
                            "<td style='padding: 8px;'>#%1 %2</td>"
                            "<td style='padding: 8px;'>%3</td>"
                            "<td style='padding: 8px;'>%4</td>"
                            "<td style='padding: 8px;'>%5 day(s)</td>"
                            "<td style='padding: 8px; color:%6;'><b>Score: %7/100 %8 %9</b></td>"
                            "</tr>")
                        .arg(c.customerId())
                        .arg(c.name())
                        .arg(c.reportType())
                        .arg(statusDisplay)
                        .arg(daysOld)
                        .arg(levelColor)
                        .arg(score)
                        .arg(levelIcon)
                        .arg(level);
    }
    analysis += "</table><br>";

    // Improvement 3: visual priority bars in QTextEdit HTML.
    analysis += "<b>Priority Distribution</b><br>";

    auto addBar = [&](const QString &label, const QString &color, int count) {
        const double pct = (100.0 * count) / customers_.size();
        analysis += QString("<div style='margin: 8px 0;'>"
                            "<div><b>%1:</b> %2 (%3%)</div>"
                            "<div style='width: 100%; background-color: #113328; border-radius: 6px; height: 16px;'>"
                            "<div style='height: 16px; width: %4%; background-color: %5; border-radius: 6px;'></div>"
                            "</div>"
                            "</div>")
                        .arg(label)
                        .arg(count)
                        .arg(QString::number(pct, 'f', 1))
                        .arg(QString::number(pct, 'f', 1))
                        .arg(color);
    };

    addBar("CRITICAL", "#ff4444", levelCounts.value("CRITICAL", 0));
    addBar("HIGH", "#ffaa00", levelCounts.value("HIGH", 0));
    addBar("MEDIUM", "#ffcc00", levelCounts.value("MEDIUM", 0));
    addBar("LOW", "#00cc66", levelCounts.value("LOW", 0));

    analysis += "<br><b>&#128203; AI Recommendations:</b><br>";
    if (levelCounts.value("CRITICAL", 0) > 0) {
        analysis += "- Dispatch emergency team for CRITICAL reports first<br>";
    }
    if (levelCounts.value("HIGH", 0) > 0) {
        analysis += "- Assign additional resources to HIGH priority reports<br>";
    }
    analysis += "- Review pending and rejected reports daily for faster closure<br>";

    return analysis;
}

// ============== PREDICTIVE ANALYTICS METHODS ==============

void AdvancedFeatures::onShowPredictiveAnalysis()
{
    addMessage("Show me predictive analytics for next week", true);
    addMessage(generatePredictiveAnalysis(), false);
}

QString AdvancedFeatures::generatePredictiveAnalysis()
{
    QString report;
    report += "<b>&#128302; AI PREDICTIVE ANALYTICS REPORT</b><br>";
    report += "<small>Forecast Period: Next 7 Days</small><br><br>";

    // Add trend analysis
    report += analyzeTrends();
    report += "<br>";

    // Add predictions
    report += predictNextWeekReports();
    report += "<br>";

    // Add escalation risks
    report += getEscalationRisks();
    report += "<br>";

    // Add recommendations
    report += generateActionableRecommendations();

    return report;
}

QString AdvancedFeatures::analyzeTrends()
{
    QMap<QString, int> typeCounts;
    QMap<QString, int> statusCounts;

    for (const Customer &c : customers_) {
        typeCounts[c.reportType()]++;
        statusCounts[normalizeStatus(c.status())]++;
    }

    QString trends = "<b>&#128200; HISTORICAL TREND ANALYSIS</b><br><br>";

    int total = customers_.size();
    if (total == 0) {
        return trends + "<i>No historical data available for trend analysis.</i><br>";
    }

    trends += "<table style='width: 100%;'>";
    trends += "<tr style='border-bottom: 1px solid #00ff9c;'><th>Report Type</th><th>Count</th><th>Trend</th></tr>";

    QStringList types = {"Illegal Dumping", "Garbage Overflow", "Missed Waste Collection", "Recycling Issue"};

    for (const QString &type : types) {
        int count = typeCounts.value(type, 0);
        int trendScore = calculateTrendScore(type);
        QString trendIndicator;

        if (trendScore > 0) {
            trendIndicator = QString("<span style='color: #ff4444;'>&#8593; +%1%</span>").arg(trendScore);
        } else if (trendScore < 0) {
            trendIndicator = QString("<span style='color: #00cc66;'>&#8595; %1%</span>").arg(trendScore);
        } else {
            trendIndicator = "<span style='color: #ffcc00;'>&#8594; Stable</span>";
        }

        trends += QString("<tr><td>%1</td><td>%2</td><td>%3</td></tr>")
                      .arg(type).arg(count).arg(trendIndicator);
    }
    trends += "</table><br>";

    // Status breakdown
    trends += "<b>Current Status Distribution:</b><br>";
    // Improvement 6: use "Solved" everywhere to match real values.
    trends += QString("Pending: %1 | In Progress: %2 | Rejected: %3 | Solved: %4<br>")
                  .arg(statusCounts.value("pending", 0))
                  .arg(statusCounts.value("in progress", 0))
                  .arg(statusCounts.value("rejected", 0))
                  .arg(statusCounts.value("solved", 0));

    return trends;
}

int AdvancedFeatures::calculateTrendScore(const QString &reportType)
{
    // Improvement 5: trend score now uses real status mix for each report type.
    int pending = 0;
    int inProgress = 0;
    int solved = 0;

    for (const Customer &c : customers_) {
        if (c.reportType() != reportType) {
            continue;
        }

        const QString status = normalizeStatus(c.status());
        if (status == "pending") {
            ++pending;
        } else if (status == "in progress") {
            ++inProgress;
        } else if (status == "solved") {
            ++solved;
        }
    }

    int score = (pending * 10) + (inProgress * 5) - (solved * 8);
    return qBound(-30, score, 30);
}

QString AdvancedFeatures::predictNextWeekReports()
{
    QMap<QString, int> typeCounts;
    for (const Customer &c : customers_) {
        typeCounts[c.reportType()]++;
    }

    QString prediction = "<b>&#128202; PREDICTED REPORTS - NEXT 7 DAYS</b><br><br>";

    prediction += "<table style='width: 100%; border-collapse: collapse;'>";
    prediction += "<tr style='background-color: #0a1f18;'>";
    prediction += "<th style='padding: 8px; text-align: left;'>Report Type</th>";
    prediction += "<th style='padding: 8px;'>Predicted Count</th>";
    prediction += "<th style='padding: 8px;'>Priority Level</th>";
    prediction += "</tr>";

    // Prediction calculations based on current data patterns
    int illegalBase = typeCounts.value("Illegal Dumping", 0);
    int overflowBase = typeCounts.value("Garbage Overflow", 0);
    int missedBase = typeCounts.value("Missed Waste Collection", 0);
    int recyclingBase = typeCounts.value("Recycling Issue", 0);

    // Predicted ranges (simulated ML prediction)
    int illegalMin = qMax(1, illegalBase), illegalMax = illegalBase + 3;
    int overflowMin = qMax(2, overflowBase), overflowMax = overflowBase + 5;
    int missedMin = qMax(1, missedBase - 1), missedMax = missedBase + 2;
    int recyclingMin = qMax(0, recyclingBase - 1), recyclingMax = recyclingBase + 1;

    prediction += QString("<tr><td style='padding: 8px;'>&#128680; Illegal Dumping</td>"
                          "<td style='padding: 8px; text-align: center;'>%1 - %2</td>"
                          "<td style='padding: 8px;'><span style='color: #ff4444;'><b>CRITICAL</b></span></td></tr>")
                      .arg(illegalMin).arg(illegalMax);

    prediction += QString("<tr><td style='padding: 8px;'>&#9888; Garbage Overflow</td>"
                          "<td style='padding: 8px; text-align: center;'>%1 - %2</td>"
                          "<td style='padding: 8px;'><span style='color: #ffaa00;'><b>HIGH</b></span></td></tr>")
                      .arg(overflowMin).arg(overflowMax);

    prediction += QString("<tr><td style='padding: 8px;'>&#128203; Missed Waste Collection</td>"
                          "<td style='padding: 8px; text-align: center;'>%1 - %2</td>"
                          "<td style='padding: 8px;'><span style='color: #ffcc00;'><b>MEDIUM</b></span></td></tr>")
                      .arg(missedMin).arg(missedMax);

    prediction += QString("<tr><td style='padding: 8px;'>&#9851; Recycling Issues</td>"
                          "<td style='padding: 8px; text-align: center;'>%1 - %2</td>"
                          "<td style='padding: 8px;'><span style='color: #00cc66;'><b>LOW</b></span></td></tr>")
                      .arg(recyclingMin).arg(recyclingMax);

    prediction += "</table><br>";

    int totalMin = illegalMin + overflowMin + missedMin + recyclingMin;
    int totalMax = illegalMax + overflowMax + missedMax + recyclingMax;
    prediction += QString("<b>Total Expected Reports:</b> %1 - %2<br>").arg(totalMin).arg(totalMax);

    return prediction;
}

QString AdvancedFeatures::getEscalationRisks()
{
    QString risks = "<b>&#9888; ESCALATION RISK ASSESSMENT</b><br><br>";

    int criticalRisk = 0;
    int highRisk = 0;
    QString rows;

    for (const Customer &c : customers_) {
        const QString status = normalizeStatus(c.status());
        if (status == "solved") {
            continue;
        }

        const QString level = calculatePriorityLevel(c);
        if (level != "CRITICAL" && level != "HIGH") {
            continue;
        }

        if (level == "CRITICAL") {
            ++criticalRisk;
        } else {
            ++highRisk;
        }

        rows += QString("<tr><td>Customer #%1</td><td>%2</td>"
                        "<td>%3 day(s) old</td>"
                        "<td><span style='color: %4;'><b>&#8594; %5</b></span></td></tr>")
                    .arg(c.customerId())
                    .arg(c.reportType())
                    .arg(calculateReportAgeDays(c))
                    .arg(getPriorityColor(level))
                    .arg(level);
    }

    if (criticalRisk == 0 && highRisk == 0) {
        risks += "<span style='color: #00cc66;'>&#10004; No active reports at risk of escalation.</span><br>";
        return risks;
    }

    risks += "<b>Reports Likely to Escalate:</b><br>";
    risks += "<table style='width: 100%;'>";
    risks += rows;
    risks += "</table><br>";

    if (criticalRisk > 0) {
        risks += QString("&#128680; <span style='color: #ff4444;'><b>%1 report(s)</b> at CRITICAL escalation risk!</span><br>").arg(criticalRisk);
    }
    if (highRisk > 0) {
        risks += QString("&#9888; <span style='color: #ffaa00;'><b>%1 report(s)</b> at HIGH escalation risk!</span><br>").arg(highRisk);
    }

    return risks;
}

QString AdvancedFeatures::generateActionableRecommendations()
{
    QString recs = "<b>&#128203; ACTIONABLE RECOMMENDATIONS FOR ADMINISTRATORS</b><br><br>";

    QMap<QString, int> pendingByType;
    int agedCritical = 0;

    for (const Customer &c : customers_) {
        const QString status = normalizeStatus(c.status());
        if (status == "pending") {
            pendingByType[c.reportType()]++;
        }

        // Improvement 2 reflected in recommendations.
        if (calculatePriorityLevel(c) == "CRITICAL" &&
            normalizeStatus(c.status()) != "solved" &&
            calculateReportAgeDays(c) > 7) {
            ++agedCritical;
        }
    }

    int illegalPending = pendingByType.value("Illegal Dumping", 0);
    int overflowPending = pendingByType.value("Garbage Overflow", 0);
    int missedPending = pendingByType.value("Missed Waste Collection", 0);

    recs += "<b>&#127919; Immediate Actions Required:</b><br>";
    recs += "<table style='width: 100%;'>";

    if (illegalPending > 0) {
        recs += QString("<tr><td>&#128680;</td><td><b>URGENT:</b> Dispatch emergency cleanup team for %1 Illegal Dumping case(s)</td></tr>").arg(illegalPending);
    }

    if (agedCritical > 0) {
        recs += QString("<tr><td>&#9200;</td><td><b>URGENT:</b> %1 report(s) older than 7 days are auto-marked CRITICAL. Escalate immediately.</td></tr>").arg(agedCritical);
    }

    if (overflowPending > 0) {
        recs += QString("<tr><td>&#9888;</td><td><b>HIGH:</b> Schedule additional collection routes for %1 Garbage Overflow area(s)</td></tr>").arg(overflowPending);
    }

    if (missedPending > 0) {
        recs += QString("<tr><td>&#128203;</td><td><b>MEDIUM:</b> Add %1 address(es) to priority pickup list</td></tr>").arg(missedPending);
    }

    recs += "</table><br>";

    recs += "<b>&#128197; Proactive Measures for Next Week:</b><br>";
    recs += "- Increase patrol frequency in areas with recent Illegal Dumping reports<br>";
    recs += "- Pre-position overflow containers in high-volume zones<br>";
    recs += "- Send reminder notifications to customers with pending collections<br>";
    recs += "- Review staffing levels for predicted report volume<br><br>";

    recs += "<b>&#128202; Monitoring Priorities:</b><br>";
    recs += "- Review all Pending reports daily for status changes<br>";
    recs += "- Monitor Illegal Dumping hotspots via scheduled inspections<br>";
    recs += "- Track resolution times to identify process bottlenecks<br>";

    return recs;
}

QString AdvancedFeatures::getPriorityColor(const QString &priority)
{
    if (priority == "CRITICAL") return "#ff4444";
    if (priority == "HIGH") return "#ffaa00";
    if (priority == "MEDIUM") return "#ffcc00";
    if (priority == "LOW") return "#00cc66";
    return "#ffffff";
}

int AdvancedFeatures::calculatePriorityScore(const Customer &customer) const
{
    // Improvement 1: numeric score system (0-100) from type + status + age weights.
    int typeWeight = 0;
    if (customer.reportType() == "Illegal Dumping") {
        typeWeight = 50;
    } else if (customer.reportType() == "Garbage Overflow") {
        typeWeight = 35;
    } else if (customer.reportType() == "Missed Waste Collection") {
        typeWeight = 20;
    } else if (customer.reportType() == "Recycling Issue") {
        typeWeight = 10;
    }

    const QString status = normalizeStatus(customer.status());
    int statusWeight = 0;
    if (status == "pending") {
        statusWeight = 30;
    } else if (status == "in progress") {
        statusWeight = 15;
    } else if (status == "rejected") {
        statusWeight = 20;
    } else if (status == "solved") {
        statusWeight = 0;
    }

    const int daysOld = calculateReportAgeDays(customer);
    int ageWeight = 0;
    if (daysOld > 7) {
        ageWeight = 20;
    } else if (daysOld > 3) {
        ageWeight = 10;
    }

    return qBound(0, typeWeight + statusWeight + ageWeight, 100);
}

int AdvancedFeatures::calculateReportAgeDays(const Customer &customer) const
{
    if (!customer.reportDate().isValid()) {
        return 0;
    }

    const int days = customer.reportDate().daysTo(QDate::currentDate());
    return days < 0 ? 0 : days;
}

QString AdvancedFeatures::calculatePriorityLevel(const Customer &customer) const
{
    const QString status = normalizeStatus(customer.status());
    const int daysOld = calculateReportAgeDays(customer);

    // Improvement 2: force CRITICAL when older than 7 days and not solved.
    if (daysOld > 7 && status != "solved") {
        return "CRITICAL";
    }

    const int score = calculatePriorityScore(customer);
    if (score >= 75) {
        return "CRITICAL";
    }
    if (score >= 50) {
        return "HIGH";
    }
    if (score >= 25) {
        return "MEDIUM";
    }
    return "LOW";
}

QString AdvancedFeatures::normalizeStatus(const QString &status) const
{
    QString normalized = status.trimmed().toLower();

    // Improvement 6: map any legacy "resolved" value to "solved".
    if (normalized == "resolved") {
        return "solved";
    }
    if (normalized == "inprogress") {
        return "in progress";
    }
    return normalized;
}

QString AdvancedFeatures::getPriorityIcon(const QString &priority) const
{
    if (priority == "CRITICAL") return "🔴";
    if (priority == "HIGH") return "🟠";
    if (priority == "MEDIUM") return "🟡";
    return "🟢";
}
