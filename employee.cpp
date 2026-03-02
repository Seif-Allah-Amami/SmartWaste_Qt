#include "employee.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

Employee::Employee()
    : m_id(-1)
    , m_salary(0.0)
{
}

Employee::Employee(int id,
                   const QString &fullName,
                   const QString &email,
                   const QString &position,
                   const QString &department,
                   const QDate &hireDate,
                   double salary)
    : m_id(id)
    , m_fullName(fullName)
    , m_email(email)
    , m_position(position)
    , m_department(department)
    , m_hireDate(hireDate)
    , m_salary(salary)
{
}

int Employee::id() const
{
    return m_id;
}

QString Employee::fullName() const
{
    return m_fullName;
}

QString Employee::email() const
{
    return m_email;
}

QString Employee::position() const
{
    return m_position;
}

QString Employee::department() const
{
    return m_department;
}

QDate Employee::hireDate() const
{
    return m_hireDate;
}

double Employee::salary() const
{
    return m_salary;
}

void Employee::setId(int id)
{
    m_id = id;
}

void Employee::setFullName(const QString &fullName)
{
    m_fullName = fullName;
}

void Employee::setEmail(const QString &email)
{
    m_email = email;
}

void Employee::setPosition(const QString &position)
{
    m_position = position;
}

void Employee::setDepartment(const QString &department)
{
    m_department = department;
}

void Employee::setHireDate(const QDate &hireDate)
{
    m_hireDate = hireDate;
}

void Employee::setSalary(double salary)
{
    m_salary = salary;
}

bool Employee::create() const
{
    QSqlQuery query;
    query.prepare("INSERT INTO employees (full_name, email, position, department, hire_date, salary) "
                  "VALUES (:full_name, :email, :position, :department, :hire_date, :salary)");
    query.bindValue(":full_name", m_fullName);
    query.bindValue(":email", m_email);
    query.bindValue(":position", m_position);
    query.bindValue(":department", m_department);
    query.bindValue(":hire_date", m_hireDate.toString("yyyy-MM-dd"));
    query.bindValue(":salary", m_salary);

    return query.exec();
}

bool Employee::update() const
{
    if (m_id <= 0) {
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE employees SET full_name = :full_name, email = :email, position = :position, "
                  "department = :department, hire_date = :hire_date, salary = :salary WHERE id = :id");
    query.bindValue(":id", m_id);
    query.bindValue(":full_name", m_fullName);
    query.bindValue(":email", m_email);
    query.bindValue(":position", m_position);
    query.bindValue(":department", m_department);
    query.bindValue(":hire_date", m_hireDate.toString("yyyy-MM-dd"));
    query.bindValue(":salary", m_salary);

    return query.exec();
}

bool Employee::remove(int id)
{
    if (id <= 0) {
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM employees WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QList<Employee> Employee::readAll()
{
    QList<Employee> employees;

    QSqlQuery query;
    query.prepare("SELECT id, full_name, email, position, department, hire_date, salary "
                  "FROM employees ORDER BY id DESC");

    if (!query.exec()) {
        return employees;
    }

    while (query.next()) {
        Employee employee;
        employee.setId(query.value("id").toInt());
        employee.setFullName(query.value("full_name").toString());
        employee.setEmail(query.value("email").toString());
        employee.setPosition(query.value("position").toString());
        employee.setDepartment(query.value("department").toString());
        employee.setHireDate(QDate::fromString(query.value("hire_date").toString(), "yyyy-MM-dd"));
        employee.setSalary(query.value("salary").toDouble());
        employees.append(employee);
    }

    return employees;
}
