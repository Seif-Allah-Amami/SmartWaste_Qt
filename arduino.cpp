#include "arduino.h"
#include <QDate>
Arduino::Arduino(QObject *parent) : QObject(parent) {
    serial = new QSerialPort(this);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    connect(serial, &QSerialPort::readyRead, this, &Arduino::onDataReceived);
}

void Arduino::connectToArduino(const QString &portName) {
    serial->setPortName(portName);
    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Connected to Arduino on" << portName;
    } else {
        qDebug() << "Failed to connect:" << serial->errorString();
    }
}

void Arduino::disconnect() {
    if (serial->isOpen()) {
        serial->close();
    }
}


void Arduino::processRequest(const QString &plateNum) {
    QSqlQuery query;
    query.prepare("SELECT v.STATUS FROM RAYEN.VEHICLE v "
                  "WHERE v.PLATE_NUM = :plate");
    query.bindValue(":plate", plateNum);
    if (query.exec() && query.next()) {
        QString status = query.value(0).toString();
        if (status == "Active") {
            sendResponse("GRANTED");
        } else {
            sendResponse("DENIED|Vehicle not active");
        }
    } else {
        sendResponse("DENIED|Vehicle not found");
    }
}

void Arduino::sendResponse(const QString &response) {
    if (serial->isOpen()) {
        serial->write((response + "\n").toUtf8());
        qDebug() << "Sent:" << response;
    }
}
void Arduino::onDataReceived() {
    while (serial->canReadLine()) {
        QString line = serial->readLine().trimmed();
        line.remove(QChar('\0'));
        if (line.isEmpty()) continue;
        qDebug() << "Received:" << line;
        if (line.startsWith("REQ|")) {
            QString plateNum = line.mid(4);
            processRequest(plateNum);
        } else if (line.startsWith("RFID|")) {
            QString uid = line.mid(5);
            processRFID(uid);
        }
    }
}
void Arduino::processRFID(const QString &uid) {
    QSqlQuery query;
    query.prepare("SELECT s.RATING, s.CONTRACT_END_DATE FROM RAYEN.SUPPLIER s "
                  "WHERE s.RFID_UID = :uid");
    query.bindValue(":uid", uid);

    QString result;
    if (query.exec() && query.next()) {
        double rating = query.value(0).toDouble();
        QDate contractEnd = query.value(1).toDate();
        QDate today = QDate::currentDate();

        if (rating < 2.0) {
            result = "DENIED|Supplier blacklisted";
        } else if (contractEnd.isValid() && contractEnd < today) {
            result = "DENIED|Contract expired";
        } else {
            result = "GRANTED";
        }
    } else {
        result = "DENIED|Supplier not found";
    }

    sendResponse(result);
    emit accessAttempt(uid, result);
}
