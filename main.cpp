#include "mainwindow.h"
<<<<<<< HEAD
#include "connection.h"
=======

>>>>>>> origin/supplier
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD

    Connection c;
    if(!c.createconnect())
        return 1;

=======
>>>>>>> origin/supplier
    MainWindow w;
    w.show();
    return a.exec();
}
