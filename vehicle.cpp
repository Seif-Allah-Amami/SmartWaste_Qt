#include "vehicle.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

QString Vehicle::s_lastError;

bool Vehicle::ensureDbOpen()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        s_lastError = "Database not open.";
        return false;
    }
    return true;
}

bool Vehicle::ensureEmployeeExists(int employeeId)
{
    if (employeeId <= 0) {
        return true;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT 1 FROM EMPLOYEE WHERE EMPLOYEE_ID = :employee_id");
    checkQuery.bindValue(":employee_id", employeeId);

    if (!checkQuery.exec()) {
        s_lastError = checkQuery.lastError().text();
        return false;
    }

    if (checkQuery.next()) {
        return true;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO EMPLOYEE (EMPLOYEE_ID) VALUES (:employee_id)");
    insertQuery.bindValue(":employee_id", employeeId);

    if (!insertQuery.exec()) {
        s_lastError = insertQuery.lastError().text();
        return false;
    }

    return true;
}

Vehicle::Vehicle()
    : m_idVehicle(0)
    , m_employeeId(0)
{
}

Vehicle::Vehicle(int idVehicle,
                 const QString &plateNum,
                 const QString &type,
                 const QString &model,
                 const QString &fuelType,
                 const QString &status,
                 const QDate &nextMaintenance,
                 int employeeId)
    : m_idVehicle(idVehicle)
    , m_plateNum(plateNum)
    , m_type(type)
    , m_model(model)
    , m_fuelType(fuelType)
    , m_status(status)
    , m_nextMaintenance(nextMaintenance)
    , m_employeeId(employeeId)
{
}

int Vehicle::idVehicle() const
{
    return m_idVehicle;
}

void Vehicle::setIdVehicle(int idVehicle)
{
    m_idVehicle = idVehicle;
}

QString Vehicle::plateNum() const
{
    return m_plateNum;
}

void Vehicle::setPlateNum(const QString &plateNum)
{
    m_plateNum = plateNum;
}

QString Vehicle::type() const
{
    return m_type;
}

void Vehicle::setType(const QString &type)
{
    m_type = type;
}

QString Vehicle::model() const
{
    return m_model;
}

void Vehicle::setModel(const QString &model)
{
    m_model = model;
}

QString Vehicle::fuelType() const
{
    return m_fuelType;
}

void Vehicle::setFuelType(const QString &fuelType)
{
    m_fuelType = fuelType;
}

QString Vehicle::status() const
{
    return m_status;
}

void Vehicle::setStatus(const QString &status)
{
    m_status = status;
}

QDate Vehicle::nextMaintenance() const
{
    return m_nextMaintenance;
}

void Vehicle::setNextMaintenance(const QDate &nextMaintenance)
{
    m_nextMaintenance = nextMaintenance;
}

int Vehicle::employeeId() const
{
    return m_employeeId;
}

void Vehicle::setEmployeeId(int employeeId)
{
    m_employeeId = employeeId;
}

bool Vehicle::create() const
{
    if (!ensureDbOpen()) {
        qWarning() << "Vehicle::create" << s_lastError;
        return false;
    }

    if (!ensureEmployeeExists(m_employeeId)) {
        qWarning() << "Vehicle::create" << s_lastError;
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO VEHICLE (ID_VEHICLE, PLATE_NUM, TYPE, MODEL, FUEL_TYPE, STATUS, NEXT_MAINTENANCE, EMPLOYEE_ID) "
                  "VALUES (:id_vehicle, :plate_num, :type, :model, :fuel_type, :status, :next_maintenance, :employee_id)");

    query.bindValue(":id_vehicle", m_idVehicle);
    query.bindValue(":plate_num", m_plateNum);
    query.bindValue(":type", m_type);
    query.bindValue(":model", m_model);
    query.bindValue(":fuel_type", m_fuelType);
    query.bindValue(":status", m_status);

    if (m_nextMaintenance.isValid()) {
        query.bindValue(":next_maintenance", m_nextMaintenance);
    } else {
        query.bindValue(":next_maintenance", QVariant(QVariant::Date));
    }

    if (m_employeeId > 0) {
        query.bindValue(":employee_id", m_employeeId);
    } else {
        query.bindValue(":employee_id", QVariant(QVariant::Int));
    }

    if (!query.exec()) {
        s_lastError = query.lastError().text();
        qWarning() << "Vehicle::create" << s_lastError;
        return false;
    }

    s_lastError.clear();
    return true;
}

bool Vehicle::update() const
{
    if (!ensureDbOpen()) {
        qWarning() << "Vehicle::update" << s_lastError;
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE VEHICLE SET PLATE_NUM = :plate_num, TYPE = :type, MODEL = :model, "
                  "FUEL_TYPE = :fuel_type, STATUS = :status, NEXT_MAINTENANCE = :next_maintenance, "
                  "EMPLOYEE_ID = :employee_id WHERE ID_VEHICLE = :id_vehicle");

    query.bindValue(":id_vehicle", m_idVehicle);
    query.bindValue(":plate_num", m_plateNum);
    query.bindValue(":type", m_type);
    query.bindValue(":model", m_model);
    query.bindValue(":fuel_type", m_fuelType);
    query.bindValue(":status", m_status);

    if (m_nextMaintenance.isValid()) {
        query.bindValue(":next_maintenance", m_nextMaintenance);
    } else {
        query.bindValue(":next_maintenance", QVariant(QVariant::Date));
    }

    if (m_employeeId > 0) {
        query.bindValue(":employee_id", m_employeeId);
    } else {
        query.bindValue(":employee_id", QVariant(QVariant::Int));
    }

    if (!query.exec()) {
        s_lastError = query.lastError().text();
        qWarning() << "Vehicle::update" << s_lastError;
        return false;
    }

    s_lastError.clear();
    return true;
}

QList<Vehicle> Vehicle::readAll()
{
    QList<Vehicle> vehicles;
    if (!ensureDbOpen()) {
        qWarning() << "Vehicle::readAll" << s_lastError;
        return vehicles;
    }

    QSqlQuery query;
    if (!query.exec("SELECT ID_VEHICLE, PLATE_NUM, TYPE, MODEL, FUEL_TYPE, STATUS, NEXT_MAINTENANCE, EMPLOYEE_ID "
                    "FROM VEHICLE ORDER BY ID_VEHICLE")) {
        s_lastError = query.lastError().text();
        qWarning() << "Vehicle::readAll" << s_lastError;
        return vehicles;
    }

    while (query.next()) {
        Vehicle vehicle;
        vehicle.setIdVehicle(query.value("ID_VEHICLE").toInt());
        vehicle.setPlateNum(query.value("PLATE_NUM").toString());
        vehicle.setType(query.value("TYPE").toString());
        vehicle.setModel(query.value("MODEL").toString());
        vehicle.setFuelType(query.value("FUEL_TYPE").toString());
        vehicle.setStatus(query.value("STATUS").toString());
        vehicle.setNextMaintenance(query.value("NEXT_MAINTENANCE").toDate());
        vehicle.setEmployeeId(query.value("EMPLOYEE_ID").toInt());
        vehicles.append(vehicle);
    }

    s_lastError.clear();
    return vehicles;
}

bool Vehicle::remove(int idVehicle)
{
    if (!ensureDbOpen()) {
        qWarning() << "Vehicle::remove" << s_lastError;
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM VEHICLE WHERE ID_VEHICLE = :id_vehicle");
    query.bindValue(":id_vehicle", idVehicle);

    if (!query.exec()) {
        s_lastError = query.lastError().text();
        qWarning() << "Vehicle::remove" << s_lastError;
        return false;
    }

    s_lastError.clear();
    return true;
}

QString Vehicle::lastError()
{
    return s_lastError;
}
