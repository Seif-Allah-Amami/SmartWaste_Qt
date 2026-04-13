#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QDate>
#include <QList>
#include <QString>

class Employee
{
public:
    Employee();
    Employee(int id,
             const QString &fullName,
             const QString &email,
             const QString &position,
             const QString &department,
             const QDate &hireDate,
             double salary,
             int idMachine,
             int idSupplier);

    // Getters
    int     id()         const;
    QString fullName()   const;
    QString email()      const;
    QString position()   const;
    QString department() const;
    QDate   hireDate()   const;
    double  salary()     const;
    int     idMachine()  const;
    int     idSupplier() const;

    // Setters
    void setId(int id);
    void setFullName(const QString &fullName);
    void setEmail(const QString &email);
    void setPosition(const QString &position);
    void setDepartment(const QString &department);
    void setHireDate(const QDate &hireDate);
    void setSalary(double salary);
    void setIdMachine(int idMachine);
    void setIdSupplier(int idSupplier);

    // CRUD
    bool create() const;
    bool update() const;
    static bool remove(int id);
    static QList<Employee> readAll();

    // Error handling
    static QString lastError();

    // Validation helpers (public)
    static bool machineExists(int machineId);
    static bool supplierExists(int supplierId);
    static bool isValidEmail(const QString &email);
    static bool isValidSalary(double salary);
    static bool isValidHireDate(const QDate &hireDate);
    static bool isValidName(const QString &name);

private:
    int     m_id;
    QString m_fullName;
    QString m_email;
    QString m_position;
    QString m_department;
    QDate   m_hireDate;
    double  m_salary;
    int     m_idMachine;
    int     m_idSupplier;

    static QString m_lastError;
};

#endif // EMPLOYEE_H
