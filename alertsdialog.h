#ifndef ALERTSDIALOG_H
#define ALERTSDIALOG_H

/*  alertsdialog.h
 *
 *  Machine Alerts & Predictions Dashboard
 *  ───────────────────────────────────────
 *  Reads Machine + machine_history and computes:
 *    1. Predicted next failure date
 *    2. Next recommended maintenance date
 *    3. Per-status duration & frequency insights
 *
 *  Tables used
 *  ───────────────────────────────────────────────────
 *    Machine        : ID_MACHINE, FULL_NAME, STATUS
 *    machine_history: machine_id, changed_at,
 *                     field_name, new_value
 */

#include <QDialog>
#include <QString>
#include <QDateTime>
#include <QLabel>
#include <QFrame>
#include <QWidget>
#include <QList>
#include <QMap>

// ─────────────────────────────────────────────────────────────────────────────
//  One recorded status transition
// ─────────────────────────────────────────────────────────────────────────────
struct StatusEvent {
    QString   status;
    QDateTime changedAt;
};

// ─────────────────────────────────────────────────────────────────────────────
//  Confidence level for the failure prediction
// ─────────────────────────────────────────────────────────────────────────────
enum class Confidence {
    Insufficient,   // 0 active→failure transitions
    Low,            // 1–2
    Medium,         // 3–4
    High            // ≥ 5
};

// ─────────────────────────────────────────────────────────────────────────────
//  All computed results — populated by computePredictions()
// ─────────────────────────────────────────────────────────────────────────────
struct PredictionResult {
    // Failure
    bool        failurePredicted        = false;
    QDateTime   predictedFailureDate;
    Confidence  failureConfidence       = Confidence::Insufficient;
    qint64      avgActiveDurationSec    = 0;
    int         activePeriodCount       = 0;

    // Maintenance
    bool        maintenancePredicted    = false;
    QDateTime   nextMaintenanceDate;
    qint64      avgMaintenanceIntervalSec = 0;
    int         maintenanceEventCount   = 0;

    // Current status
    QString     currentStatus;
    QDateTime   currentStatusStart;

    // Insights
    QMap<QString, qint64> statusDurationSec;   // status → total seconds
    QMap<QString, int>    statusCount;          // status → event count
    QString               mostFrequentStatus;
    int                   totalEvents = 0;
};

// ─────────────────────────────────────────────────────────────────────────────
//  AlertsDialog
// ─────────────────────────────────────────────────────────────────────────────
class AlertsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlertsDialog(const QString &machineId,
                          const QString &machineName,
                          QWidget       *parent = nullptr);

private slots:
    void onExportPDF();

private:
    QString          m_machineId;
    QString          m_machineName;
    PredictionResult m_result;

    // UI widgets updated in populateUi()
    QLabel  *m_lblFailureDate;
    QLabel  *m_lblFailureConfBadge;
    QLabel  *m_lblAvgActive;
    QLabel  *m_lblDataPoints;
    QLabel  *m_lblCurrentStatus;
    QLabel  *m_lblMaintenanceDate;
    QLabel  *m_lblMaintenanceCount;
    QLabel  *m_lblMaintenanceInterval;
    QWidget *m_insightsContainer;

    // Data pipeline
    QList<StatusEvent> loadStatusHistory();
    PredictionResult   computePredictions(const QList<StatusEvent> &events,
                                        const QString &fallbackStatus);
    void               populateUi();

    // UI builders
    void    buildUi();
    void    writePDF(const QString &path);
    QFrame *buildHeader();
    QFrame *buildFailureCard();
    QFrame *buildMaintenanceCard();
    QFrame *buildInsightsCard();
    QFrame *buildMethodologyCard();

    // Style helpers (same palette as MachineHistory)
    static QFrame  *makeCard(QWidget *parent = nullptr);
    static QLabel  *makeTitle(const QString &text, QWidget *parent = nullptr);
    static QLabel  *makeFieldLabel(const QString &text, QWidget *parent = nullptr);
    static QLabel  *makeValueLabel(const QString &text, QWidget *parent = nullptr);
    static QColor   statusColor(const QString &status);
    static QString  statusBadgeStyle(const QString &status);
    static QString  confidenceText(Confidence c);
    static QString  confidenceBadgeStyle(Confidence c);
    static QString  urgencyDateStyle(const QDateTime &dt);
};

#endif // ALERTSDIALOG_H