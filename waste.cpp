#include "waste.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
<<<<<<< HEAD
=======
#include <QVariant>

namespace {
QString resolveWasteIdColumn()
{
    static QString cached;
    if (!cached.isEmpty()) {
        return cached;
    }

    QSqlQuery query;
    query.prepare(
        "SELECT cols.column_name "
        "FROM user_constraints cons "
        "JOIN user_cons_columns cols "
        "  ON cons.constraint_name = cols.constraint_name "
        " AND cons.owner = cols.owner "
        "WHERE cons.constraint_type = 'P' "
        "  AND cons.table_name = 'WASTE' "
        "ORDER BY cols.position");
    if (query.exec() && query.next()) {
        cached = query.value(0).toString();
        if (!cached.isEmpty()) {
            return cached;
        }
    }

    query.prepare("SELECT column_name FROM user_tab_columns WHERE table_name = 'WASTE' AND column_name IN ('WASTE_ID', 'ID', 'ID_WASTE')");
    if (query.exec()) {
        while (query.next()) {
            const QString name = query.value(0).toString();
            if (name == "WASTE_ID") {
                cached = name;
                return cached;
            }
            if (cached.isEmpty()) {
                cached = name;
            }
        }
    }

    if (cached.isEmpty()) {
        cached = "ID";
    }
    return cached;
}
}
>>>>>>> 5be580a (waste X Arduino)

Waste::Waste()
    : m_id(-1)
    , m_quantity(0)
    , m_weightKg(0.0)
<<<<<<< HEAD
=======
    , m_humidityPercent(-1)
    , m_distanceCm(-1)
>>>>>>> 5be580a (waste X Arduino)
{
}

Waste::Waste(int id,
             const QString &type,
             const QString &category,
             int quantity,
             double weightKg,
             const QDate &collectionDate,
             const QString &location,
<<<<<<< HEAD
             const QString &status)
=======
             const QString &status,
             int humidityPercent,
             int distanceCm)
>>>>>>> 5be580a (waste X Arduino)
    : m_id(id)
    , m_type(type)
    , m_category(category)
    , m_quantity(quantity)
    , m_weightKg(weightKg)
    , m_collectionDate(collectionDate)
    , m_location(location)
    , m_status(status)
<<<<<<< HEAD
=======
    , m_humidityPercent(humidityPercent)
    , m_distanceCm(distanceCm)
>>>>>>> 5be580a (waste X Arduino)
{
}

int Waste::id() const
{
    return m_id;
}

QString Waste::type() const
{
    return m_type;
}

QString Waste::category() const
{
    return m_category;
}

int Waste::quantity() const
{
    return m_quantity;
}

double Waste::weightKg() const
{
    return m_weightKg;
}

QDate Waste::collectionDate() const
{
    return m_collectionDate;
}

QString Waste::location() const
{
    return m_location;
}

QString Waste::status() const
{
    return m_status;
}

<<<<<<< HEAD
=======
int Waste::humidityPercent() const
{
    return m_humidityPercent;
}

int Waste::distanceCm() const
{
    return m_distanceCm;
}

>>>>>>> 5be580a (waste X Arduino)
void Waste::setId(int id)
{
    m_id = id;
}

void Waste::setType(const QString &type)
{
    m_type = type;
}

void Waste::setCategory(const QString &category)
{
    m_category = category;
}

void Waste::setQuantity(int quantity)
{
    m_quantity = quantity;
}

void Waste::setWeightKg(double weightKg)
{
    m_weightKg = weightKg;
}

void Waste::setCollectionDate(const QDate &collectionDate)
{
    m_collectionDate = collectionDate;
}

void Waste::setLocation(const QString &location)
{
    m_location = location;
}

void Waste::setStatus(const QString &status)
{
    m_status = status;
}

<<<<<<< HEAD
bool Waste::create() const
{
    QSqlQuery query;
    query.prepare("INSERT INTO WASTE (WASTE_TYPE, CATEGORY, QUANTITY, WEIGHT_KG, COLLECTION_DATE, LOCATION, STATUS) "
                  "VALUES (:waste_type, :category, :quantity, :weight_kg, TO_DATE(:collection_date, 'YYYY-MM-DD'), :location, :status)");
=======
void Waste::setHumidityPercent(int humidityPercent)
{
    m_humidityPercent = humidityPercent;
}

void Waste::setDistanceCm(int distanceCm)
{
    m_distanceCm = distanceCm;
}

bool Waste::create() const
{
    QSqlQuery query;
    query.prepare("INSERT INTO WASTE (WASTE_TYPE, CATEGORY, QUANTITY, WEIGHT_KG, COLLECTION_DATE, LOCATION, STATUS, HUMIDITY_PERCENT, DISTANCE_CM) "
                  "VALUES (:waste_type, :category, :quantity, :weight_kg, TO_DATE(:collection_date, 'YYYY-MM-DD'), :location, :status, :humidity_percent, :distance_cm)");
>>>>>>> 5be580a (waste X Arduino)
    query.bindValue(":waste_type", m_type);
    query.bindValue(":category", m_category);
    query.bindValue(":quantity", m_quantity);
    query.bindValue(":weight_kg", m_weightKg);
    query.bindValue(":collection_date", m_collectionDate.toString("yyyy-MM-dd"));
    query.bindValue(":location", m_location);
    query.bindValue(":status", m_status);
<<<<<<< HEAD
=======
    query.bindValue(":humidity_percent", m_humidityPercent >= 0 ? QVariant(m_humidityPercent) : QVariant(QVariant::Int));
    query.bindValue(":distance_cm", m_distanceCm >= 0 ? QVariant(m_distanceCm) : QVariant(QVariant::Int));
>>>>>>> 5be580a (waste X Arduino)

    bool result = query.exec();
    if (!result) {
        qDebug() << "CREATE WASTE ERROR:" << query.lastError().text();
        qDebug() << "Query:" << query.executedQuery();
    } else {
        qDebug() << "Waste record created successfully";
    }
    return result;
}

bool Waste::update() const
{
    if (m_id <= 0) {
        return false;
    }

    QSqlQuery query;
<<<<<<< HEAD
    query.prepare("UPDATE WASTE SET WASTE_TYPE = :waste_type, CATEGORY = :category, QUANTITY = :quantity, "
                  "WEIGHT_KG = :weight_kg, COLLECTION_DATE = TO_DATE(:collection_date, 'YYYY-MM-DD'), LOCATION = :location, STATUS = :status "
                  "WHERE ID = :id");
=======
    const QString idColumn = resolveWasteIdColumn();
    query.prepare(QString("UPDATE WASTE SET WASTE_TYPE = :waste_type, CATEGORY = :category, QUANTITY = :quantity, "
                          "WEIGHT_KG = :weight_kg, COLLECTION_DATE = TO_DATE(:collection_date, 'YYYY-MM-DD'), LOCATION = :location, STATUS = :status, "
                          "HUMIDITY_PERCENT = :humidity_percent, DISTANCE_CM = :distance_cm "
                          "WHERE %1 = :id").arg(idColumn));
>>>>>>> 5be580a (waste X Arduino)
    query.bindValue(":id", m_id);
    query.bindValue(":waste_type", m_type);
    query.bindValue(":category", m_category);
    query.bindValue(":quantity", m_quantity);
    query.bindValue(":weight_kg", m_weightKg);
    query.bindValue(":collection_date", m_collectionDate.toString("yyyy-MM-dd"));
    query.bindValue(":location", m_location);
    query.bindValue(":status", m_status);
<<<<<<< HEAD
    
=======
    query.bindValue(":humidity_percent", m_humidityPercent >= 0 ? QVariant(m_humidityPercent) : QVariant(QVariant::Int));
    query.bindValue(":distance_cm", m_distanceCm >= 0 ? QVariant(m_distanceCm) : QVariant(QVariant::Int));

>>>>>>> 5be580a (waste X Arduino)
    bool result = query.exec();
    if (!result) {
        qDebug() << "UPDATE WASTE ERROR:" << query.lastError().text();
    }
    return result;
}

bool Waste::remove(int id)
{
    if (id <= 0) {
        return false;
    }

    QSqlQuery query;
<<<<<<< HEAD
    query.prepare("DELETE FROM WASTE WHERE ID = :id");
=======
    const QString idColumn = resolveWasteIdColumn();
    query.prepare(QString("DELETE FROM WASTE WHERE %1 = :id").arg(idColumn));
>>>>>>> 5be580a (waste X Arduino)
    query.bindValue(":id", id);
    return query.exec();
}

QList<Waste> Waste::readAll()
{
    QList<Waste> records;

    QSqlQuery query;
<<<<<<< HEAD
    query.prepare("SELECT ID, WASTE_TYPE, CATEGORY, QUANTITY, WEIGHT_KG, "
                  "TO_CHAR(COLLECTION_DATE, 'YYYY-MM-DD') AS COLLECTION_DATE, LOCATION, STATUS "
                  "FROM WASTE ORDER BY ID DESC");
=======
    const QString idColumn = resolveWasteIdColumn();
    query.prepare(QString("SELECT %1 AS ID, WASTE_TYPE, CATEGORY, QUANTITY, WEIGHT_KG, "
                          "TO_CHAR(COLLECTION_DATE, 'YYYY-MM-DD') AS COLLECTION_DATE, LOCATION, STATUS, "
                          "HUMIDITY_PERCENT, DISTANCE_CM "
                          "FROM WASTE ORDER BY %1 DESC").arg(idColumn));
>>>>>>> 5be580a (waste X Arduino)

    if (!query.exec()) {
        qDebug() << "Error reading waste records:" << query.lastError().text();
        return records;
    }

    while (query.next()) {
        Waste waste;
        waste.setId(query.value("ID").toInt());
        waste.setType(query.value("WASTE_TYPE").toString());
        waste.setCategory(query.value("CATEGORY").toString());
        waste.setQuantity(query.value("QUANTITY").toInt());
        waste.setWeightKg(query.value("WEIGHT_KG").toDouble());
        waste.setCollectionDate(QDate::fromString(query.value("COLLECTION_DATE").toString(), "yyyy-MM-dd"));
        waste.setLocation(query.value("LOCATION").toString());
        waste.setStatus(query.value("STATUS").toString());
<<<<<<< HEAD
=======
        waste.setHumidityPercent(query.value("HUMIDITY_PERCENT").isNull() ? -1 : query.value("HUMIDITY_PERCENT").toInt());
        waste.setDistanceCm(query.value("DISTANCE_CM").isNull() ? -1 : query.value("DISTANCE_CM").toInt());
>>>>>>> 5be580a (waste X Arduino)
        records.append(waste);
    }

    return records;
}
