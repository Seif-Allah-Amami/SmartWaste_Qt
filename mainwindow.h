#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include "machinestats.h"
#include "machinehistory.h"
#include "alertsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
=======

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
>>>>>>> d40e1db5339865986d79f6e20a2a9d6620de1d3a
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

<<<<<<< HEAD
private slots:
    void on_btnAddMachine_clicked();
    void on_btnViewMachines_clicked();
    void on_btnDeleteMachine_clicked();
    void on_btnEditMachine_clicked();
    void on_btnExportPDF_clicked();
    void on_searchBox_textChanged(const QString &text);
    void on_sortComboBox_currentIndexChanged(int index);
    void on_btnMachinePerformance_clicked();
    void on_btnHistory_clicked();
    void on_btnAlertSystem_clicked();

private:
    Ui::MainWindow *ui;
    class Connection *conn;
};
#endif // MAINWINDOW_H
=======
private:
    Ui::MainWindow *ui;

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
    void showVehiclePage();
    void showMachinePage();
=======
<<<<<<< HEAD
    void showVehiclePage();
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb

    // Logic methods
    void onLoginClicked();
    void onVerifyClicked();
};

#endif // MAINWINDOW_H
>>>>>>> d40e1db5339865986d79f6e20a2a9d6620de1d3a
