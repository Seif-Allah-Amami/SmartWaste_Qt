<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> origin/employee
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "connection.h"
<<<<<<< HEAD
=======
=======
#include "mainwindow.h"

#include <QApplication>
>>>>>>> origin/employee
>>>>>>> origin/employee

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> origin/employee

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

<<<<<<< HEAD
=======
=======
    MainWindow w;
    w.show();
>>>>>>> origin/employee
>>>>>>> origin/employee
    return a.exec();
}
