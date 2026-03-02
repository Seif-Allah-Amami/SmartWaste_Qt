#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Start on login page
    ui->stackedwidget->setCurrentIndex(0);

    // Connect all navigation buttons
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    // Login Page Navigation
    connect(ui->btnLogin, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->btnForgotPassword, &QPushButton::clicked, this, &MainWindow::showRecoveryPage);

    // Recovery Page Navigation
    connect(ui->btnRecoveryContinue, &QPushButton::clicked, this, &MainWindow::showVerificationPage);
    connect(ui->btnRecoveryCancel, &QPushButton::clicked, this, &MainWindow::showLoginPage);

    // Verification Page Navigation
    connect(ui->btnVerifyCheck, &QPushButton::clicked, this, &MainWindow::onVerifyClicked);
    connect(ui->btnVerifyCancel, &QPushButton::clicked, this, &MainWindow::showLoginPage);

    // Main Menu Navigation
    connect(ui->btnMenuEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnMenuCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
    connect(ui->btnMenuWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
<<<<<<< HEAD
    connect(ui->btnMenuVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnMenuMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
    connect(ui->btnMenuSupplier, &QPushButton::clicked, this, &MainWindow::showSupplierPage);
=======
<<<<<<< HEAD
    connect(ui->btnMenuVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnMenuMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
=======
<<<<<<< HEAD
    connect(ui->btnMenuVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544

    // Employee Page Sidebar Navigation
    connect(ui->btnEmpDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnEmpLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmpCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
<<<<<<< HEAD
    connect(ui->btnEmpVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
    connect(ui->btnEmpMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
    connect(ui->btnEmpSupplier, &QPushButton::clicked, this, &MainWindow::showSupplierPage);
=======
<<<<<<< HEAD
    connect(ui->btnEmpVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
    connect(ui->btnEmpMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
=======
<<<<<<< HEAD
    connect(ui->btnEmpVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
    // Waste Management Sidebar Navigation
    connect(ui->btnDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
<<<<<<< HEAD
    connect(ui->btnVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
    connect(ui->btnSupplier, &QPushButton::clicked, this, &MainWindow::showSupplierPage);
=======
<<<<<<< HEAD
    connect(ui->btnVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
=======
<<<<<<< HEAD
    connect(ui->btnVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
    // Waste Vehicle Sidebar Navigation
    connect(ui->btnDashboard_2, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout_2, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmployee_2, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnWaste_2, &QPushButton::clicked, this, &MainWindow::showWastePage);
<<<<<<< HEAD
    connect(ui->btnMachines_2, &QPushButton::clicked, this, &MainWindow::showMachinePage);
    connect(ui->btnSupplier_2, &QPushButton::clicked, this, &MainWindow::showSupplierPage);
=======
<<<<<<< HEAD
    connect(ui->btnMachines_2, &QPushButton::clicked, this, &MainWindow::showMachinePage);
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
    // Waste Machine Sidebar Navigation
    connect(ui->btnDashboard_3, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout_3, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnVehicle_3, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnEmployee_3, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnWaste_3, &QPushButton::clicked, this, &MainWindow::showWastePage);
<<<<<<< HEAD
    connect(ui->btnSuppliers, &QPushButton::clicked, this, &MainWindow::showSupplierPage);
    // Waste Supplier Sidebar Navigation
    connect(ui->btnDashboard_4, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout_3, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnInventory, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnReports, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnOrders, &QPushButton::clicked, this, &MainWindow::showWastePage);
    connect(ui->btnMachines_4, &QPushButton::clicked, this, &MainWindow::showMachinePage);
=======
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544


    // ✅ ADD THIS LINE ONLY

<<<<<<< HEAD
=======
=======
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03


    // ✅ ADD THIS LINE ONLY
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
}


// ================= ADD THIS FUNCTION ONLY =================

void MainWindow::showWastePage()
{
    ui->stackedwidget->setCurrentWidget(ui->wastemanagement);
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
void MainWindow::showMachinePage()
{
    ui->stackedwidget->setCurrentWidget(ui->machinePage);
}
<<<<<<< HEAD
void MainWindow::showSupplierPage()
{
    ui->stackedwidget->setCurrentWidget(ui->supplier);
}
=======
=======

>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
// ================= YOUR ORIGINAL FUNCTIONS =================

void MainWindow::showLoginPage()
{
    ui->stackedwidget->setCurrentWidget(ui->connection);
}

void MainWindow::showRecoveryPage()
{
    ui->stackedwidget->setCurrentWidget(ui->recoverpwd);
}

void MainWindow::showVerificationPage()
{
    ui->stackedwidget->setCurrentWidget(ui->verification);
}

void MainWindow::showMainMenu()
{
    ui->stackedwidget->setCurrentWidget(ui->main);
}

void MainWindow::showEmployeePage()
{
    ui->stackedwidget->setCurrentWidget(ui->employe);
}
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
void MainWindow::showVehiclePage()
{
    ui->stackedwidget->setCurrentWidget(ui->vehiclePage);
}
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544

void MainWindow::showCustomerPage()
{
    // When you create the customer page, navigate to it
    // ui->stackedwidget->setCurrentWidget(ui->customer);
}

void MainWindow::onLoginClicked()
{
    QString username = ui->loginUsername->text();
    QString password = ui->loginPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        return;
    }

    showMainMenu();
}

void MainWindow::onVerifyClicked()
{
    QString code = ui->verifyCode->text();

    if (code.isEmpty()) {
        return;
    }

    showMainMenu();
}
