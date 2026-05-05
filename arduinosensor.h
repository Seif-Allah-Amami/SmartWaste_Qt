#ifndef ARDUINOSENSOR_H
#define ARDUINOSENSOR_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QString>

/**
 * ArduinoSensor – reads soil-moisture + ultrasonic distance
 * from an Arduino sketch that prints lines like:
 *   "Humidity: 72%    Distance: 9 cm     ==>WET Waste "
 *   "Humidity: 3%     Distance: 11 cm    ==>Dry Waste "
 *
 * Usage:
 *   ArduinoSensor *sensor = new ArduinoSensor(this);
 *   connect(sensor, &ArduinoSensor::readingReady,
 *           this, &MyWindow::onSensorReading);
 *   sensor->openPort("COM3");          // Windows
 *   sensor->openPort("/dev/ttyUSB0"); // Linux
 */
class ArduinoSensor : public QObject
{
    Q_OBJECT

public:
    struct Reading {
        int     humidity   = -1;   // percent  (-1 = not yet read)
        int     distance   = -1;   // cm       (-1 = not yet read)
        bool    isWet      = false;
        bool    isValid    = false;
    };

    explicit ArduinoSensor(QObject *parent = nullptr);
    ~ArduinoSensor();

    /** Open the serial port (9600 8N1). Returns true on success. */
    bool openPort(const QString &portName);
    void closePort();
    bool isConnected() const;
    QString currentPort() const { return m_portName; }

    /** Static helper: list all available serial port names. */
    static QStringList availablePorts();

    /**
     * Request a single reading.  The sensor only fires when the Arduino
     * detects an object (distance < threshold) so this method waits up to
     * timeoutMs for a valid line, then emits readingReady().
     * If the port is not open it emits readingReady with isValid=false.
     */
    void requestReading(int timeoutMs = 8000);

    /** Last successfully parsed reading (convenience getter). */
    Reading lastReading() const { return m_last; }
    QString lastRawLine() const { return m_lastRawLine; }
    QString lastParseError() const { return m_lastParseError; }

signals:
    /** Emitted once per requestReading() call when data arrives or times out. */
    void readingReady(ArduinoSensor::Reading reading);

    /** Emitted whenever the connection state changes. */
    void connectionChanged(bool connected);

private slots:
    void onDataReady();
    void onReadTimeout();

private:
    bool parseLine(const QString &line, Reading &out);
    bool processBufferedLines();


    QSerialPort *m_port     = nullptr;
    QTimer      *m_timer    = nullptr;
    QString      m_portName;
    QByteArray   m_buf;
    Reading      m_last;
    QString      m_lastRawLine;
    QString      m_lastParseError;
    bool         m_waiting  = false;
};

#endif // ARDUINOSENSOR_H
