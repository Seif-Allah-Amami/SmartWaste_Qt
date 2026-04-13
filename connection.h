#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QString>

class Connection
{
public:
    inline static QString last_error = "";

    static bool createConnection()
    {
        if(QSqlDatabase::contains("qt_sql_default_connection"))
            QSqlDatabase::removeDatabase("qt_sql_default_connection");

        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        db.setDatabaseName("Driver={Oracle in XE};Dbq=localhost:1521/XE;");
        db.setUserName("houda");
        db.setPassword("root");

        if(db.open())
        {
            qDebug() << "Oracle connected";
            last_error = "";
            return true;
        }
        else
        {
            last_error = db.lastError().text();
            qDebug() << last_error;
            return false;
        }
    }

    static QString lastError()
    {
        return last_error;
    }
};

#endif
