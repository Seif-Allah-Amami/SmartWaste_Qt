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
             double salary);

    int id() const;
    QString fullName() const;
    QString email() const;
    QString position() const;
    QString department() const;
    QDate hireDate() const;
    double salary() const;

    void setId(int id);
    void setFullName(const QString &fullName);
    void setEmail(const QString &email);
    void setPosition(const QString &position);
    void setDepartment(const QString &department);
    void setHireDate(const QDate &hireDate);
    void setSalary(double salary);

    bool create() const;
    bool update() const;
    static bool remove(int id);
    static QList<Employee> readAll();

private:
    int m_id;
    QString m_fullName;
    QString m_email;
    QString m_position;
    QString m_department;
    QDate m_hireDate;
    double m_salary;
};

#endif // EMPLOYEE_H
