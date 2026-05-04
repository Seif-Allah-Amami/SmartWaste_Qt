#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QDate>
#include <QString>
#include <QList>

#include <QDialog>
#include <QComboBox>
#include <QPushButton>

class Customer
{
public:

    Customer();
    // Backward-compatible constructor for legacy code
    Customer(int customerId,
             const QString &name,
             const QString &email,
             const QString &phone,
             const QString &address,
             const QString &reportType,
             const QDate &reportDate,
             int employeeId);
    Customer(int customerId,
             const QString &name,
             const QString &email,
             const QString &phone,
             const QString &address,
             const QString &reportType,
             const QDate &reportDate,
             int employeeId,
             const QString &status);

    int customerId() const;
    void setCustomerId(int customerId);

    QString name() const;
    void setName(const QString &name);

    QString email() const;
    void setEmail(const QString &email);

    QString phone() const;
    void setPhone(const QString &phone);

    QString address() const;
    void setAddress(const QString &address);

    QString reportType() const;
    void setReportType(const QString &reportType);

    QDate reportDate() const;
    void setReportDate(const QDate &reportDate);

    int employeeId() const;
    void setEmployeeId(int employeeId);

    QString status() const;
    void setStatus(const QString &status);

    // ==================== CRUD OPERATIONS ====================

    // CREATE: Insert a new customer into the database
    bool add(QString *errorMessage = nullptr) const;

    // READ: Retrieve a single customer by ID
    static bool getById(int customerId, Customer &out, QString *errorMessage = nullptr);

    // READ: Retrieve all customers from the database
    static bool fetchAll(QList<Customer> &out, QString *errorMessage = nullptr);

    // UPDATE: Modify an existing customer record
    bool update(QString *errorMessage = nullptr) const;

    // DELETE: Remove a customer from the database
    static bool remove(int customerId, QString *errorMessage = nullptr);

private:
    int customerId_;
    QString name_;
    QString email_;
    QString phone_;
    QString address_;
    QString reportType_;
    QDate reportDate_;
    int employeeId_;
    // Status attribute: canonical values are "pending", "solved", "in progress", "rejected"
    QString status_;
};

class QLineEdit;
class QDateEdit;
class QDialogButtonBox;

class AddCustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomerDialog(QWidget *parent = nullptr);

    void setCustomer(const Customer &customer);
    Customer customer() const;

private slots:
    void onAccept();
    void onClearClicked();
    void onPhoneTextChanged(const QString &text);

private:
    void buildUi();
    void populateEmployeeList();
    bool validateInput();
    void clearFields();

    QLineEdit *customerIdEdit_;
    QLineEdit *nameEdit_;
    QLineEdit *emailEdit_;
    QLineEdit *phoneEdit_;
    QLineEdit *addressEdit_;
    QComboBox *reportTypeEdit_;
    QDateEdit *reportDateEdit_;
    QComboBox *employeeIdEdit_;
    QComboBox *statusEdit_;
    QDialogButtonBox *buttonBox_;
    QPushButton *clearButton_;

    bool isEdit_;
};

#endif // CUSTOMER_H
