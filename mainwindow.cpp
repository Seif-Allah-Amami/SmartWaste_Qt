#include "mainwindow.h"
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
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QImage>
#include <QPainter>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QEventLoop>
#include <QNetworkReply>
#include <QTimer>
#include <QByteArray>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QRegularExpression>
#include <QListWidget>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    connect(ui->btnEmpQRCode, &QPushButton::clicked, this, &MainWindow::onGenerateQRCodeClicked);
    // CV Upload/analyzer
    connect(ui->btnEmpExport, &QPushButton::clicked, this, &MainWindow::onUploadCVClicked);
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

    // Add an Upload CV button to the actions panel (placed near export)
    if (ui->empActionsPanelLayout) {
        QPushButton *btnUploadCV = new QPushButton("Upload CV", this);
        btnUploadCV->setObjectName("btnEmpUploadCV");
        btnUploadCV->setToolTip("Upload or paste a CV to analyze skills and match jobs");
        // Insert before the export button if possible
        int insertPos = qMax(0, ui->empActionsPanelLayout->count() - 2);
        ui->empActionsPanelLayout->insertWidget(insertPos, btnUploadCV);
        connect(btnUploadCV, &QPushButton::clicked, this, &MainWindow::onUploadCVClicked);
    }
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

    // Validate search input: max 100 characters, no special SQL characters
    if (!searchText.isEmpty()) {
        if (searchText.length() > 100) {
            QMessageBox::warning(this, "Search Validation", "Search text cannot exceed 100 characters.");
            ui->empSearchBox->setText(searchText.left(100));
            return;
        }

        // Check for SQL injection attempts
        if (searchText.contains("'") || searchText.contains("\"") || searchText.contains(";") || searchText.contains("--")) {
            QMessageBox::warning(this, "Search Validation", "Search contains invalid characters. Quotes and SQL operators are not allowed.");
            ui->empSearchBox->clear();
            return;
        }

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
        // Field presence validation
        if (nameEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(&dialog, "Validation", "Full name is required.");
            return;
        }
        if (emailEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(&dialog, "Validation", "Email is required.");
            return;
        }
        if (positionEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(&dialog, "Validation", "Position is required.");
            return;
        }
        if (departmentEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(&dialog, "Validation", "Department is required.");
            return;
        }

        // Name validation (letters, spaces, hyphens only; 2-100 chars)
        if (!Employee::isValidName(nameEdit->text().trimmed())) {
            QMessageBox::warning(&dialog, "Validation", "Name must be 2-100 characters and contain only letters, spaces, or hyphens.");
            return;
        }

        // Email format validation
        if (!Employee::isValidEmail(emailEdit->text().trimmed())) {
            QMessageBox::warning(&dialog, "Validation", "Email format is invalid. Example: user@example.com");
            return;
        }

        // Salary validation
        if (!Employee::isValidSalary(salarySpin->value())) {
            QMessageBox::warning(&dialog, "Validation", "Salary must be between 0 and 10,000,000.");
            return;
        }

        // Hire date validation
        if (!Employee::isValidHireDate(dateEdit->date())) {
            QMessageBox::warning(&dialog, "Validation", "Hire date cannot be in the future.");
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

void MainWindow::onUploadCVClicked()
{
    QDialog dlg(this);
    dlg.setWindowTitle("CV Analyzer");
    dlg.setMinimumSize(600, 480);

    QVBoxLayout *root = new QVBoxLayout(&dlg);

    QLabel *hint = new QLabel("Paste CV text below or load a text file (.txt). Then click Analyze.", &dlg);
    hint->setWordWrap(true);
    root->addWidget(hint);

    QTextEdit *cvEdit = new QTextEdit(&dlg);
    cvEdit->setPlaceholderText("Paste resume / CV text here...");
    root->addWidget(cvEdit, 1);

    QHBoxLayout *h = new QHBoxLayout();
    QPushButton *loadBtn = new QPushButton("Load file", &dlg);
    QPushButton *analyzeBtn = new QPushButton("Analyze", &dlg);
    QPushButton *closeBtn = new QPushButton("Close", &dlg);
    h->addWidget(loadBtn);
    h->addStretch(1);
    h->addWidget(analyzeBtn);
    h->addWidget(closeBtn);
    root->addLayout(h);

    connect(loadBtn, &QPushButton::clicked, &dlg, [&]() {
        const QString path = QFileDialog::getOpenFileName(&dlg, "Open CV file", QString(), "Text files (*.txt);;All files (*)");
        if (path.isEmpty()) return;
        QFile f(path);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(&dlg, "Open file", "Failed to open file.");
            return;
        }
        const QByteArray data = f.readAll();
        cvEdit->setPlainText(QString::fromUtf8(data));
    });

    connect(closeBtn, &QPushButton::clicked, &dlg, &QDialog::reject);

    connect(analyzeBtn, &QPushButton::clicked, &dlg, [&]() {
        const QString cvText = cvEdit->toPlainText().toLower();
        if (cvText.trimmed().isEmpty()) {
            QMessageBox::warning(&dlg, "Analyze", "Please paste or load a CV first.");
            return;
        }

        // Simple job -> required skills database
        struct JobSpec { QString title; QStringList skills; };
        const QVector<JobSpec> jobs = {
            {"Driver", {"driving", "license", "road safety", "punctuality"}},
            {"Waste Collector", {"physical strength", "teamwork", "punctuality", "field work"}},
            {"Technician", {"repair", "maintenance", "mechanical", "hardware"}},
            {"Admin", {"communication", "organization", "management", "planning"}},
            {"Supervisor", {"leadership", "communication", "decision making", "organization"}}
        };

        struct Result { QString title; int matched; int total; QStringList matchedSkills; };
        QVector<Result> results;

        for (const JobSpec &job : jobs) {
            int matched = 0;
            QStringList matchedSkills;
            for (const QString &skill : job.skills) {
                QRegularExpression re("\\b" + QRegularExpression::escape(skill) + "\\b", QRegularExpression::CaseInsensitiveOption);
                if (re.match(cvText).hasMatch()) {
                    matched++;
                    matchedSkills << skill;
                }
            }
            results.append({job.title, matched, (int)job.skills.size(), matchedSkills});
        }

        // Sort by percentage desc then matched count
        std::sort(results.begin(), results.end(), [](const Result &a, const Result &b) {
            double pa = a.total ? (double)a.matched / a.total : 0.0;
            double pb = b.total ? (double)b.matched / b.total : 0.0;
            if (pa != pb) return pa > pb;
            return a.matched > b.matched;
        });

        // Build result text
        QString out;
        if (results.isEmpty()) out = "No job specs available.";
        else {
            const Result &best = results.first();
            double bestPct = best.total ? (100.0 * best.matched / best.total) : 0.0;
            out += QString("Best match: %1 (%2% matched)\n\n").arg(best.title).arg(QString::number(bestPct, 'f', 1));
            out += "Ranking:\n";
            for (const Result &r : results) {
                double pct = r.total ? (100.0 * r.matched / r.total) : 0.0;
                out += QString("- %1 : %2/%3 skills (%4%)\n").arg(r.title).arg(r.matched).arg(r.total).arg(QString::number(pct, 'f', 1));
                if (!r.matchedSkills.isEmpty()) out += QString("  matched: %1\n").arg(r.matchedSkills.join(", "));
            }
        }

        // Show results in a simple dialog
        QDialog resultDlg(this);
        resultDlg.setWindowTitle("CV Analysis Results");
        resultDlg.setMinimumSize(520, 360);
        QVBoxLayout *rl = new QVBoxLayout(&resultDlg);
        QTextEdit *resView = new QTextEdit(&resultDlg);
        resView->setReadOnly(true);
        resView->setPlainText(out);
        rl->addWidget(resView);
        QDialogButtonBox *rbtns = new QDialogButtonBox(QDialogButtonBox::Ok, &resultDlg);
        rl->addWidget(rbtns);
        connect(rbtns, &QDialogButtonBox::accepted, &resultDlg, &QDialog::accept);
        resultDlg.exec();
    });

    dlg.exec();
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
    showMainMenu();
}

void MainWindow::onVerifyClicked()
{
    if (ui->verifyCode->text().isEmpty()) return;
    showMainMenu();
}

void MainWindow::onGenerateQRCodeClicked()
{
    // Check if an employee is selected
    int employeeId = -1;
    if (!selectedEmployeeId(employeeId)) {
        QMessageBox::warning(this, "Generate QR Code", "Please select an employee first.");
        return;
    }

    // Get employee data from table
    const int row = ui->empTable->currentRow();
    if (row < 0) return;

    // Extract employee information
    QString empId = ui->empTable->item(row, 0)->text();
    QString fullName = ui->empTable->item(row, 1)->text();
    QString email = ui->empTable->item(row, 2)->text();
    QString position = ui->empTable->item(row, 3)->text();
    QString department = ui->empTable->item(row, 4)->text();
    QString hireDate = ui->empTable->item(row, 5)->text();
    QString salary = ui->empTable->item(row, 6)->text();

    // Format employee data as URL with query parameters
    // Using your computer's actual WiFi IP address
    QString qrUrl = QString(
        "http://172.20.10.2:8000/employee.html?"
        "id=%1&name=%2&email=%3&position=%4&department=%5&hiredate=%6&salary=%7"
    ).arg(
        QString::number(employeeId),
        fullName,
        email,
        position,
        department,
        hireDate,
        salary
    );

    // URL encode the parameters to handle spaces and special characters
    qrUrl = qrUrl.replace(" ", "%20");

    // Create QR Code dialog
    QDialog *qrDialog = new QDialog(this);
    qrDialog->setWindowTitle("Employee QR Code");
    qrDialog->setMinimumSize(400, 450);
    qrDialog->setStyleSheet("QDialog { background-color: #0a0e27; }");

    QVBoxLayout *layout = new QVBoxLayout(qrDialog);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);

    // Title label
    QLabel *titleLabel = new QLabel("Scan to view employee information", qrDialog);
    titleLabel->setStyleSheet("QLabel { color: #00ff9c; font-size: 12px; font-weight: 500; }");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // QR Code image label
    QLabel *qrLabel = new QLabel(qrDialog);
    qrLabel->setAlignment(Qt::AlignCenter);
    qrLabel->setStyleSheet("QLabel { background-color: white; padding: 10px; }");

    // Generate QR code using online service
    // Encode URL for QR code
    QString encodedUrl = qrUrl;
    encodedUrl = encodedUrl.replace("?", "%3F").replace("&", "%26").replace("=", "%3D");

    // Create URL for QR code generation
    QUrl apiUrl = QUrl(QString("https://api.qrserver.com/v1/create-qr-code/?size=300x300&data=%1").arg(encodedUrl));

    // Try to load QR code from online API
    QNetworkAccessManager *manager = new QNetworkAccessManager(qrDialog);
    QNetworkRequest request = QNetworkRequest(apiUrl);
    QNetworkReply *reply = manager->get(request);

    // Create event loop to wait for network response
    QEventLoop *loop = new QEventLoop(qrDialog);
    connect(reply, &QNetworkReply::finished, loop, &QEventLoop::quit);

    // Set timeout
    QTimer *timer = new QTimer(qrDialog);
    connect(timer, &QTimer::timeout, loop, &QEventLoop::quit);
    timer->start(5000);

    loop->exec();
    timer->stop();

    if (reply->error() == QNetworkReply::NoError) {
        QPixmap qrPixmap;
        qrPixmap.loadFromData(reply->readAll());
        if (!qrPixmap.isNull()) {
            qrLabel->setPixmap(qrPixmap.scaledToWidth(350, Qt::SmoothTransformation));
        } else {
            qrLabel->setText("Failed to generate QR code");
            qrLabel->setStyleSheet("QLabel { color: #ff6666; background-color: white; padding: 10px; }");
        }
    } else {
        // Fallback: show the URL if QR generation fails
        qrLabel->setText(QString("QR Code Generation Failed\n\nAccess this link:\n\n%1").arg(qrUrl));
        qrLabel->setStyleSheet("QLabel { color: #00ff9c; background-color: white; padding: 10px; font-family: monospace; font-size: 9px; }");
        qrLabel->setWordWrap(true);
    }

    reply->deleteLater();
    layout->addWidget(qrLabel, 1);

    // Info label
    QLabel *infoLabel = new QLabel("Scan this QR code with your camera to access employee information.", qrDialog);
    infoLabel->setStyleSheet("QLabel { color: #66ffcc; font-size: 11px; }");
    infoLabel->setWordWrap(true);
    infoLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(infoLabel);

    // Close button
    QPushButton *closeBtn = new QPushButton("Close", qrDialog);
    closeBtn->setStyleSheet("QPushButton { background-color: #00ff9c; color: #050d0a; padding: 8px; border-radius: 4px; font-weight: 600; } QPushButton:hover { background-color: #33ffcc; }");
    connect(closeBtn, &QPushButton::clicked, qrDialog, &QDialog::accept);
    layout->addWidget(closeBtn);

    qrDialog->exec();
    qrDialog->deleteLater();
}
