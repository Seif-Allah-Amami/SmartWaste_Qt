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
        // ODBC connection
        db = QSqlDatabase::addDatabase("QODBC");

        db.setDatabaseName("Driver={Oracle in XE};Dbq=localhost:1521/XE;");
        db.setUserName("Rayen");      // change if needed
        db.setPassword("root");        // change password

        if(db.open())
        {
            qDebug() << "Oracle connected";
            return true;
        }
        else
        {
            qDebug() << "Error:" << db.lastError().text();
            return false;
        }
    }
};

#endif
