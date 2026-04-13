<<<<<<< HEAD
#include "connexion.h"
#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
=======
#include "mainwindow.h"

#include <QApplication>
>>>>>>> origin/vehicle

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD

    Connection connection;
    if (!connection.createconnect()) {
        QMessageBox::warning(nullptr,
                             "Database",
                             "Failed to connect to the database. Verify your ODBC source and credentials.");
    }

=======
>>>>>>> origin/vehicle
    MainWindow w;
    w.show();
    return a.exec();
}
