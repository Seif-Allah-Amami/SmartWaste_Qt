#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    // Logic methods
    void onLoginClicked();
    void onVerifyClicked();
};

#endif // MAINWINDOW_H
