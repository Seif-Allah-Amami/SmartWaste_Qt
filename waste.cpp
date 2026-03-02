#include "waste.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

Waste::Waste()
    : m_id(-1)
    , m_quantity(0)
    , m_weightKg(0.0)
{
}

Waste::Waste(int id,
             const QString &type,
             const QString &category,
             int quantity,
             double weightKg,
             const QDate &collectionDate,
             const QString &location,
             const QString &status)
    : m_id(id)
    , m_type(type)
    , m_category(category)
    , m_quantity(quantity)
    , m_weightKg(weightKg)
    , m_collectionDate(collectionDate)
    , m_location(location)
    , m_status(status)
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

bool Waste::create() const
{
    QSqlQuery query;
    query.prepare("INSERT INTO WASTE (WASTE_TYPE, CATEGORY, QUANTITY, WEIGHT_KG, COLLECTION_DATE, LOCATION, STATUS) "
                  "VALUES (:waste_type, :category, :quantity, :weight_kg, TO_DATE(:collection_date, 'YYYY-MM-DD'), :location, :status)");
    query.bindValue(":waste_type", m_type);
    query.bindValue(":category", m_category);
    query.bindValue(":quantity", m_quantity);
    query.bindValue(":weight_kg", m_weightKg);
    query.bindValue(":collection_date", m_collectionDate.toString("yyyy-MM-dd"));
    query.bindValue(":location", m_location);
    query.bindValue(":status", m_status);

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
    query.prepare("UPDATE WASTE SET WASTE_TYPE = :waste_type, CATEGORY = :category, QUANTITY = :quantity, "
                  "WEIGHT_KG = :weight_kg, COLLECTION_DATE = TO_DATE(:collection_date, 'YYYY-MM-DD'), LOCATION = :location, STATUS = :status "
                  "WHERE ID = :id");
    query.bindValue(":id", m_id);
    query.bindValue(":waste_type", m_type);
    query.bindValue(":category", m_category);
    query.bindValue(":quantity", m_quantity);
    query.bindValue(":weight_kg", m_weightKg);
    query.bindValue(":collection_date", m_collectionDate.toString("yyyy-MM-dd"));
    query.bindValue(":location", m_location);
    query.bindValue(":status", m_status);
    
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
    query.prepare("DELETE FROM WASTE WHERE ID = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QList<Waste> Waste::readAll()
{
    QList<Waste> records;

    QSqlQuery query;
    query.prepare("SELECT ID, WASTE_TYPE, CATEGORY, QUANTITY, WEIGHT_KG, "
                  "TO_CHAR(COLLECTION_DATE, 'YYYY-MM-DD') AS COLLECTION_DATE, LOCATION, STATUS "
                  "FROM WASTE ORDER BY ID DESC");

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
        records.append(waste);
    }

    return records;
}
