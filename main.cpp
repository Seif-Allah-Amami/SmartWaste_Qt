#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // database connection
    if(!Connection::createConnection())
    {
        qDebug() << "Connection failed:" << Connection::lastError();
    }
    else
    {
        qDebug() << "Database connected.";
    }

    MainWindow w;
    w.show();

    return a.exec();
}
