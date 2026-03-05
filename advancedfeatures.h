#ifndef ADVANCEDFEATURES_H
#define ADVANCEDFEATURES_H

#include <QDialog>
#include <QList>
#include "customer.h"

class QTextEdit;
class QLineEdit;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;

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

private:
    void setupUI();
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

    QList<Customer> customers_;

    // UI Components
    QTextEdit *chatDisplay_;
    QLineEdit *messageInput_;
    QPushButton *sendButton_;
    QPushButton *priorityButton_;
    QPushButton *predictiveButton_;
    QLabel *titleLabel_;
};

#endif // ADVANCEDFEATURES_H
