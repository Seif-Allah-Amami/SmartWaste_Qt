#include "mainwindow.h"
#include "connexion.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection connection;
    if (!connection.createconnect()) {
        QMessageBox::critical(nullptr, "Database", "Failed to connect to the database.");
        return 1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
