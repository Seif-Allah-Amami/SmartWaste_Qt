#include "employee.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QRegularExpression>
#include <QDate>

Employee::Employee()
    : m_id(-1)
    , m_salary(0.0)
    , m_idMachine(0)
    , m_idSupplier(0)
{
}

Employee::Employee(int id,
                   const QString &fullName,
                   const QString &email,
                   const QString &position,
                   const QString &department,
                   const QDate &hireDate,
                   double salary,
                   int idMachine,
                   int idSupplier)
    : m_id(id)
    , m_fullName(fullName)
    , m_email(email)
    , m_position(position)
    , m_department(department)
    , m_hireDate(hireDate)
    , m_salary(salary)
    , m_idMachine(idMachine)
    , m_idSupplier(idSupplier)
{
}

int     Employee::id()         const { return m_id; }
QString Employee::fullName()   const { return m_fullName; }
QString Employee::email()      const { return m_email; }
QString Employee::position()   const { return m_position; }
QString Employee::department() const { return m_department; }
QDate   Employee::hireDate()   const { return m_hireDate; }
double  Employee::salary()     const { return m_salary; }
int     Employee::idMachine()  const { return m_idMachine; }
int     Employee::idSupplier() const { return m_idSupplier; }

void Employee::setId(int id)                        { m_id = id; }
void Employee::setFullName(const QString &fullName) { m_fullName = fullName; }
void Employee::setEmail(const QString &email)       { m_email = email; }
void Employee::setPosition(const QString &position) { m_position = position; }
void Employee::setDepartment(const QString &dept)   { m_department = dept; }
void Employee::setHireDate(const QDate &hireDate)   { m_hireDate = hireDate; }
void Employee::setSalary(double salary)             { m_salary = salary; }
void Employee::setIdMachine(int idMachine)          { m_idMachine = idMachine; }
void Employee::setIdSupplier(int idSupplier)        { m_idSupplier = idSupplier; }

QString Employee::lastError()
{
    return m_lastError;
}

QString Employee::m_lastError = "";

bool Employee::machineExists(int machineId)
{
    if (machineId <= 0) return true; // 0 means no machine assigned, allow it
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM MACHINE WHERE ID_MACHINE = :id");
    query.bindValue(":id", machineId);
    if (!query.exec() || !query.next()) return false;
    return query.value(0).toInt() > 0;
}

bool Employee::supplierExists(int supplierId)
{
    if (supplierId <= 0) return true; // 0 means no supplier assigned, allow it
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SUPPLIER WHERE ID_SUPPLIER = :id");
    query.bindValue(":id", supplierId);
    if (!query.exec() || !query.next()) return false;
    return query.value(0).toInt() > 0;
}

bool Employee::isValidEmail(const QString &email)
{
    // Email format validation: must contain @ and at least one . after @
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return emailRegex.match(email).hasMatch();
}

bool Employee::isValidSalary(double salary)
{
    // Salary must be non-negative and reasonable (not exceeding 10 million)
    return salary >= 0.0 && salary <= 10000000.0;
}

bool Employee::isValidHireDate(const QDate &hireDate)
{
    // Hire date must be valid and not in the future
    if (!hireDate.isValid()) return false;
    return hireDate <= QDate::currentDate();
}

bool Employee::isValidName(const QString &name)
{
    // Name must be 2-100 characters and contain only letters, spaces, and hyphens
    if (name.length() < 2 || name.length() > 100) return false;
    QRegularExpression nameRegex("^[a-zA-Z\\s\\-']+$");
    return nameRegex.match(name).hasMatch();
}

bool Employee::create() const
{
    if (m_id <= 0) {
        m_lastError = "Employee ID must be greater than 0.";
        return false;
    }

    // Check if employee ID already exists
    QSqlQuery checkId;
    checkId.prepare("SELECT COUNT(*) FROM EMPLOYEE WHERE EMPLOYEE_ID = :id");
    checkId.bindValue(":id", m_id);
    if (checkId.exec() && checkId.next() && checkId.value(0).toInt() > 0) {
        m_lastError = QString("Employee ID %1 already exists. Please use a different ID.").arg(m_id);
        return false;
    }

    // Validate machine ID exists
    if (!machineExists(m_idMachine)) {
        m_lastError = QString("Machine ID %1 does not exist. Please enter a valid Machine ID.").arg(m_idMachine);
        return false;
    }

    // Validate supplier ID exists
    if (!supplierExists(m_idSupplier)) {
        m_lastError = QString("Supplier ID %1 does not exist. Please enter a valid Supplier ID.").arg(m_idSupplier);
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYEE (EMPLOYEE_ID, FULL_NAME, EMAIL, POSITION, DEPARTMENT, HIRE_DATE, SALARY, ID_MACHINE, ID_SUPPLIER) "
                  "VALUES (:employee_id, :full_name, :email, :position, :department, :hire_date, :salary, :id_machine, :id_supplier)");
    query.bindValue(":employee_id", m_id);
    query.bindValue(":full_name",   m_fullName);
    query.bindValue(":email",       m_email);
    query.bindValue(":position",    m_position);
    query.bindValue(":department",  m_department);
    query.bindValue(":hire_date",   m_hireDate);
    query.bindValue(":salary",      m_salary);
    query.bindValue(":id_machine",  m_idMachine > 0 ? QVariant(m_idMachine) : QVariant());
    query.bindValue(":id_supplier", m_idSupplier > 0 ? QVariant(m_idSupplier) : QVariant());

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool Employee::update() const
{
    if (m_id <= 0) {
        m_lastError = "Employee ID must be greater than 0.";
        return false;
    }

    // Validate machine ID exists
    if (!machineExists(m_idMachine)) {
        m_lastError = QString("Machine ID %1 does not exist. Please enter a valid Machine ID.").arg(m_idMachine);
        return false;
    }

    // Validate supplier ID exists
    if (!supplierExists(m_idSupplier)) {
        m_lastError = QString("Supplier ID %1 does not exist. Please enter a valid Supplier ID.").arg(m_idSupplier);
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEE SET FULL_NAME = :full_name, EMAIL = :email, POSITION = :position, "
                  "DEPARTMENT = :department, HIRE_DATE = :hire_date, SALARY = :salary, "
                  "ID_MACHINE = :id_machine, ID_SUPPLIER = :id_supplier "
                  "WHERE EMPLOYEE_ID = :id");
    query.bindValue(":id",          m_id);
    query.bindValue(":full_name",   m_fullName);
    query.bindValue(":email",       m_email);
    query.bindValue(":position",    m_position);
    query.bindValue(":department",  m_department);
    query.bindValue(":hire_date",   m_hireDate);
    query.bindValue(":salary",      m_salary);
    query.bindValue(":id_machine",  m_idMachine > 0 ? QVariant(m_idMachine) : QVariant());
    query.bindValue(":id_supplier", m_idSupplier > 0 ? QVariant(m_idSupplier) : QVariant());

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool Employee::remove(int id)
{
    if (id <= 0) {
        m_lastError = "Invalid employee ID.";
        return false;
    }

    // Check if any vehicles are assigned to this employee
    QSqlQuery checkVehicle;
    checkVehicle.prepare("SELECT COUNT(*) FROM VEHICLE WHERE EMPLOYEE_ID = :id");
    checkVehicle.bindValue(":id", id);
    if (checkVehicle.exec() && checkVehicle.next() && checkVehicle.value(0).toInt() > 0) {
        m_lastError = "Cannot delete this employee because they have vehicles assigned to them.\n"
                      "Please reassign or delete those vehicles first.";
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYEE WHERE EMPLOYEE_ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

QList<Employee> Employee::readAll()
{
    QList<Employee> employees;

    QSqlQuery query;
    query.prepare("SELECT EMPLOYEE_ID, FULL_NAME, EMAIL, POSITION, DEPARTMENT, HIRE_DATE, SALARY, ID_MACHINE, ID_SUPPLIER "
                  "FROM EMPLOYEE ORDER BY EMPLOYEE_ID DESC");

    if (!query.exec()) return employees;

    while (query.next()) {
        Employee employee;
        employee.setId(query.value("EMPLOYEE_ID").toInt());
        employee.setFullName(query.value("FULL_NAME").toString());
        employee.setEmail(query.value("EMAIL").toString());
        employee.setPosition(query.value("POSITION").toString());
        employee.setDepartment(query.value("DEPARTMENT").toString());
        employee.setHireDate(query.value("HIRE_DATE").toDate());
        employee.setSalary(query.value("SALARY").toDouble());
        employee.setIdMachine(query.value("ID_MACHINE").toInt());
        employee.setIdSupplier(query.value("ID_SUPPLIER").toInt());
        employees.append(employee);
    }

    return employees;
}
