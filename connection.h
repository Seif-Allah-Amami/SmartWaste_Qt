#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class Connection
{
public:
    QSqlDatabase db;

    bool createconnect()
    {
        if (QSqlDatabase::contains("myConnection")) {
            db = QSqlDatabase::database("myConnection");
            if (db.isOpen()) {
                return true;
            }
            // Try to reopen if closed
            if (db.open()) {
                return true;
            }
        }

        db = QSqlDatabase::addDatabase("QODBC", "myConnection");
        db.setDatabaseName("source_project2A");
        db.setUserName("eya");
        db.setPassword("root");

        if(db.open()) {
            qDebug() << "Oracle connected";
            return true;
        } else {
            qDebug() << "Connection Error:" << db.lastError().text();
            return false;
        }
    }
};

#endif

