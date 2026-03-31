#include "mainwindow.h"
#include "ui_mainwindow.h"
<<<<<<< HEAD
#include "connection.h"
#include "machine.h"
#include "machinestats.h"
#include "machinehistory.h"
#include "alertsdialog.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QTableWidgetItem>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>

static void fillTable(QTableWidget *table, QSqlQueryModel *model)
{
    table->setRowCount(0);
    for (int r = 0; r < model->rowCount(); ++r) {
        table->insertRow(r);
        for (int c = 0; c < model->columnCount(); ++c) {
            QString val = (c == 4)
                ? model->record(r).value(c).toDate().toString("yyyy-MM-dd")
                : model->record(r).value(c).toString();
            table->setItem(r, c, new QTableWidgetItem(val));
        }
    }
    delete model;
}
=======
>>>>>>> d40e1db5339865986d79f6e20a2a9d6620de1d3a

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
<<<<<<< HEAD
    , conn(new Connection())
{
    ui->setupUi(this);

    if (!conn->createconnect()) {
        QMessageBox::critical(this, "Database", "Failed to connect to Oracle database");
    }

    QStringList headers = {"ID", "Name", "Type", "Location", "Purchase Date", "Status"};
    ui->machinesTable->setColumnCount(headers.size());
    ui->machinesTable->setHorizontalHeaderLabels(headers);
=======
{
    ui->setupUi(this);

    // Start on login page
    ui->stackedwidget->setCurrentIndex(0);

    // Connect all navigation buttons
    setupConnections();
>>>>>>> d40e1db5339865986d79f6e20a2a9d6620de1d3a
}

MainWindow::~MainWindow()
{
<<<<<<< HEAD
    delete conn;
    delete ui;
}

void MainWindow::on_btnViewMachines_clicked()
{
    fillTable(ui->machinesTable, Machine::afficher());
}

void MainWindow::on_searchBox_textChanged(const QString &text)
{
    fillTable(ui->machinesTable, Machine::rechercher(text, ui->sortComboBox->currentText()));
}

void MainWindow::on_sortComboBox_currentIndexChanged(int index)
{
    fillTable(ui->machinesTable, Machine::rechercher(ui->searchBox->text(), ui->sortComboBox->currentText()));
}

void MainWindow::on_btnExportPDF_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Export PDF", QString(), "PDF files (*.pdf)");
    if (path.isEmpty())
        return;

    QPdfWriter writer(path);
    writer.setPageSize(QPageSize::A4);
    writer.setPageMargins(QMarginsF(30, 30, 30, 30));

    QString html = "<h1>Machines Report</h1>";
    html += "<table border=1 cellspacing=0 cellpadding=3>";
    int cols = ui->machinesTable->columnCount();
    html += "<tr>";
    for (int c = 0; c < cols; ++c) {
        QTableWidgetItem *header = ui->machinesTable->horizontalHeaderItem(c);
        html += "<th>" + (header ? header->text() : QString()) + "</th>";
    }
    html += "</tr>";
    int rows = ui->machinesTable->rowCount();
    for (int r = 0; r < rows; ++r) {
        html += "<tr>";
        for (int c = 0; c < cols; ++c) {
            QTableWidgetItem *item = ui->machinesTable->item(r, c);
            html += "<td>" + (item ? item->text() : QString()) + "</td>";
        }
        html += "</tr>";
    }
    html += "</table>";

    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&writer);
}

void MainWindow::on_btnDeleteMachine_clicked()
{
    int row = ui->machinesTable->currentRow();
    if (row < 0) { QMessageBox::warning(this, "Delete", "Please select a machine first."); return; }

    QString idStr = ui->machinesTable->item(row, 0) ? ui->machinesTable->item(row, 0)->text() : QString();
    if (idStr.isEmpty()) { QMessageBox::warning(this, "Delete", "Selected machine has no ID."); return; }

    if (QMessageBox::question(this, "Confirm Delete", "Delete machine " + idStr + "?",
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) return;

    if (!Machine::supprimer(idStr.toInt()))
        QMessageBox::critical(this, "Database", "Failed to delete.");
    else {
        QMessageBox::information(this, "Success", "Machine deleted successfully.");
        fillTable(ui->machinesTable, Machine::afficher());
    }
}

void MainWindow::on_btnAddMachine_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Add Machine");
    QFormLayout form(&dialog);
    QLineEdit *nameEdit = new QLineEdit(&dialog);
    QComboBox *typeCombo = new QComboBox(&dialog);
    typeCombo->addItems({"Waste Compactor", "Shredder", "Baler", "Recycling Sorter"});
    QLineEdit *locationEdit = new QLineEdit(&dialog);
    QDateEdit *purchaseEdit = new QDateEdit(QDate::currentDate(), &dialog);
    purchaseEdit->setCalendarPopup(true);
    QComboBox *statusCombo = new QComboBox(&dialog);
    statusCombo->addItems({"Active", "Under Maintenance", "Out of Service"});
    form.addRow("Name:", nameEdit);
    form.addRow("Type:", typeCombo);
    form.addRow("Location:", locationEdit);
    form.addRow("Purchase Date:", purchaseEdit);
    form.addRow("Status:", statusCombo);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        if (nameEdit->text().isEmpty())     { QMessageBox::warning(this, "Input error", "Please enter the machine name.");     return; }
        if (locationEdit->text().isEmpty()) { QMessageBox::warning(this, "Input error", "Please enter the machine location."); return; }

        Machine m(nameEdit->text(), typeCombo->currentText(), locationEdit->text(),
                  purchaseEdit->date().toString("yyyy-MM-dd"), statusCombo->currentText());

        if (!m.ajouter())
            QMessageBox::critical(this, "Database", "Failed to insert record.");
        else {
            QMessageBox::information(this, "Success", "Machine added successfully.");
            fillTable(ui->machinesTable, Machine::afficher());
        }
    }
}

void MainWindow::on_btnEditMachine_clicked()
{
    int row = ui->machinesTable->currentRow();
    if (row < 0) { QMessageBox::warning(this, "Edit", "Please select a machine first."); return; }

    QString idStr    = ui->machinesTable->item(row, 0)->text();
    QString name     = ui->machinesTable->item(row, 1)->text();
    QString type     = ui->machinesTable->item(row, 2)->text();
    QString location = ui->machinesTable->item(row, 3)->text();
    QDate purchase   = QDate::fromString(ui->machinesTable->item(row, 4)->text(), "yyyy-MM-dd");
    QString status   = ui->machinesTable->item(row, 5)->text();

    QDialog dialog(this);
    dialog.setWindowTitle("Edit Machine");
    QFormLayout form(&dialog);
    QLineEdit *nameEdit = new QLineEdit(name, &dialog);
    QComboBox *typeCombo = new QComboBox(&dialog);
    typeCombo->addItems({"Waste Compactor", "Shredder", "Baler", "Recycling Sorter"});
    typeCombo->setCurrentText(type);
    QLineEdit *locationEdit = new QLineEdit(location, &dialog);
    QDateEdit *purchaseEdit = new QDateEdit(purchase, &dialog);
    purchaseEdit->setCalendarPopup(true);
    QComboBox *statusCombo = new QComboBox(&dialog);
    statusCombo->addItems({"Active", "Under Maintenance", "Out of Service"});
    statusCombo->setCurrentText(status);
    form.addRow("Name:", nameEdit);
    form.addRow("Type:", typeCombo);
    form.addRow("Location:", locationEdit);
    form.addRow("Purchase Date:", purchaseEdit);
    form.addRow("Status:", statusCombo);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        if (nameEdit->text().isEmpty())     { QMessageBox::warning(this, "Input error", "Please enter the machine name.");     return; }
        if (locationEdit->text().isEmpty()) { QMessageBox::warning(this, "Input error", "Please enter the machine location."); return; }

        Machine m(nameEdit->text(), typeCombo->currentText(), locationEdit->text(),
                  purchaseEdit->date().toString("yyyy-MM-dd"), statusCombo->currentText());

        if (!m.modifier(idStr.toInt()))
            QMessageBox::critical(this, "Database", "Failed to update record.");
        else {
            QMessageBox::information(this, "Success", "Machine updated successfully.");
            fillTable(ui->machinesTable, Machine::afficher());
        }
    }
}
void MainWindow::on_btnMachinePerformance_clicked()
{
    int row = ui->machinesTable->currentRow();

    if (row < 0) {
        MachineGlobalStats dlg(this);
        dlg.exec();
    } else {
        QString id       = ui->machinesTable->item(row, 0)->text();
        QString name     = ui->machinesTable->item(row, 1)->text();
        QString type     = ui->machinesTable->item(row, 2)->text();
        QString location = ui->machinesTable->item(row, 3)->text();
        QString date     = ui->machinesTable->item(row, 4)->text();
        QString status   = ui->machinesTable->item(row, 5)->text();

        MachineSingleStats dlg(id, name, type, location, date, status, this);
        dlg.exec();
    }
}
void MainWindow::on_btnHistory_clicked()
{
    int row = ui->machinesTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, tr("History"),
                             tr("Please select a machine to view its history."));
        return;
    }

    QString id   = ui->machinesTable->item(row, 0)->text();
    QString name = ui->machinesTable->item(row, 1)->text();

    MachineHistory dlg(id, name, this);
    dlg.exec();
}

void MainWindow::on_btnAlertSystem_clicked()
{
    int row = ui->machinesTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this,
                             tr("Alerts & Predictions"),
                             tr("Please select a machine from the table first."));
        return;
    }

    const QString id   = ui->machinesTable->item(row, 0)->text();
    const QString name = ui->machinesTable->item(row, 1)->text();

    AlertsDialog dlg(id, name, this);
    dlg.exec();
}
=======
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
=======
<<<<<<< HEAD
    connect(ui->btnMenuVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb

    // Employee Page Sidebar Navigation
    connect(ui->btnEmpDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnEmpLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmpCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
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
    // Waste Management Sidebar Navigation
    connect(ui->btnDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
<<<<<<< HEAD
    connect(ui->btnVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
=======
<<<<<<< HEAD
    connect(ui->btnVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
    // Waste Vehicle Sidebar Navigation
    connect(ui->btnDashboard_2, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout_2, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmployee_2, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnWaste_2, &QPushButton::clicked, this, &MainWindow::showWastePage);
<<<<<<< HEAD
    connect(ui->btnMachines_2, &QPushButton::clicked, this, &MainWindow::showMachinePage);
    // Waste Machine Sidebar Navigation
    connect(ui->btnDashboard_3, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout_3, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnVehicle_3, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnEmployee_3, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnWaste_3, &QPushButton::clicked, this, &MainWindow::showWastePage);


    // ✅ ADD THIS LINE ONLY

=======
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03


    // ✅ ADD THIS LINE ONLY
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
}


// ================= ADD THIS FUNCTION ONLY =================

void MainWindow::showWastePage()
{
    ui->stackedwidget->setCurrentWidget(ui->wastemanagement);
}

<<<<<<< HEAD
void MainWindow::showMachinePage()
{
    ui->stackedwidget->setCurrentWidget(ui->machinePage);
}
=======

>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
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
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
void MainWindow::showVehiclePage()
{
    ui->stackedwidget->setCurrentWidget(ui->vehiclePage);
}
<<<<<<< HEAD
=======
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb

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
>>>>>>> d40e1db5339865986d79f6e20a2a9d6620de1d3a
