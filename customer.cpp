// Always include the header first
#include "customer.h"

// Backward-compatible constructor for legacy code
Customer::Customer(int customerId,
                   const QString &name,
                   const QString &email,
                   const QString &phone,
                   const QString &address,
                   const QString &reportType,
                   const QDate &reportDate,
                   int employeeId)
    : customerId_(customerId),
    name_(name),
    email_(email),
    phone_(phone),
    address_(address),
    reportType_(reportType),
    reportDate_(reportDate),
    employeeId_(employeeId),
    status_("pending")
{
}

#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QIntValidator>
#include <QLineEdit>
#include <QMessageBox>
#include <QComboBox>

#include <QVBoxLayout>
#include <QRegularExpression>

#include <QSqlQuery>
#include <QSqlError>
#include <QMetaType>
#include <QVariant>

Customer::Customer()
    : customerId_(0),
    employeeId_(0),
    status_("pending")
{
}

Customer::Customer(int customerId,
                   const QString &name,
                   const QString &email,
                   const QString &phone,
                   const QString &address,
                   const QString &reportType,
                   const QDate &reportDate,
                   int employeeId,
                   const QString &status)
    : customerId_(customerId),
    name_(name),
    email_(email),
    phone_(phone),
    address_(address),
    reportType_(reportType),
    reportDate_(reportDate),
    employeeId_(employeeId),
    status_(status)
{
}
QString Customer::status() const
{
    return status_;
}

void Customer::setStatus(const QString &status)
{
    // Canonical values: "pending", "solved", "in progress", "rejected"
    // Accept legacy "resolved" and map it to "solved".
    const QString normalized = status.trimmed().toLower();
    static const QStringList allowed = {"pending", "solved", "in progress", "rejected", "resolved"};
    if (allowed.contains(normalized)) {
        status_ = (normalized == "resolved") ? "solved" : normalized;
    } else {
        status_ = "pending"; // fallback to default if invalid
    }
}

int Customer::customerId() const
{
    return customerId_;
}

void Customer::setCustomerId(int customerId)
{
    customerId_ = customerId;
}

QString Customer::name() const
{
    return name_;
}

void Customer::setName(const QString &name)
{
    name_ = name;
}

QString Customer::email() const
{
    return email_;
}

void Customer::setEmail(const QString &email)
{
    email_ = email;
}

QString Customer::phone() const
{
    return phone_;
}

void Customer::setPhone(const QString &phone)
{
    phone_ = phone;
}

QString Customer::address() const
{
    return address_;
}

void Customer::setAddress(const QString &address)
{
    address_ = address;
}

QString Customer::reportType() const
{
    return reportType_;
}

void Customer::setReportType(const QString &reportType)
{
    reportType_ = reportType;
}

QDate Customer::reportDate() const
{
    return reportDate_;
}

void Customer::setReportDate(const QDate &reportDate)
{
    reportDate_ = reportDate;
}

int Customer::employeeId() const
{
    return employeeId_;
}

void Customer::setEmployeeId(int employeeId)
{
    employeeId_ = employeeId;
}

// ==================== CRUD OPERATIONS ====================

// CREATE: Insert a new customer record into the database
bool Customer::add(QString *errorMessage) const
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO CUSTOMER (CUSTOMER_ID, NAME, EMAIL, PHONE, ADDRESS, REPORT_TYPE, REPORT_DATE, "
        "EMPLOYEE_ID, STATUS) "
        "VALUES (CUSTOMER_SEQ.NEXTVAL, :name, :email, :phone, :address, :report_type, TO_DATE(:report_date, 'YYYY-MM-DD'), "
        ":employee_id, :status)");


    query.bindValue(":name", name_);
    query.bindValue(":email", email_);
    query.bindValue(":phone", phone_);
    query.bindValue(":address", address_);
    query.bindValue(":report_type", reportType_);
    query.bindValue(":report_date", reportDate_.toString("yyyy-MM-dd"));
    if (employeeId_ > 0) {
        query.bindValue(":employee_id", employeeId_);
    } else {
        // Oracle expects a typed NULL for NUMBER columns.
        query.bindValue(":employee_id", QVariant(QMetaType::fromType<int>()));
    }
    query.bindValue(":status", status_);

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    return true;
}

// READ: Retrieve a single customer by ID from the database
bool Customer::getById(int customerId, Customer &out, QString *errorMessage)
{
    QSqlQuery query;
    query.prepare(
        "SELECT CUSTOMER_ID, NAME, EMAIL, PHONE, ADDRESS, REPORT_TYPE, REPORT_DATE, "
        "EMPLOYEE_ID, STATUS FROM CUSTOMER WHERE CUSTOMER_ID = :customer_id");
    query.bindValue(":customer_id", customerId);

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    if (query.next()) {
        out = Customer(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toDate(),
            query.value(7).toInt(),
            query.value(8).toString());
        return true;
    }

    if (errorMessage) {
        *errorMessage = "Customer not found";
    }
    return false;
}

// READ: Retrieve all customers from the database
bool Customer::fetchAll(QList<Customer> &out, QString *errorMessage)
{
    out.clear();

    QSqlQuery query;
    query.prepare(
        "SELECT CUSTOMER_ID, NAME, EMAIL, PHONE, ADDRESS, REPORT_TYPE, REPORT_DATE, "
        "EMPLOYEE_ID, STATUS FROM CUSTOMER");

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    while (query.next()) {
        Customer customer(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toDate(),
            query.value(7).toInt(),
            query.value(8).toString());
        out.append(customer);
    }

    return true;
}

// UPDATE: Modify an existing customer record in the database
bool Customer::update(QString *errorMessage) const
{
    QSqlQuery query;
    query.prepare(
        "UPDATE CUSTOMER SET NAME = :name, EMAIL = :email, PHONE = :phone, ADDRESS = :address, "
        "REPORT_TYPE = :report_type, REPORT_DATE = :report_date, "
        "EMPLOYEE_ID = :employee_id, STATUS = :status WHERE CUSTOMER_ID = :customer_id");

    query.bindValue(":name", name_);
    query.bindValue(":email", email_);
    query.bindValue(":phone", phone_);
    query.bindValue(":address", address_);
    query.bindValue(":report_type", reportType_);
    query.bindValue(":report_date", reportDate_);
    if (employeeId_ > 0) {
        query.bindValue(":employee_id", employeeId_);
    } else {
        // Oracle expects a typed NULL for NUMBER columns.
        query.bindValue(":employee_id", QVariant(QMetaType::fromType<int>()));
    }
    query.bindValue(":status", status_);
    query.bindValue(":customer_id", customerId_);

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    return true;
}

// DELETE: Remove a customer record from the database
bool Customer::remove(int customerId, QString *errorMessage)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CUSTOMER WHERE CUSTOMER_ID = :customer_id");
    query.bindValue(":customer_id", customerId);
    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    return true;
}

AddCustomerDialog::AddCustomerDialog(QWidget *parent)
    : QDialog(parent),
    customerIdEdit_(nullptr),
    nameEdit_(nullptr),
    emailEdit_(nullptr),
    phoneEdit_(nullptr),
    addressEdit_(nullptr),
    reportTypeEdit_(nullptr),
    reportDateEdit_(nullptr),
    employeeIdEdit_(nullptr),
    buttonBox_(nullptr),
    isEdit_(false)
{
    setWindowTitle("Add Customer");
    setModal(true);
    buildUi();
}

void AddCustomerDialog::buildUi()
{
    auto *layout = new QVBoxLayout(this);
    auto *formLayout = new QFormLayout();

    customerIdEdit_ = new QLineEdit(this);
    customerIdEdit_->setValidator(new QIntValidator(1, 1000000000, this));
    customerIdEdit_->setPlaceholderText("Customer ID");

    nameEdit_ = new QLineEdit(this);
    nameEdit_->setPlaceholderText("Full name");

    emailEdit_ = new QLineEdit(this);
    emailEdit_->setPlaceholderText("example@domain.com");

    phoneEdit_ = new QLineEdit(this);
    phoneEdit_->setPlaceholderText("+216 12345678");
    phoneEdit_->setText("+216 ");
    connect(phoneEdit_, &QLineEdit::textChanged, this, &AddCustomerDialog::onPhoneTextChanged);

    addressEdit_ = new QLineEdit(this);
    addressEdit_->setPlaceholderText("Address");

    reportTypeEdit_ = new QComboBox(this);
    reportTypeEdit_->addItems({
        "Missed Waste Collection",
        "Garbage Overflow",
        "Illegal Dumping",
        "Recycling Issue"
    });

    reportDateEdit_ = new QDateEdit(this);
    reportDateEdit_->setCalendarPopup(true);
    reportDateEdit_->setDisplayFormat("yyyy-MM-dd");
    reportDateEdit_->setDate(QDate::currentDate());

    employeeIdEdit_ = new QComboBox(this);
    populateEmployeeList();

    statusEdit_ = new QComboBox(this);
    statusEdit_->addItems({"pending", "in progress", "solved", "rejected"});

    // Customer ID is auto-generated
    customerIdEdit_->setVisible(false);
    formLayout->addRow("Name", nameEdit_);
    formLayout->addRow("Email", emailEdit_);
    formLayout->addRow("Phone", phoneEdit_);
    formLayout->addRow("Address", addressEdit_);
    formLayout->addRow("Report Type", reportTypeEdit_);
    formLayout->addRow("Report Date", reportDateEdit_);
    formLayout->addRow("Employee ID", employeeIdEdit_);
    formLayout->addRow("Status", statusEdit_);

    buttonBox_ = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, this);
    connect(buttonBox_, &QDialogButtonBox::accepted, this, &AddCustomerDialog::onAccept);
    connect(buttonBox_, &QDialogButtonBox::rejected, this, &AddCustomerDialog::reject);

    clearButton_ = new QPushButton("Clear", this);
    connect(clearButton_, &QPushButton::clicked, this, &AddCustomerDialog::onClearClicked);

    layout->addLayout(formLayout);
    layout->addWidget(clearButton_);
    layout->addWidget(buttonBox_);
}

void AddCustomerDialog::populateEmployeeList()
{
    employeeIdEdit_->clear();
    employeeIdEdit_->addItem("(none)", 0);

    QSqlQuery query;
    if (!query.exec("SELECT EMPLOYEE_ID, FULL_NAME FROM EMPLOYEE ORDER BY FULL_NAME")) {
        QMessageBox::warning(this, "Employees", "Failed to load employees.\n" + query.lastError().text());
        return;
    }

    while (query.next()) {
        const int id = query.value(0).toInt();
        const QString name = query.value(1).toString();
        employeeIdEdit_->addItem(QString("%1 - %2").arg(id).arg(name), id);
    }
}

void AddCustomerDialog::onClearClicked()
{
    clearFields();
}

void AddCustomerDialog::clearFields()
{
    customerIdEdit_->clear();
    nameEdit_->clear();
    emailEdit_->clear();
    phoneEdit_->setText("+216 ");
    addressEdit_->clear();
    reportTypeEdit_->setCurrentIndex(0);
    reportDateEdit_->setDate(QDate::currentDate());
    employeeIdEdit_->setCurrentIndex(0);
    statusEdit_->setCurrentIndex(0);
}

void AddCustomerDialog::setCustomer(const Customer &customer)
{
    isEdit_ = true;
    setWindowTitle("Edit Customer");

    customerIdEdit_->setText(QString::number(customer.customerId()));
    customerIdEdit_->setEnabled(false);
    nameEdit_->setText(customer.name());
    emailEdit_->setText(customer.email());
    phoneEdit_->setText(customer.phone());
    addressEdit_->setText(customer.address());
    int idx = reportTypeEdit_->findText(customer.reportType());
    if (idx >= 0) {
        reportTypeEdit_->setCurrentIndex(idx);
    } else {
        reportTypeEdit_->setCurrentIndex(0);
    }

    QString statusText = customer.status().trimmed().toLower();
    if (statusText == "resolved") {
        statusText = "solved";
    }

    int statusIdx = statusEdit_->findText(statusText);
    if (statusIdx >= 0) {
        statusEdit_->setCurrentIndex(statusIdx);
    } else {
        statusEdit_->setCurrentIndex(0);
    }

    if (customer.reportDate().isValid()) {
        reportDateEdit_->setDate(customer.reportDate());
    }
    const int employeeId = customer.employeeId();
    int employeeIdx = employeeIdEdit_->findData(employeeId);
    if (employeeIdx >= 0) {
        employeeIdEdit_->setCurrentIndex(employeeIdx);
    } else if (employeeId > 0) {
        employeeIdEdit_->addItem(QString("%1 - (not found)").arg(employeeId), employeeId);
        employeeIdEdit_->setCurrentIndex(employeeIdEdit_->count() - 1);
    } else {
        employeeIdEdit_->setCurrentIndex(0);
    }
}

Customer AddCustomerDialog::customer() const
{
    return Customer(
        customerIdEdit_->text().toInt(),
        nameEdit_->text().trimmed(),
        emailEdit_->text().trimmed(),
        phoneEdit_->text().trimmed(),
        addressEdit_->text().trimmed(),
        reportTypeEdit_->currentText().trimmed(),
        reportDateEdit_->date(),
        employeeIdEdit_->currentData().toInt(),
        statusEdit_->currentText().trimmed());
}

void AddCustomerDialog::onAccept()
{
    if (!validateInput()) {
        return;
    }

    accept();
}

void AddCustomerDialog::onPhoneTextChanged(const QString &text)
{
    // Ensure +216 prefix is always present
    if (!text.startsWith("+216")) {
        phoneEdit_->blockSignals(true);
        QString digits = text;
        digits.remove(QRegularExpression("[^0-9]"));
        phoneEdit_->setText("+216 " + digits);
        phoneEdit_->setCursorPosition(phoneEdit_->text().length());
        phoneEdit_->blockSignals(false);
    }
}

bool AddCustomerDialog::validateInput()
{


    if (nameEdit_->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Name is required.");
        return false;
    }

    QString email = emailEdit_->text().trimmed();
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Email is required.");
        return false;
    }

    // Basic strict email validation: disallow empty local-part and domain labels that start with '.' or '-'.
    QRegularExpression emailRegex(
        R"(^[A-Za-z0-9](?:[A-Za-z0-9._%+-]{0,62}[A-Za-z0-9])?@[A-Za-z0-9](?:[A-Za-z0-9-]{0,61}[A-Za-z0-9])?(?:\.[A-Za-z0-9](?:[A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$)");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Invalid email format.");
        return false;
    }

    QString phone = phoneEdit_->text().trimmed();
    if (phone.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Phone number is required.");
        return false;
    }

    // Tunisia phone format: +216 followed by exactly 8 digits
    QRegularExpression phoneRegex(R"(^\+216\s?\d{8}$)");
    if (!phoneRegex.match(phone).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Invalid phone format.\nRequired: +216 followed by 8 digits\nExample: +216 12345678");
        return false;
    }

    return true;
}

