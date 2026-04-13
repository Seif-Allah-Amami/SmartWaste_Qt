#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connection.h"
#include "waste.h"

#include <QMainWindow>
#include <QDateTime>

class QLabel;

class QCloseEvent;
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

private slots:
    void on_btnClearSelection_clicked();
    void on_btnEmpClear_clicked();

private:

    QList<Waste> m_cachedWaste;
    QList<ScheduledPickup> m_scheduledPickups;
    int m_nextPickupTicket;
    bool m_databaseReady;
    Connection m_connection;  // Keep connection alive
    QLabel *m_searchHintLabel;
};

#endif // MAINWINDOW_H
