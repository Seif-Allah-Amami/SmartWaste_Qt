<<<<<<< HEAD
QT       += core gui sql charts network
=======
QT       += core gui sql charts network serialport
>>>>>>> 5be580a (waste X Arduino)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

<<<<<<< HEAD
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
=======
SOURCES += \
    arduinosensor.cpp \
>>>>>>> 5be580a (waste X Arduino)
    main.cpp \
    mainwindow.cpp \
    waste.cpp

HEADERS += \
<<<<<<< HEAD
=======
    arduinosensor.h \
>>>>>>> 5be580a (waste X Arduino)
    connection.h \
    mainwindow.h \
    waste.h

FORMS += \
    mainwindow.ui

<<<<<<< HEAD
# Default rules for deployment.
=======
>>>>>>> 5be580a (waste X Arduino)
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
