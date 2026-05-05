#include "arduinosensor.h"

#include <QSerialPortInfo>
#include <QRegularExpression>
#include <QDebug>

// ──────────────────────────────────────────────────────────────────────────────
ArduinoSensor::ArduinoSensor(QObject *parent)
    : QObject(parent)
    , m_port(new QSerialPort(this))
    , m_timer(new QTimer(this))
{
    m_timer->setSingleShot(true);
    connect(m_port,  &QSerialPort::readyRead, this, &ArduinoSensor::onDataReady);
    connect(m_timer, &QTimer::timeout,        this, &ArduinoSensor::onReadTimeout);
}

ArduinoSensor::~ArduinoSensor()
{
    closePort();
}

// ──────────────────────────────────────────────────────────────────────────────
QStringList ArduinoSensor::availablePorts()
{
    QStringList list;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        list << info.portName();
    return list;
}

// ──────────────────────────────────────────────────────────────────────────────
bool ArduinoSensor::openPort(const QString &portName)
{
    if (m_port->isOpen())
        m_port->close();

    m_portName = portName;
    m_port->setPortName(portName);
    m_port->setBaudRate(QSerialPort::Baud9600);
    m_port->setDataBits(QSerialPort::Data8);
    m_port->setParity(QSerialPort::NoParity);
    m_port->setStopBits(QSerialPort::OneStop);
    m_port->setFlowControl(QSerialPort::NoFlowControl);

    const bool ok = m_port->open(QIODevice::ReadWrite);
    if (!ok)
        qWarning() << "ArduinoSensor: cannot open" << portName << m_port->errorString();

    if (ok) {
        m_port->setDataTerminalReady(true);
        m_port->clear(QSerialPort::AllDirections);
        m_buf.clear();
        m_lastRawLine.clear();
        m_lastParseError.clear();
    }

    emit connectionChanged(ok);
    return ok;
}

void ArduinoSensor::closePort()
{
    if (m_port && m_port->isOpen()) {
        m_port->close();
        emit connectionChanged(false);
    }
}

bool ArduinoSensor::isConnected() const
{
    return m_port && m_port->isOpen();
}

// ──────────────────────────────────────────────────────────────────────────────
void ArduinoSensor::requestReading(int timeoutMs)
{
    if (!isConnected()) {
        Reading r;
        r.isValid = false;

        emit readingReady(r);
        return;
    }
    // Flush any stale bytes so the next reading reflects the current object.
    m_port->clear(QSerialPort::Input);
    m_port->readAll();
    m_buf.clear();

    // Keep bytes that may already be waiting. Some Arduino sketches print only
    // when an object first enters range, so clearing input here can discard the
    // one valid reading the user is trying to capture.
    m_lastRawLine.clear();
    m_lastParseError.clear();
    m_waiting = true;
    m_timer->start(timeoutMs);

    m_buf += m_port->readAll();
    processBufferedLines();
}

// ──────────────────────────────────────────────────────────────────────────────
void ArduinoSensor::onDataReady()
{
    m_buf += m_port->readAll();
    processBufferedLines();
}

bool ArduinoSensor::processBufferedLines()
{
    // Process all complete lines; emit the first valid reading after a request.
    bool emitted = false;
    while (m_buf.contains('\n')) {
        const int idx = m_buf.indexOf('\n');
        const QByteArray lineBytes = m_buf.left(idx);
        m_buf.remove(0, idx + 1);

        const QString line = QString::fromUtf8(lineBytes).trimmed();
        if (line.isEmpty()) {
            continue;
        }

        m_lastRawLine = line;
        Reading r;
        if (parseLine(line, r)) {
            m_last = r;
            if (m_waiting) {
                m_waiting = false;
                m_timer->stop();
                emit readingReady(r);
                emitted = true;
                break;
            }
        }
    }

    return emitted;
}

void ArduinoSensor::onReadTimeout()
{
    if (m_waiting) {
        m_waiting = false;
        qWarning() << "ArduinoSensor: timed out waiting for sensor data";
        Reading r;
        r.isValid = false;
        emit readingReady(r);
    }
}

// ──────────────────────────────────────────────────────────────────────────────
// Expected format from Arduino sketch:
//   "Humidity: 72%    Distance: 9 cm     ==>WET Waste"
//   "Humidity: 3%     Distance: 11 cm    ==>Dry Waste"
// Lines like "BIN OPEN" or header banners are ignored.
bool ArduinoSensor::parseLine(const QString &line, Reading &out)
{
    static const QRegularExpression reHum(
        R"((Humidity|Moisture|Hum)\s*[:=]?\s*(\d{1,3})\s*%?)",
        QRegularExpression::CaseInsensitiveOption);
    static const QRegularExpression reDist(
        R"((Distance|Dist)\s*[:=]?\s*(\d{1,4})\s*(cm)?)",
        QRegularExpression::CaseInsensitiveOption);
    static const QRegularExpression reWet(
        R"((==>\s*WET\s*Waste|\bWET\b|\bOrganic\b))",
        QRegularExpression::CaseInsensitiveOption);
    static const QRegularExpression reDry(
        R"((==>\s*DRY\s*Waste|\bDRY\b|\bPlastic\b|\bRecyclable\b))",
        QRegularExpression::CaseInsensitiveOption);
    static const QRegularExpression reAnyNumber(
        R"((\d+))",
        QRegularExpression::CaseInsensitiveOption);

    QRegularExpressionMatch mHum  = reHum.match(line);
    QRegularExpressionMatch mDist = reDist.match(line);

    int humidity = -1;
    int distance = -1;

    if (mHum.hasMatch()) {
        humidity = mHum.captured(2).toInt();
    }
    if (mDist.hasMatch()) {
        distance = mDist.captured(2).toInt();
    }

    if (humidity < 0 || distance < 0) {
        // Fallback parser: accept first two numeric values in the line.
        QRegularExpressionMatchIterator it = reAnyNumber.globalMatch(line);
        QList<int> numbers;
        while (it.hasNext()) {
            const QRegularExpressionMatch m = it.next();
            bool ok = false;
            const int value = m.captured(1).toInt(&ok);
            if (ok) {
                numbers.append(value);
            }
        }
        if (numbers.size() >= 2) {
            humidity = numbers.at(0);
            distance = numbers.at(1);
        }
    }

    if (humidity < 0 || distance < 0) {
        m_lastParseError = "Could not extract both humidity and distance from serial text.";
        return false;
    }

    if (humidity > 100) {
        m_lastParseError = "Humidity out of expected range (0-100).";
        return false;
    }

    if (distance > 500) {
        m_lastParseError = "Distance out of expected range (0-500 cm).";
        return false;
    }

    out.humidity = humidity;
    out.distance = distance;

    const bool hasWet = reWet.match(line).hasMatch();
    const bool hasDry = reDry.match(line).hasMatch();
    const int wetThreshold = 10;

    if (hasWet && !hasDry) {
        out.isWet = true;
    } else if (hasDry && !hasWet) {
        out.isWet = false;
    } else {
        // Fallback to humidity threshold when marker words are absent or mixed.
        const bool invertHumidity = true;
        out.isWet = invertHumidity ? (humidity <= wetThreshold) : (humidity > wetThreshold);
    }

    out.isValid  = true;
    m_lastParseError.clear();
    return true;
}
