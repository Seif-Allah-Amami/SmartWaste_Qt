#include "connexion.h"
#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection connection;
    if (!connection.createconnect()) {
        QMessageBox::warning(nullptr,
                             "Database",
                             "Failed to connect to the database. Verify your ODBC source and credentials.");
    }

    MainWindow w;
    w.show();
    return a.exec();
}
