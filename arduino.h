#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtSql/QSqlQuery>
#include <QDebug>

class Arduino : public QObject {
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);
    void connectToArduino(const QString &portName);
    void disconnect();

signals:
    void accessAttempt(const QString &plate, const QString &result);

private slots:
    void onDataReceived();

private:
    QSerialPort *serial;
    void processRequest(const QString &plateNum);
    void processRFID(const QString &uid);
    void sendResponse(const QString &response);
};

#endif
