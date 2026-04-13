<<<<<<< HEAD
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "connection.h"
=======
#include "mainwindow.h"

#include <QApplication>
>>>>>>> origin/employee

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD

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

=======
    MainWindow w;
    w.show();
>>>>>>> origin/employee
    return a.exec();
}
