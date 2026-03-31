#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QVariant>

#include "machine.h"

Machine::Machine() {}

Machine::Machine(const QString &name, const QString &type,
                 const QString &location, const QString &date,
                 const QString &status)
{
    m_name     = name;
    m_type     = type;
    m_location = location;
    m_date     = date;
    m_status   = status;
}

bool Machine::ajouter()
{
    QSqlQuery query(QSqlDatabase::database("myConnection"));
    query.prepare("INSERT INTO Machine (ID_MACHINE, FULL_NAME, TYPE, LOCATION, PURCHASE_DATE, STATUS)"
                  " VALUES (MACHINE_SEQ.NEXTVAL, ?, ?, ?, TO_DATE(?, 'YYYY-MM-DD'), ?)");
    query.addBindValue(m_name);
    query.addBindValue(m_type);
    query.addBindValue(m_location);
    query.addBindValue(m_date);
    query.addBindValue(m_status);
    return query.exec();
}

bool Machine::modifier(int id)
{
    QSqlQuery query(QSqlDatabase::database("myConnection"));
    query.prepare("UPDATE Machine SET FULL_NAME = ?, TYPE = ?, LOCATION = ?, "
                  "PURCHASE_DATE = TO_DATE(?, 'YYYY-MM-DD'), STATUS = ? WHERE ID_MACHINE = ?");
    query.addBindValue(m_name);
    query.addBindValue(m_type);
    query.addBindValue(m_location);
    query.addBindValue(m_date);
    query.addBindValue(m_status);
    query.addBindValue(id);
    return query.exec();
}

bool Machine::supprimer(int id)
{
    QSqlQuery query(QSqlDatabase::database("myConnection"));
    query.prepare("DELETE FROM Machine WHERE ID_MACHINE = ?");
    query.addBindValue(id);
    return query.exec();
}

QSqlQueryModel* Machine::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query(QSqlDatabase::database("myConnection"));
    query.exec("SELECT ID_MACHINE, FULL_NAME, TYPE, LOCATION, PURCHASE_DATE, STATUS FROM Machine ORDER BY ID_MACHINE ASC");
    model->setQuery(query);
    return model;
}

QSqlQueryModel* Machine::rechercher(const QString &filter, const QString &sortColumn)
{
    QString pattern  = "%" + filter + "%";
    QString upattern = pattern.toUpper();

    QString whereClause;
    if (!filter.trimmed().isEmpty()) {
        whereClause = "WHERE TO_CHAR(ID_MACHINE) LIKE ? OR UPPER(FULL_NAME) LIKE ? "
                      "OR UPPER(TYPE) LIKE ? OR UPPER(LOCATION) LIKE ? "
                      "OR TO_CHAR(PURCHASE_DATE, 'YYYY-MM-DD') LIKE ? OR UPPER(STATUS) LIKE ? ";
    }

    QString orderByClause = "ORDER BY ";
    if      (sortColumn.contains("Name",   Qt::CaseInsensitive)) orderByClause += "FULL_NAME ASC";
    else if (sortColumn.contains("Type",   Qt::CaseInsensitive)) orderByClause += "TYPE ASC";
    else if (sortColumn.contains("Status", Qt::CaseInsensitive)) orderByClause += "STATUS ASC";
    else if (sortColumn.contains("Date",   Qt::CaseInsensitive)) orderByClause += "PURCHASE_DATE DESC";
    else                                                          orderByClause += "ID_MACHINE ASC";

    QString queryStr = "SELECT ID_MACHINE, FULL_NAME, TYPE, LOCATION, PURCHASE_DATE, STATUS FROM Machine "
                       + whereClause + orderByClause;

    QSqlQuery query(QSqlDatabase::database("myConnection"));
    query.prepare(queryStr);

    if (!filter.trimmed().isEmpty()) {
        query.addBindValue(pattern);   // ID_MACHINE
        query.addBindValue(upattern);  // FULL_NAME
        query.addBindValue(upattern);  // TYPE
        query.addBindValue(upattern);  // LOCATION
        query.addBindValue(pattern);   // PURCHASE_DATE
        query.addBindValue(upattern);  // STATUS
    }

    query.exec();
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);
    return model;
}
