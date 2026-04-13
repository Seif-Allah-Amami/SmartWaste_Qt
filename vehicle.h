#ifndef VEHICLE_H
#define VEHICLE_H

#include <QDate>
#include <QList>
#include <QString>

class Vehicle
{
public:
    Vehicle();
    Vehicle(int idVehicle,
            const QString &plateNum,
            const QString &type,
            const QString &model,
            const QString &fuelType,
            const QString &status,
            const QDate &nextMaintenance,
            int employeeId);

    int idVehicle() const;
    void setIdVehicle(int idVehicle);

    QString plateNum() const;
    void setPlateNum(const QString &plateNum);

    QString type() const;
    void setType(const QString &type);

    QString model() const;
    void setModel(const QString &model);

    QString fuelType() const;
    void setFuelType(const QString &fuelType);

    QString status() const;
    void setStatus(const QString &status);

    QDate nextMaintenance() const;
    void setNextMaintenance(const QDate &nextMaintenance);

    int employeeId() const;
    void setEmployeeId(int employeeId);

    bool create() const;
    bool update() const;
    static QList<Vehicle> readAll();
    static bool remove(int idVehicle);
    static QString lastError();

private:
    static bool ensureDbOpen();
    static bool ensureEmployeeExists(int employeeId);
    static QString s_lastError;

    int m_idVehicle;
    QString m_plateNum;
    QString m_type;
    QString m_model;
    QString m_fuelType;
    QString m_status;
    QDate m_nextMaintenance;
    int m_employeeId;
};

#endif // VEHICLE_H
