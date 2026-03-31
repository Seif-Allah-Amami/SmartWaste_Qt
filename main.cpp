#include "mainwindow.h"
<<<<<<< HEAD
#include "connection.h"
=======

>>>>>>> d40e1db5339865986d79f6e20a2a9d6620de1d3a
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD

    Connection c;
    if(!c.createconnect())
        return 1;

=======
>>>>>>> d40e1db5339865986d79f6e20a2a9d6620de1d3a
    MainWindow w;
    w.show();
    return a.exec();
}
