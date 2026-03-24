#ifndef ADVANCEDFEATURES_H
#define ADVANCEDFEATURES_H

#include <QDialog>
#include <QList>
#include "customer.h"

class QTextEdit;
class QLineEdit;
class QPushButton;
class QLabel;
class QComboBox;
class QDateEdit;
class QProgressBar;
class QTableWidget;
class QCloseEvent;

class AdvancedFeatures : public QDialog
{
    Q_OBJECT

public:
    explicit AdvancedFeatures(const QList<Customer> &customers, QWidget *parent = nullptr);
    ~AdvancedFeatures();

private slots:
    void onSendMessage();
    void onShowPriorityAnalysis();
    void onShowPredictiveAnalysis();
    void onFilterChanged();
    void onSmartSortByPriority();
    void onDeleteSelectedReport();
    void onExportPdfWithCharts();
    void onAutoExportCsvBackup();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setupUI();
    void refreshDashboardAndTable();
    void refreshStatisticsPanel();
    void refreshReportsTable();
    void refreshStatusBadges();
    void showOverduePendingAlert();
    QList<Customer> getFilteredCustomers() const;
    QString suggestedStatusFor(const Customer &customer) const;
    bool isDuplicateCustomer(const Customer &customer) const;
    bool isBlacklistedCustomer(const Customer &customer) const;
    void writeCsvBackup(const QString &filePath) const;

    void addMessage(const QString &message, bool isUser);
    QString processUserMessage(const QString &message);
    QString getPriorityForReportType(const QString &reportType);
    QString generatePriorityAnalysis();

    // Predictive Analytics Methods
    QString generatePredictiveAnalysis();
    QString analyzeTrends();
    QString predictNextWeekReports();
    QString getEscalationRisks();
    QString generateActionableRecommendations();
    int calculateTrendScore(const QString &reportType);
    QString getPriorityColor(const QString &priority);

    // Improvement 1 + 2 helpers: numeric score and date-based critical escalation.
    int calculatePriorityScore(const Customer &customer) const;
    int calculateReportAgeDays(const Customer &customer) const;
    QString calculatePriorityLevel(const Customer &customer) const;
    QString normalizeStatus(const QString &status) const;
    QString getPriorityIcon(const QString &priority) const;

    QList<Customer> customers_;

    // UI Components
    QLabel *totalReportsValueLabel_;
    QLabel *resolvedPercentValueLabel_;
    QLabel *pendingPercentValueLabel_;
    QLabel *commonTypeValueLabel_;
    QLabel *avgResolutionValueLabel_;
    QLabel *statusBadgeLabel_;
    QLabel *statusSuggestionLabel_;

    QProgressBar *resolvedProgressBar_;
    QProgressBar *pendingProgressBar_;

    QLineEdit *searchFilterEdit_;
    QComboBox *statusFilterCombo_;
    QComboBox *typeFilterCombo_;
    QDateEdit *fromDateFilterEdit_;
    QDateEdit *toDateFilterEdit_;

    QTableWidget *reportsTable_;
    QPushButton *smartSortButton_;
    QPushButton *deleteButton_;
    QPushButton *exportPdfButton_;

    QTextEdit *chatDisplay_;
    QLineEdit *messageInput_;
    QPushButton *sendButton_;
    QPushButton *priorityButton_;
    QPushButton *predictiveButton_;
    QLabel *titleLabel_;

    bool prioritySortEnabled_;
    int overdueThresholdDays_;
};

#endif // ADVANCEDFEATURES_H
