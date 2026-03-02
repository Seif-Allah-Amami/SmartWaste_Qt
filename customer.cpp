#include "customer.h"

#include <QDateEdit>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QIntValidator>
#include <QLineEdit>
#include <QMessageBox>
#include <QSpinBox>

#include <QVBoxLayout>
#include <QRegularExpression>

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

Customer::Customer()
    : customerId_(0),
    satisfactionScore_(0.0),
    employeeId_(0)
{
}

Customer::Customer(int customerId,
                   const QString &name,
                   const QString &email,
                   const QString &phone,
                   const QString &address,
                   const QString &reportType,
                   const QDate &reportDate,
                   double satisfactionScore,
                   int employeeId)
    : customerId_(customerId),
    name_(name),
    email_(email),
    phone_(phone),
    address_(address),
    reportType_(reportType),
    reportDate_(reportDate),
    satisfactionScore_(satisfactionScore),
    employeeId_(employeeId)
{
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

double Customer::satisfactionScore() const
{
    return satisfactionScore_;
}

void Customer::setSatisfactionScore(double satisfactionScore)
{
    satisfactionScore_ = satisfactionScore;
}

int Customer::employeeId() const
{
    return employeeId_;
}

void Customer::setEmployeeId(int employeeId)
{
    employeeId_ = employeeId;
}

bool Customer::add(QString *errorMessage) const
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO CUSTOMER (CUSTOMER_ID, NAME, EMAIL, PHONE, ADDRESS, REPORT_TYPE, REPORT_DATE, "
        "SATISFACTION_SCORE, EMPLOYEE_ID) "
        "VALUES (:customer_id, :name, :email, :phone, :address, :report_type, :report_date, "
        ":satisfaction_score, :employee_id)");

    query.bindValue(":customer_id", customerId_);
    query.bindValue(":name", name_);
    query.bindValue(":email", email_);
    query.bindValue(":phone", phone_);
    query.bindValue(":address", address_);
    query.bindValue(":report_type", reportType_);
    query.bindValue(":report_date", reportDate_);
    query.bindValue(":satisfaction_score", satisfactionScore_);
    if (employeeId_ > 0) {
        query.bindValue(":employee_id", employeeId_);
    } else {
        query.bindValue(":employee_id", QVariant(QVariant::Int));
    }

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    return true;
}

bool Customer::update(QString *errorMessage) const
{
    QSqlQuery query;
    query.prepare(
        "UPDATE CUSTOMER SET NAME = :name, EMAIL = :email, PHONE = :phone, ADDRESS = :address, "
        "REPORT_TYPE = :report_type, REPORT_DATE = :report_date, SATISFACTION_SCORE = :satisfaction_score, "
        "EMPLOYEE_ID = :employee_id WHERE CUSTOMER_ID = :customer_id");

    query.bindValue(":name", name_);
    query.bindValue(":email", email_);
    query.bindValue(":phone", phone_);
    query.bindValue(":address", address_);
    query.bindValue(":report_type", reportType_);
    query.bindValue(":report_date", reportDate_);
    query.bindValue(":satisfaction_score", satisfactionScore_);
    if (employeeId_ > 0) {
        query.bindValue(":employee_id", employeeId_);
    } else {
        query.bindValue(":employee_id", QVariant(QVariant::Int));
    }
    query.bindValue(":customer_id", customerId_);

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    return true;
}

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

bool Customer::fetchAll(QList<Customer> &out, QString *errorMessage)
{
    out.clear();

    QSqlQuery query;
    query.prepare(
        "SELECT CUSTOMER_ID, NAME, EMAIL, PHONE, ADDRESS, REPORT_TYPE, REPORT_DATE, "
        "SATISFACTION_SCORE, EMPLOYEE_ID FROM CUSTOMER");

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
            query.value(7).toDouble(),
            query.value(8).toInt());
        out.append(customer);
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
    satisfactionScoreEdit_(nullptr),
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
    emailEdit_->setPlaceholderText("Email");

    phoneEdit_ = new QLineEdit(this);
    phoneEdit_->setPlaceholderText("Phone");

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

    satisfactionScoreEdit_ = new QDoubleSpinBox(this);
    satisfactionScoreEdit_->setRange(0.0, 100.0);
    satisfactionScoreEdit_->setDecimals(2);
    satisfactionScoreEdit_->setSingleStep(1.0);

    employeeIdEdit_ = new QSpinBox(this);
    employeeIdEdit_->setRange(0, 1000000000);
    employeeIdEdit_->setSpecialValueText("(none)");

    formLayout->addRow("Customer ID", customerIdEdit_);
    formLayout->addRow("Name", nameEdit_);
    formLayout->addRow("Email", emailEdit_);
    formLayout->addRow("Phone", phoneEdit_);
    formLayout->addRow("Address", addressEdit_);
    formLayout->addRow("Report Type", reportTypeEdit_);
    formLayout->addRow("Report Date", reportDateEdit_);
    formLayout->addRow("Satisfaction Score", satisfactionScoreEdit_);
    formLayout->addRow("Employee ID", employeeIdEdit_);

    buttonBox_ = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, this);
    connect(buttonBox_, &QDialogButtonBox::accepted, this, &AddCustomerDialog::onAccept);
    connect(buttonBox_, &QDialogButtonBox::rejected, this, &AddCustomerDialog::reject);

    clearButton_ = new QPushButton("Clear", this);
    connect(clearButton_, &QPushButton::clicked, this, &AddCustomerDialog::onClearClicked);

    layout->addLayout(formLayout);
    layout->addWidget(clearButton_);
    layout->addWidget(buttonBox_);
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
    phoneEdit_->clear();
    addressEdit_->clear();
    reportTypeEdit_->setCurrentIndex(0);
    reportDateEdit_->setDate(QDate::currentDate());
    satisfactionScoreEdit_->setValue(0.0);
    employeeIdEdit_->setValue(0);
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

    if (customer.reportDate().isValid()) {
        reportDateEdit_->setDate(customer.reportDate());
    }

    satisfactionScoreEdit_->setValue(customer.satisfactionScore());
    employeeIdEdit_->setValue(customer.employeeId());
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
        satisfactionScoreEdit_->value(),
        employeeIdEdit_->value());
}

void AddCustomerDialog::onAccept()
{
    if (!validateInput()) {
        return;
    }

    accept();
}

bool AddCustomerDialog::validateInput()
{
    if (customerIdEdit_->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Customer ID is required.");
        return false;
    }

    if (nameEdit_->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Name is required.");
        return false;
    }

    QString email = emailEdit_->text().trimmed();
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Email is required.");
        return false;
    }

    QRegularExpression emailRegex(R"(^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}$)");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Invalid email format.");
        return false;
    }

    QString phone = phoneEdit_->text().trimmed();
    if (!phone.isEmpty()) {
        QRegularExpression phoneRegex(R"(^\+?[0-9\-\s]{7,20}$)");
        if (!phoneRegex.match(phone).hasMatch()) {
            QMessageBox::warning(this, "Validation", "Invalid phone number format. Allowed: digits, spaces, dashes, optional +, min 7 digits.");
            return false;
        }
    }

    return true;
}

