#include "mainwindow.h"
<<<<<<< HEAD
#include "connection.h"
#include "ui_mainwindow.h"

#include <QHeaderView>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>

#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_databaseReady(false)
{
    ui->setupUi(this);
    ui->stackedwidget->setCurrentIndex(0);
    setupConnections();
    setupEmployeeTable();
    m_databaseReady = initializeDatabase() && ensureEmployeeTable();
    onViewEmployeesClicked();
=======
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
>>>>>>> origin/employee
}

MainWindow::~MainWindow()
{
    delete ui;
}

<<<<<<< HEAD
bool MainWindow::initializeDatabase()
{
    return Connection::createConnection();
}

bool MainWindow::ensureEmployeeTable()
{
    QSqlQuery query;
    const bool ok = query.exec("SELECT EMPLOYEE_ID, FULL_NAME, EMAIL, POSITION, DEPARTMENT, HIRE_DATE, SALARY, ID_MACHINE, ID_SUPPLIER FROM EMPLOYEE WHERE 1=0");
    if (!ok)
        QMessageBox::critical(this, "Employee table", "EMPLOYEE check failed: " + query.lastError().text());
    return ok;
}

void MainWindow::setupConnections()
{
    // Login
    connect(ui->btnLogin, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->btnForgotPassword, &QPushButton::clicked, this, &MainWindow::showRecoveryPage);

    // Recovery
    connect(ui->btnRecoveryContinue, &QPushButton::clicked, this, &MainWindow::showVerificationPage);
    connect(ui->btnRecoveryCancel, &QPushButton::clicked, this, &MainWindow::showLoginPage);

    // Verification
    connect(ui->btnVerifyCheck, &QPushButton::clicked, this, &MainWindow::onVerifyClicked);
    connect(ui->btnVerifyCancel, &QPushButton::clicked, this, &MainWindow::showLoginPage);

    // Main Menu
    connect(ui->btnMenuEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnMenuCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
    connect(ui->btnMenuWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);

    // Employee Sidebar
    connect(ui->btnEmpDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnEmpLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmpEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnEmpCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
    connect(ui->btnEmpAdd, &QPushButton::clicked, this, &MainWindow::onAddEmployeeClicked);
    connect(ui->btnEmpView, &QPushButton::clicked, this, &MainWindow::onViewEmployeesClicked);
    connect(ui->btnEmpEdit, &QPushButton::clicked, this, &MainWindow::onEditEmployeeClicked);
    connect(ui->btnEmpDelete, &QPushButton::clicked, this, &MainWindow::onDeleteEmployeeClicked);
    connect(ui->btnEmpClear, &QPushButton::clicked, this, &MainWindow::onClearEmployeeClicked);
    connect(ui->empSearchBox, &QLineEdit::textChanged, this, &MainWindow::onEmpSearchChanged);
    connect(ui->empSortComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::onEmpSortChanged);

    // Waste Sidebar
    connect(ui->btnDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
}

void MainWindow::setupEmployeeTable()
{
    ui->empTable->setColumnCount(9);
    ui->empTable->setHorizontalHeaderLabels(QStringList()
                                            << "Employee ID" << "Full name" << "Email" << "Position"
                                            << "Department" << "Hire date" << "Salary" << "Machine ID" << "Supplier ID");
    ui->empTable->horizontalHeader()->setStretchLastSection(true);
    ui->empTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::loadEmployeesToTable(const QList<Employee> &employees)
{
    ui->empTable->setRowCount(employees.size());
    for (int row = 0; row < employees.size(); ++row) {
        const Employee &e = employees.at(row);
        ui->empTable->setItem(row, 0, new QTableWidgetItem(QString::number(e.id())));
        ui->empTable->setItem(row, 1, new QTableWidgetItem(e.fullName()));
        ui->empTable->setItem(row, 2, new QTableWidgetItem(e.email()));
        ui->empTable->setItem(row, 3, new QTableWidgetItem(e.position()));
        ui->empTable->setItem(row, 4, new QTableWidgetItem(e.department()));
        ui->empTable->setItem(row, 5, new QTableWidgetItem(e.hireDate().toString("yyyy-MM-dd")));
        ui->empTable->setItem(row, 6, new QTableWidgetItem(QString::number(e.salary(), 'f', 2)));
        ui->empTable->setItem(row, 7, new QTableWidgetItem(e.idMachine() > 0 ? QString::number(e.idMachine()) : ""));
        ui->empTable->setItem(row, 8, new QTableWidgetItem(e.idSupplier() > 0 ? QString::number(e.idSupplier()) : ""));
    }
}

void MainWindow::applyEmployeeSearchAndSort()
{
    QList<Employee> filtered = m_cachedEmployees;
    const QString searchText = ui->empSearchBox->text().trimmed().toLower();

    if (!searchText.isEmpty()) {
        QList<Employee> matches;
        for (const Employee &e : filtered) {
            if (QString::number(e.id()).contains(searchText, Qt::CaseInsensitive) ||
                e.fullName().contains(searchText, Qt::CaseInsensitive) ||
                e.email().contains(searchText, Qt::CaseInsensitive))
                matches.append(e);
        }
        filtered = matches;
    }

    const int sortIndex = ui->empSortComboBox->currentIndex();
    std::sort(filtered.begin(), filtered.end(), [sortIndex](const Employee &a, const Employee &b) {
        if (sortIndex == 1) return a.department().toLower() < b.department().toLower();
        if (sortIndex == 2) return a.salary() > b.salary();
        if (sortIndex == 3) return a.hireDate() > b.hireDate();
        return a.fullName().toLower() < b.fullName().toLower();
    });

    loadEmployeesToTable(filtered);
}

bool MainWindow::collectEmployeeData(Employee &employee, bool forEdit)
{
    int employeeId = -1;
    QString defaultName, defaultEmail, defaultPosition, defaultDepartment;
    QString defaultHireDate = QDate::currentDate().toString("yyyy-MM-dd");
    double defaultSalary = 0.0;
    int defaultMachineId = 0, defaultSupplierId = 0;

    if (forEdit) {
        if (!selectedEmployeeId(employeeId)) {
            QMessageBox::warning(this, "Edit employee", "Select an employee row first.");
            return false;
        }
        const int row     = ui->empTable->currentRow();
        defaultName       = ui->empTable->item(row, 1)->text();
        defaultEmail      = ui->empTable->item(row, 2)->text();
        defaultPosition   = ui->empTable->item(row, 3)->text();
        defaultDepartment = ui->empTable->item(row, 4)->text();
        defaultHireDate   = ui->empTable->item(row, 5)->text();
        defaultSalary     = ui->empTable->item(row, 6)->text().toDouble();
        defaultMachineId  = ui->empTable->item(row, 7)->text().toInt();
        defaultSupplierId = ui->empTable->item(row, 8)->text().toInt();
    }

    QDialog dialog(this);
    dialog.setWindowTitle(forEdit ? "Edit Employee" : "Add Employee");
    dialog.setMinimumWidth(380);

    QFormLayout *form = new QFormLayout(&dialog);
    form->setSpacing(10);
    form->setContentsMargins(15, 15, 15, 15);

    QSpinBox *idSpin = new QSpinBox(&dialog);
    idSpin->setRange(1, 2147483647);
    idSpin->setValue(forEdit ? employeeId : 1);
    idSpin->setEnabled(!forEdit);

    QLineEdit *nameEdit       = new QLineEdit(defaultName, &dialog);
    QLineEdit *emailEdit      = new QLineEdit(defaultEmail, &dialog);
    QLineEdit *positionEdit   = new QLineEdit(defaultPosition, &dialog);
    QLineEdit *departmentEdit = new QLineEdit(defaultDepartment, &dialog);

    QDateEdit *dateEdit = new QDateEdit(&dialog);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    const QDate parsedDate = QDate::fromString(defaultHireDate, "yyyy-MM-dd");
    dateEdit->setDate(parsedDate.isValid() ? parsedDate : QDate::currentDate());

    QDoubleSpinBox *salarySpin = new QDoubleSpinBox(&dialog);
    salarySpin->setRange(0.0, 1000000000.0);
    salarySpin->setDecimals(2);
    salarySpin->setValue(defaultSalary);

    QSpinBox *machineSpin = new QSpinBox(&dialog);
    machineSpin->setRange(0, 2147483647);
    machineSpin->setValue(defaultMachineId);
    machineSpin->setSpecialValueText("None");

    QSpinBox *supplierSpin = new QSpinBox(&dialog);
    supplierSpin->setRange(0, 2147483647);
    supplierSpin->setValue(defaultSupplierId);
    supplierSpin->setSpecialValueText("None");

    if (!forEdit) form->addRow("Employee ID:", idSpin);
    form->addRow("Full name:",   nameEdit);
    form->addRow("Email:",       emailEdit);
    form->addRow("Position:",    positionEdit);
    form->addRow("Department:",  departmentEdit);
    form->addRow("Hire date:",   dateEdit);
    form->addRow("Salary:",      salarySpin);
    form->addRow("Machine ID:",  machineSpin);
    form->addRow("Supplier ID:", supplierSpin);

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    form->addRow(buttons);

    connect(buttons, &QDialogButtonBox::accepted, &dialog, [&]() {
        if (nameEdit->text().trimmed().isEmpty() ||
            emailEdit->text().trimmed().isEmpty() ||
            positionEdit->text().trimmed().isEmpty() ||
            departmentEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(&dialog, "Validation", "Name, Email, Position and Department are required.");
            return;
        }
        dialog.accept();
    });
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted) return false;

    employee.setId(forEdit ? employeeId : idSpin->value());
    employee.setFullName(nameEdit->text().trimmed());
    employee.setEmail(emailEdit->text().trimmed());
    employee.setPosition(positionEdit->text().trimmed());
    employee.setDepartment(departmentEdit->text().trimmed());
    employee.setHireDate(dateEdit->date());
    employee.setSalary(salarySpin->value());
    employee.setIdMachine(machineSpin->value());
    employee.setIdSupplier(supplierSpin->value());
    return true;
}

bool MainWindow::selectedEmployeeId(int &id) const
{
    const int row = ui->empTable->currentRow();
    if (row < 0 || !ui->empTable->item(row, 0)) return false;
    id = ui->empTable->item(row, 0)->text().toInt();
    return id > 0;
}

void MainWindow::onAddEmployeeClicked()
{
    if (!m_databaseReady) { QMessageBox::critical(this, "Database", "Database is not ready."); return; }
    Employee employee;
    if (!collectEmployeeData(employee, false)) return;
    if (!employee.create()) {
        QMessageBox::warning(this, "Add Employee", Employee::lastError());
        return;
    }
    onViewEmployeesClicked();
    QMessageBox::information(this, "Add Employee", "Employee added successfully.");
}

void MainWindow::onViewEmployeesClicked()
{
    if (!m_databaseReady) { ui->empTable->setRowCount(0); return; }
    m_cachedEmployees = Employee::readAll();
    applyEmployeeSearchAndSort();
}

void MainWindow::onEditEmployeeClicked()
{
    if (!m_databaseReady) { QMessageBox::critical(this, "Database", "Database is not ready."); return; }
    Employee employee;
    if (!collectEmployeeData(employee, true)) return;
    if (!employee.update()) {
        QMessageBox::warning(this, "Edit Employee", Employee::lastError());
        return;
    }
    onViewEmployeesClicked();
    QMessageBox::information(this, "Edit Employee", "Employee updated successfully.");
}

void MainWindow::onDeleteEmployeeClicked()
{
    if (!m_databaseReady) { QMessageBox::critical(this, "Database", "Database is not ready."); return; }
    int employeeId = -1;
    if (!selectedEmployeeId(employeeId)) {
        QMessageBox::warning(this, "Delete employee", "Select an employee row first.");
        return;
    }
    if (QMessageBox::question(this, "Delete employee", "Are you sure you want to delete this employee?",
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) return;
    if (!Employee::remove(employeeId)) {
        QMessageBox::warning(this, "Delete Employee", Employee::lastError());
        return;
    }
    onViewEmployeesClicked();
    QMessageBox::information(this, "Delete Employee", "Employee deleted successfully.");
}

void MainWindow::onClearEmployeeClicked()
{
    ui->empSearchBox->clear();
    ui->empTable->clearSelection();
}

void MainWindow::onEmpSearchChanged(const QString &text)
{
    Q_UNUSED(text)
    applyEmployeeSearchAndSort();
}

void MainWindow::onEmpSortChanged(int index)
{
    Q_UNUSED(index)
    applyEmployeeSearchAndSort();
}

void MainWindow::on_btnClearSelection_clicked() { ui->empTable->clearSelection(); }
void MainWindow::on_btnEmpClear_clicked()
{
    ui->empSearchBox->clear();
    ui->empTable->clearSelection();
}

// ===== PAGE NAVIGATION =====

void MainWindow::showLoginPage()        { ui->stackedwidget->setCurrentWidget(ui->connection); }
void MainWindow::showRecoveryPage()     { ui->stackedwidget->setCurrentWidget(ui->recoverpwd); }
void MainWindow::showVerificationPage() { ui->stackedwidget->setCurrentWidget(ui->verification); }
void MainWindow::showMainMenu()         { ui->stackedwidget->setCurrentWidget(ui->main); }
void MainWindow::showEmployeePage()     { ui->stackedwidget->setCurrentWidget(ui->employe); }
void MainWindow::showCustomerPage()     { /* ui->stackedwidget->setCurrentWidget(ui->customer); */ }
void MainWindow::showWastePage()        { ui->stackedwidget->setCurrentWidget(ui->wastemanagement); }

void MainWindow::onLoginClicked()
{
    if (ui->loginUsername->text().isEmpty() || ui->loginPassword->text().isEmpty()) return;
=======
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

>>>>>>> origin/employee
    showMainMenu();
}

void MainWindow::onVerifyClicked()
{
<<<<<<< HEAD
    if (ui->verifyCode->text().isEmpty()) return;
=======
    QString code = ui->verifyCode->text();

    if (code.isEmpty()) {
        return;
    }

>>>>>>> origin/employee
    showMainMenu();
}
