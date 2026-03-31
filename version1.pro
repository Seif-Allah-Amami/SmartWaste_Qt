<<<<<<< HEAD
QT       += core gui sql
QT += core gui sql charts
=======
QT       += core gui

>>>>>>> d40e1db5339865986d79f6e20a2a9d6620de1d3a
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< HEAD
    alertsdialog.cpp \
    machine.cpp \
    machinehistory.cpp \
    machinestats.cpp \
=======
>>>>>>> d40e1db5339865986d79f6e20a2a9d6620de1d3a
    main.cpp \
    mainwindow.cpp

HEADERS += \
<<<<<<< HEAD
    alertsdialog.h \
    connection.h \
    machine.h \
    machinehistory.h \
    machinestats.h \
=======
>>>>>>> d40e1db5339865986d79f6e20a2a9d6620de1d3a
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
