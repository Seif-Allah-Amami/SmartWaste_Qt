#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connection.h"
#include "waste.h"
<<<<<<< HEAD
=======
#include "arduinosensor.h"          // ← NEW
>>>>>>> 5be580a (waste X Arduino)

#include <QMainWindow>
#include <QDateTime>

class QLabel;
<<<<<<< HEAD

class QCloseEvent;
=======
class QCloseEvent;

>>>>>>> 5be580a (waste X Arduino)
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    struct ScheduledPickup {
        QString ticket;
        QString type;
        QString location;
        QString urgency;
        QString priority;
        QString window;
        QDateTime deadline;
    };

    void setupConnections();

    // Navigation methods
    void showLoginPage();
    void showRecoveryPage();
    void showVerificationPage();
    void showMainMenu();
    void showEmployeePage();
    void showCustomerPage();
    void showWastePage();
<<<<<<< HEAD
<<<<<<< HEAD
    void showVehiclePage();
    void showMachinePage();
    void showSupplierPage();
=======
<<<<<<< HEAD
    void showVehiclePage();
    void showMachinePage();
=======
<<<<<<< HEAD
    void showVehiclePage();
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
=======
>>>>>>> 5be580a (waste X Arduino)

    // Waste CRUD helpers
    bool initializeDatabase();
    bool ensureWasteTable();
    bool ensurePickupScheduleTable();
    void loadScheduledPickupsFromDb();
    bool saveScheduledPickupToDb(const ScheduledPickup &pickup);
    void setupWasteTable();
    void loadWasteToTable(const QList<Waste> &records);
    void applyWasteSearchAndSort();
    bool collectWasteData(Waste &waste, bool forEdit);
    bool selectedWasteId(int &id) const;

    // Waste CRUD handlers
    void onAddWasteClicked();
    void onViewWasteClicked();
    void onEditWasteClicked();
    void onDeleteWasteClicked();
    void onClearWasteClicked();
    void onExportWastePdfClicked();
    void onViewOnMapClicked();
    void onWasteStatsClicked();
    void onSmartPickupSchedulerClicked();
    void onWasteSearchChanged(const QString &text);
    void onWasteSortChanged(int index);

    // Logic methods
    void onLoginClicked();
    void onVerifyClicked();

<<<<<<< HEAD
=======
    // ── Arduino sensor helpers ────────────────────────────────────────────────
    void setupArduinoSensor();
    void onArduinoConnect();
    void onArduinoDisconnect();
    // ─────────────────────────────────────────────────────────────────────────

>>>>>>> 5be580a (waste X Arduino)
private slots:
    void on_btnClearSelection_clicked();
    void on_btnEmpClear_clicked();

<<<<<<< HEAD
private:

    QList<Waste> m_cachedWaste;
    QList<ScheduledPickup> m_scheduledPickups;
    int m_nextPickupTicket;
    bool m_databaseReady;
    Connection m_connection;  // Keep connection alive
    QLabel *m_searchHintLabel;
=======
    // ── Arduino slots ─────────────────────────────────────────────────────────
    void onArduinoConnectionChanged(bool connected);
    void onSensorAutoSave(ArduinoSensor::Reading reading);
    void onSensorDetailsClicked();
    // ─────────────────────────────────────────────────────────────────────────

private:
    QList<Waste>          m_cachedWaste;
    QList<ScheduledPickup> m_scheduledPickups;
    int                   m_nextPickupTicket;
    bool                  m_databaseReady;
    bool                  m_suppressArduinoAutoSave = false;
    Connection            m_connection;
    QLabel               *m_searchHintLabel;

    // ── Arduino members ───────────────────────────────────────────────────────
    ArduinoSensor        *m_arduino        = nullptr;
    QLabel               *m_arduinoStatus  = nullptr;  // status-bar widget
    // ─────────────────────────────────────────────────────────────────────────
>>>>>>> 5be580a (waste X Arduino)
};

#endif // MAINWINDOW_H
