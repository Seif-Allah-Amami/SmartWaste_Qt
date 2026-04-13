#include "connection.h"

// Initialize static member
QString Connection::s_lastError = "";

bool Connection::createConnection()
{
    const QString connectionName = "qt_sql_default_connection";
    QStringList drivers = QSqlDatabase::drivers();
    qDebug() << "Available drivers:" << drivers;

    // Close any existing connection
    if (QSqlDatabase::contains(connectionName)) {
        QSqlDatabase existing = QSqlDatabase::database(connectionName, false);
        if (existing.isOpen()) {
            existing.close();
        }
        QSqlDatabase::removeDatabase(connectionName);
    }

    // Try QOCI (native Oracle driver)
    if (drivers.contains("QOCI")) {
        qDebug() << "Trying QOCI...";
        QSqlDatabase db = QSqlDatabase::addDatabase("QOCI", connectionName);
        db.setHostName("localhost");
        db.setPort(1521);
        db.setDatabaseName("xe");
        db.setUserName("houda");
        db.setPassword("root");
        if (db.open()) {
            qDebug() << "✓ QOCI connection successful!";
            return testConnection();
        }
        QSqlDatabase::removeDatabase(connectionName);
    }

    // Try QODBC
    if (drivers.contains("QODBC")) {
        qDebug() << "Trying QODBC...";
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", connectionName);
        db.setDatabaseName("Source_Projet2A");
        db.setUserName("houda");
        db.setPassword("root");
        if (db.open()) {
            qDebug() << "✓ QODBC connection successful!";
            return testConnection();
        }
        QSqlDatabase::removeDatabase(connectionName);
    }

    // Fallback to SQLite for demo mode
    qDebug() << "Starting in Demo Mode with SQLite...";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(":memory:");
    
    if (db.open()) {
        qDebug() << "✓ Demo Mode initialized";
        setupDemoDatabase();
        return true;
    }
    
    s_lastError = "Fatal: Cannot initialize any database!";
    return false;
}

bool Connection::testConnection()
{
    QSqlQuery query;
    if (query.exec("SELECT 1 FROM DUAL")) {
        qDebug() << "✓ Connection test successful!";
        s_lastError = "";
        return true;
    } else {
        s_lastError = query.lastError().text();
        return false;
    }
}

void Connection::setupDemoDatabase()
{
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS EMPLOYEE");
    query.exec("CREATE TABLE EMPLOYEE (EMPLOYEE_ID INTEGER PRIMARY KEY, "
              "FULL_NAME TEXT, EMAIL TEXT, POSITION TEXT, DEPARTMENT TEXT, "
              "HIRE_DATE DATE, SALARY REAL, ID_MACHINE INTEGER, ID_SUPPLIER INTEGER)");
    
    query.prepare("INSERT INTO EMPLOYEE VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(1001);
    query.addBindValue("John Doe");
    query.addBindValue("john@company.com");
    query.addBindValue("Manager");
    query.addBindValue("IT");
    query.addBindValue("2023-01-15");
    query.addBindValue(5000.0);
    query.addBindValue(1);
    query.addBindValue(1);
    query.exec();
    
    query.addBindValue(1002);
    query.addBindValue("Jane Smith");
    query.addBindValue("jane@company.com");
    query.addBindValue("Developer");
    query.addBindValue("IT");
    query.addBindValue("2023-06-20");
    query.addBindValue(4500.0);
    query.addBindValue(2);
    query.addBindValue(1);
    query.exec();
    
    qDebug() << "✓ Demo database initialized";
}

QString Connection::lastError()
{
    return s_lastError;
}
