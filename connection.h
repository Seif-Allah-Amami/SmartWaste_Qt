#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStringList>

class Connection
{
public:
    QSqlDatabase db;

    bool createconnect()
    {
        // Remove old connection if exists
        if (QSqlDatabase::contains("qt_sql_default_connection")) {
            QSqlDatabase::removeDatabase("qt_sql_default_connection");
        }

        // ODBC connection to Oracle
        db = QSqlDatabase::addDatabase("QODBC");

        db.setDatabaseName("Driver={Oracle in XE};DBQ=XE;");
<<<<<<< HEAD
        db.setUserName("Manar");
        db.setPassword("root");
=======
        db.setUserName("saaida");
        db.setPassword("0000");
>>>>>>> 5be580a (waste X Arduino)

        if(db.open())
        {
            qDebug() << "Oracle connected successfully!";
            return true;
        }
        else
        {
            qDebug() << "Connection Error:" << db.lastError().text();
            qDebug() << "Driver Error:" << db.lastError().driverText();
            qDebug() << "Database Error:" << db.lastError().databaseText();
            return false;
        }
    }

    QSqlDatabase getDatabase() const
    {
        return db;
    }

    QStringList allEntities(const QString &owner = QString(), bool includeViews = true) const
    {
        QStringList entities;
        if (!db.isOpen()) {
            qDebug() << "Database is not open.";
            return entities;
        }

        QSqlQuery query(db);
        const bool filterByOwner = !owner.trimmed().isEmpty();

        QString tableSql = "SELECT owner || '.' || table_name AS entity_name FROM all_tables";
        QString viewSql = "SELECT owner || '.' || view_name AS entity_name FROM all_views";

        if (filterByOwner) {
            tableSql += " WHERE UPPER(owner) = UPPER(:owner)";
            viewSql += " WHERE UPPER(owner) = UPPER(:owner)";
        }

        QString sql = tableSql;
        if (includeViews) {
            sql += " UNION " + viewSql;
        }
        sql += " ORDER BY entity_name";

        query.prepare(sql);
        if (filterByOwner) {
            query.bindValue(":owner", owner);
        }

        if (!query.exec()) {
            qDebug() << "Error fetching entities:" << query.lastError().text();
            return entities;
        }

        while (query.next()) {
            entities.append(query.value("ENTITY_NAME").toString());
        }

        return entities;
    }

    bool entityExists(const QString &entityName, const QString &owner = QString(), bool includeViews = true) const
    {
        if (!db.isOpen()) {
            return false;
        }

        QString schemaOwner = owner.trimmed();
        QString objectName = entityName.trimmed();

        if (objectName.contains('.')) {
            const QStringList parts = objectName.split('.', Qt::SkipEmptyParts);
            if (parts.size() == 2) {
                schemaOwner = parts.at(0);
                objectName = parts.at(1);
            }
        }

        const bool filterByOwner = !schemaOwner.isEmpty();

        QString tableSql = "SELECT COUNT(*) AS cnt FROM all_tables WHERE UPPER(table_name) = UPPER(:name)";
        QString viewSql = "SELECT COUNT(*) AS cnt FROM all_views WHERE UPPER(view_name) = UPPER(:name)";

        if (filterByOwner) {
            tableSql += " AND UPPER(owner) = UPPER(:owner)";
            viewSql += " AND UPPER(owner) = UPPER(:owner)";
        }

        QString sql = "SELECT SUM(cnt) FROM (" + tableSql;
        if (includeViews) {
            sql += " UNION ALL " + viewSql;
        }
        sql += ")";

        QSqlQuery query(db);
        query.prepare(sql);
        query.bindValue(":name", objectName);
        if (filterByOwner) {
            query.bindValue(":owner", schemaOwner);
        }

        if (!query.exec() || !query.next()) {
            qDebug() << "Error checking entity existence:" << query.lastError().text();
            return false;
        }

        return query.value(0).toInt() > 0;
    }
};

#endif // CONNECTION_H
