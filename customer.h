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
             double satisfactionScore,
             int employeeId);
    Customer(int customerId,
             const QString &name,
             const QString &email,
             const QString &phone,
             const QString &address,
             const QString &reportType,
             const QDate &reportDate,
             double satisfactionScore,
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

    double satisfactionScore() const;
    void setSatisfactionScore(double satisfactionScore);

    int employeeId() const;
    void setEmployeeId(int employeeId);

    QString status() const;
    void setStatus(const QString &status);

    bool add(QString *errorMessage = nullptr) const;
    bool update(QString *errorMessage = nullptr) const;

    static bool remove(int customerId, QString *errorMessage = nullptr);
    static bool fetchAll(QList<Customer> &out, QString *errorMessage = nullptr);

private:
    int customerId_;
    QString name_;
    QString email_;
    QString phone_;
    QString address_;
    QString reportType_;
    QDate reportDate_;
    double satisfactionScore_;
    int employeeId_;
    // Status attribute: allowed values are "pending", "resolved", "in progress", "rejected"
    QString status_;
};

class QLineEdit;
class QDateEdit;
class QDoubleSpinBox;
class QSpinBox;
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

private:
    void buildUi();
    bool validateInput();
    void clearFields();

    QLineEdit *customerIdEdit_;
    QLineEdit *nameEdit_;
    QLineEdit *emailEdit_;
    QLineEdit *phoneEdit_;
    QLineEdit *addressEdit_;
    QComboBox *reportTypeEdit_;
    QDateEdit *reportDateEdit_;
    QDoubleSpinBox *satisfactionScoreEdit_;
    QSpinBox *employeeIdEdit_;
    QComboBox *statusEdit_;
    QDialogButtonBox *buttonBox_;
    QPushButton *clearButton_;

    bool isEdit_;
};

#endif // CUSTOMER_H
