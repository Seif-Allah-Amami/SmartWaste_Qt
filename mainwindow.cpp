#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QComboBox>
#include <QFileDialog>
#include <QDateTime>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QTableWidget>
#include <QMap>
#include <QHBoxLayout>
#include <QFrame>
#include <QGuiApplication>
#include <QScreen>
#include <QFile>
#include <QDir>
#include <QSet>
#include <QHash>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QEventLoop>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMouseEvent>
#include <QWheelEvent>

#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QValueAxis>

#include <algorithm>

<<<<<<< HEAD
=======
#include "arduinosensor.h"

>>>>>>> 5be580a (waste X Arduino)
class OSMTileMapWidget : public QWidget
{
public:
    explicit OSMTileMapWidget(QWidget *parent = nullptr)
        : QWidget(parent)
        , m_network(new QNetworkAccessManager(this))
    {
        setMouseTracking(true);
        setMinimumSize(900, 600);

        connect(m_network, &QNetworkAccessManager::finished, this, [this](QNetworkReply *reply) {
            const QString key = reply->property("tileKey").toString();
            m_pending.remove(key);

            if (reply->error() == QNetworkReply::NoError) {
                QPixmap pix;
                pix.loadFromData(reply->readAll());
                if (!pix.isNull()) {
                    m_tileCache.insert(key, pix);
                }
            }

            reply->deleteLater();
            update();
        });
    }

    void setMarker(double lat, double lon, const QString &name)
    {
        m_markerLat = lat;
        m_markerLon = lon;
        m_markerName = name;
        m_centerLat = lat;
        m_centerLon = lon;
        m_initialLat = lat;
        m_initialLon = lon;
        m_zoom = 13;
        update();
    }

    void resetView()
    {
        m_centerLat = m_initialLat;
        m_centerLon = m_initialLon;
        m_zoom = 13;
        update();
    }

    void zoomIn()
    {
        m_zoom = qMin(19, m_zoom + 1);
        update();
    }

    void zoomOut()
    {
        m_zoom = qMax(3, m_zoom - 1);
        update();
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.fillRect(rect(), QColor("#031912"));

        const int tileSize = 256;
        const int n = 1 << m_zoom;

        const QPointF centerWorld = geoToWorld(m_centerLat, m_centerLon, m_zoom);
        const double startX = centerWorld.x() - width() / 2.0;
        const double startY = centerWorld.y() - height() / 2.0;

        const int minTileX = static_cast<int>(std::floor(startX / tileSize));
        const int maxTileX = static_cast<int>(std::floor((startX + width()) / tileSize));
        const int minTileY = static_cast<int>(std::floor(startY / tileSize));
        const int maxTileY = static_cast<int>(std::floor((startY + height()) / tileSize));

        for (int tileY = minTileY; tileY <= maxTileY; ++tileY) {
            if (tileY < 0 || tileY >= n) {
                continue;
            }

            for (int tileX = minTileX; tileX <= maxTileX; ++tileX) {
                const int wrappedX = ((tileX % n) + n) % n;
                const QString key = QString("%1/%2/%3").arg(m_zoom).arg(wrappedX).arg(tileY);

                const int drawX = static_cast<int>(tileX * tileSize - startX);
                const int drawY = static_cast<int>(tileY * tileSize - startY);
                const QRect tileRect(drawX, drawY, tileSize, tileSize);

                if (m_tileCache.contains(key)) {
                    painter.drawPixmap(tileRect, m_tileCache.value(key));
                } else {
                    painter.fillRect(tileRect, QColor("#0b2a20"));
                    painter.setPen(QColor("#1f5845"));
                    painter.drawRect(tileRect);
                    requestTile(m_zoom, wrappedX, tileY, key);
                }
            }
        }

        const QPointF markerWorld = geoToWorld(m_markerLat, m_markerLon, m_zoom);
        const int markerX = static_cast<int>(markerWorld.x() - startX);
        const int markerY = static_cast<int>(markerWorld.y() - startY);

        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setBrush(QColor("#00d084"));
        painter.setPen(QPen(QColor("#043b2b"), 2));
        painter.drawEllipse(QPoint(markerX, markerY), 9, 9);

        painter.setPen(QColor("#d8fff1"));
        painter.drawText(markerX + 12, markerY - 12, m_markerName);
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            m_dragging = true;
            m_lastPos = event->pos();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (!m_dragging) {
            return;
        }

        const QPoint delta = event->pos() - m_lastPos;
        m_lastPos = event->pos();

        QPointF world = geoToWorld(m_centerLat, m_centerLon, m_zoom);
        world.rx() -= delta.x();
        world.ry() -= delta.y();

        const QPair<double, double> geo = worldToGeo(world.x(), world.y(), m_zoom);
        m_centerLat = qBound(-85.0511, geo.first, 85.0511);
        m_centerLon = geo.second;
        update();
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            m_dragging = false;
        }
    }

    void wheelEvent(QWheelEvent *event) override
    {
        const int delta = event->angleDelta().y();
        if (delta > 0) {
            zoomIn();
        } else if (delta < 0) {
            zoomOut();
        }
        event->accept();
    }

private:
    static QPointF geoToWorld(double lat, double lon, int zoom)
    {
        const double tileSize = 256.0;
        const double n = static_cast<double>(1 << zoom);
        const double x = (lon + 180.0) / 360.0 * n * tileSize;
        const double latRad = lat * M_PI / 180.0;
        const double y = (1.0 - std::log(std::tan(latRad) + 1.0 / std::cos(latRad)) / M_PI) / 2.0 * n * tileSize;
        return QPointF(x, y);
    }

    static QPair<double, double> worldToGeo(double worldX, double worldY, int zoom)
    {
        const double tileSize = 256.0;
        const double n = static_cast<double>(1 << zoom);
        const double worldSize = n * tileSize;

        while (worldX < 0.0) {
            worldX += worldSize;
        }
        while (worldX >= worldSize) {
            worldX -= worldSize;
        }

        worldY = qBound(0.0, worldY, worldSize);

        const double lon = worldX / worldSize * 360.0 - 180.0;
        const double mercN = M_PI - (2.0 * M_PI * worldY) / worldSize;
        const double lat = 180.0 / M_PI * std::atan(0.5 * (std::exp(mercN) - std::exp(-mercN)));
        return qMakePair(lat, lon);
    }

    void requestTile(int z, int x, int y, const QString &key)
    {
        if (m_pending.contains(key)) {
            return;
        }

        m_pending.insert(key);
        QUrl url(QString("https://tile.openstreetmap.org/%1/%2/%3.png").arg(z).arg(x).arg(y));
        QNetworkRequest request(url);
        request.setRawHeader("User-Agent", "ManarWasteApp/1.0 (educational project)");

        QNetworkReply *reply = m_network->get(request);
        reply->setProperty("tileKey", key);
    }

    QNetworkAccessManager *m_network;
    QHash<QString, QPixmap> m_tileCache;
    QSet<QString> m_pending;

    double m_markerLat = 36.8065;
    double m_markerLon = 10.1815;
    QString m_markerName = "Location";

    double m_centerLat = 36.8065;
    double m_centerLon = 10.1815;
    double m_initialLat = 36.8065;
    double m_initialLon = 10.1815;
    int m_zoom = 13;

    bool m_dragging = false;
    QPoint m_lastPos;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_nextPickupTicket(1000)
    , m_databaseReady(false)
    , m_searchHintLabel(nullptr)
{
    ui->setupUi(this);

<<<<<<< HEAD
    // Start on login page
    ui->stackedwidget->setCurrentIndex(0);

    // Connect all navigation buttons
    setupConnections();
=======
    // Start directly on Waste Management (module selection disabled)
    ui->stackedwidget->setCurrentWidget(ui->wastemanagement);

    // Connect all navigation buttons
    setupConnections();
    setupArduinoSensor(); // Arduino sensor init
>>>>>>> 5be580a (waste X Arduino)

    setupWasteTable();
    m_databaseReady = initializeDatabase() && ensureWasteTable() && ensurePickupScheduleTable();
    if (m_databaseReady) {
        loadScheduledPickupsFromDb();
    }
    onViewWasteClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    // Login Page Navigation
    connect(ui->btnLogin, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->btnForgotPassword, &QPushButton::clicked, this, &MainWindow::showRecoveryPage);

    // Recovery Page Navigation
    connect(ui->btnRecoveryContinue, &QPushButton::clicked, this, &MainWindow::showVerificationPage);
    connect(ui->btnRecoveryCancel, &QPushButton::clicked, this, &MainWindow::showLoginPage);

    // Verification Page Navigation
    connect(ui->btnVerifyCheck, &QPushButton::clicked, this, &MainWindow::onVerifyClicked);
    connect(ui->btnVerifyCancel, &QPushButton::clicked, this, &MainWindow::showLoginPage);

    // Main Menu Navigation
<<<<<<< HEAD
    connect(ui->btnMenuEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnMenuCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
    connect(ui->btnMenuWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
<<<<<<< HEAD
    connect(ui->btnMenuVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnMenuMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
    connect(ui->btnMenuSupplier, &QPushButton::clicked, this, &MainWindow::showSupplierPage);
=======
<<<<<<< HEAD
    connect(ui->btnMenuVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnMenuMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
=======
<<<<<<< HEAD
    connect(ui->btnMenuVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544

    // Employee Page Sidebar Navigation
    connect(ui->btnEmpDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnEmpLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmpEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnEmpCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
<<<<<<< HEAD
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);

=======
<<<<<<< HEAD
    connect(ui->btnEmpVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
    connect(ui->btnEmpMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
    connect(ui->btnEmpSupplier, &QPushButton::clicked, this, &MainWindow::showSupplierPage);
=======
<<<<<<< HEAD
    connect(ui->btnEmpVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
    connect(ui->btnEmpMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
=======
<<<<<<< HEAD
    connect(ui->btnEmpVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
>>>>>>> origin/waste
    // Waste Management Sidebar Navigation
    connect(ui->btnDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
<<<<<<< HEAD
=======
    connect(ui->btnMenuCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
    connect(ui->btnMenuWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);

    // Employee Page Sidebar Navigation
    ui->searchBox->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9 \\\\-]{0,10}$"), this));
    connect(ui->btnEmpLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmpCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);

    // Waste Management Sidebar Navigation
    connect(ui->btnDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
>>>>>>> 5be580a (waste X Arduino)
    connect(ui->btnWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
    connect(ui->btnViewWaste, &QPushButton::clicked, this, &MainWindow::onViewWasteClicked);
    connect(ui->btnAddWaste, &QPushButton::clicked, this, &MainWindow::onAddWasteClicked);
    connect(ui->btnWasteStats, &QPushButton::clicked, this, &MainWindow::onWasteStatsClicked);
<<<<<<< HEAD
=======

    // Sensor Details button — created in code to avoid ui_mainwindow.h regeneration issues
    QPushButton *btnSensorDetails = new QPushButton("Sensor Details", this);
    btnSensorDetails->setStyleSheet(
        "QPushButton {"
        "  background-color: transparent;"
        "  border: 1px solid #6bffb8;"
        "  border-radius: 10px;"
        "  padding: 10px 20px;"
        "  color: #6bffb8;"
        "  font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "  background-color: rgba(107, 255, 184, 0.1);"
        "}");
    ui->topActionsLayout->insertWidget(3, btnSensorDetails);
    connect(btnSensorDetails, &QPushButton::clicked, this, &MainWindow::onSensorDetailsClicked);
>>>>>>> 5be580a (waste X Arduino)
    connect(ui->btnEditWaste, &QPushButton::clicked, this, &MainWindow::onEditWasteClicked);
    connect(ui->btnDeleteWaste, &QPushButton::clicked, this, &MainWindow::onDeleteWasteClicked);
    connect(ui->btnExportPDF, &QPushButton::clicked, this, &MainWindow::onExportWastePdfClicked);
    connect(ui->btnViewMaps, &QPushButton::clicked, this, &MainWindow::onViewOnMapClicked);
    connect(ui->btnRate, &QPushButton::clicked, this, &MainWindow::onSmartPickupSchedulerClicked);
    connect(ui->btnClearSelection, &QPushButton::clicked, this, &MainWindow::onClearWasteClicked);
    connect(ui->btnClearSelection, &QPushButton::clicked, this, &MainWindow::on_btnClearSelection_clicked);
    connect(ui->btnEmpClear, &QPushButton::clicked, this, &MainWindow::on_btnEmpClear_clicked);
    connect(ui->searchBox, &QLineEdit::textChanged, this, &MainWindow::onWasteSearchChanged);
    connect(ui->sortComboBox,
            qOverload<int>(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::onWasteSortChanged);
<<<<<<< HEAD
=======
<<<<<<< HEAD
    connect(ui->btnVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
    connect(ui->btnSupplier, &QPushButton::clicked, this, &MainWindow::showSupplierPage);
=======
<<<<<<< HEAD
    connect(ui->btnVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnMachines, &QPushButton::clicked, this, &MainWindow::showMachinePage);
=======
<<<<<<< HEAD
    connect(ui->btnVehicle, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
    // Waste Vehicle Sidebar Navigation
    connect(ui->btnDashboard_2, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout_2, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmployee_2, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnWaste_2, &QPushButton::clicked, this, &MainWindow::showWastePage);
<<<<<<< HEAD
    connect(ui->btnMachines_2, &QPushButton::clicked, this, &MainWindow::showMachinePage);
    connect(ui->btnSupplier_2, &QPushButton::clicked, this, &MainWindow::showSupplierPage);
=======
<<<<<<< HEAD
    connect(ui->btnMachines_2, &QPushButton::clicked, this, &MainWindow::showMachinePage);
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
    // Waste Machine Sidebar Navigation
    connect(ui->btnDashboard_3, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout_3, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnVehicle_3, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnEmployee_3, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnWaste_3, &QPushButton::clicked, this, &MainWindow::showWastePage);
<<<<<<< HEAD
    connect(ui->btnSuppliers, &QPushButton::clicked, this, &MainWindow::showSupplierPage);
    // Waste Supplier Sidebar Navigation
    connect(ui->btnDashboard_4, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout_3, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnInventory, &QPushButton::clicked, this, &MainWindow::showVehiclePage);
    connect(ui->btnReports, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnOrders, &QPushButton::clicked, this, &MainWindow::showWastePage);
    connect(ui->btnMachines_4, &QPushButton::clicked, this, &MainWindow::showMachinePage);
=======
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544


    // ✅ ADD THIS LINE ONLY

<<<<<<< HEAD
=======
=======
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> origin/waste
=======
>>>>>>> 5be580a (waste X Arduino)

    ui->sortComboBox->setItemData(0, "date_desc");
    ui->sortComboBox->setItemData(1, "type_asc");
    ui->sortComboBox->setItemData(2, "location_asc");
    ui->sortComboBox->setItemData(3, "status_asc");

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 5be580a (waste X Arduino)
    if (ui->sortComboBox->findText("Sort: ID") < 0) {
        ui->sortComboBox->addItem("Sort: ID");
    }
    const int sortIdIndex = ui->sortComboBox->findText("Sort: ID");
    if (sortIdIndex >= 0) {
        ui->sortComboBox->setItemData(sortIdIndex, "id_asc");
    }

    ui->searchBox->setMaxLength(10);
<<<<<<< HEAD
    ui->searchBox->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9-]{0,10}$"), this));
=======
    ui->searchBox->setValidator(new QRegularExpressionValidator(QRegularExpression(R"(^[A-Za-z0-9 \-]{0,10}$)"), this));
>>>>>>> 5be580a (waste X Arduino)

    connect(ui->searchBox, &QLineEdit::inputRejected, this, [this]() {
        if (!m_searchHintLabel) {
            return;
        }

<<<<<<< HEAD
        QString sortMode = ui->sortComboBox->currentData().toString();
        if (sortMode.isEmpty()) {
            const QString sortText = ui->sortComboBox->currentText().toLower();
            if (sortText.contains("type")) {
                sortMode = "type_asc";
            } else if (sortText.contains("id")) {
                sortMode = "id_asc";
            } else if (sortText.contains("location")) {
                sortMode = "location_asc";
            } else if (sortText.contains("status")) {
                sortMode = "status_asc";
            } else {
                sortMode = "date_desc";
            }
        }

        m_searchHintLabel->setVisible(true);
        if (ui->searchBox->text().length() >= ui->searchBox->maxLength()) {
            m_searchHintLabel->setText("Maximum 10 characters reached.");
        } else if (sortMode == "id_asc") {
            m_searchHintLabel->setText("Invalid character. ID search accepts numbers only.");
        } else if (sortMode == "date_desc") {
            m_searchHintLabel->setText("Invalid character. Date search accepts digits and '-'.");
        } else {
            m_searchHintLabel->setText("Invalid character. This search accepts letters and spaces only.");
=======
        m_searchHintLabel->setVisible(true);
        if (ui->searchBox->text().length() >= ui->searchBox->maxLength()) {
            m_searchHintLabel->setText("Maximum 10 characters reached.");
        } else {
            m_searchHintLabel->setText("Invalid character. Use letters, numbers, spaces, '-' only.");
>>>>>>> 5be580a (waste X Arduino)
        }
        m_searchHintLabel->setStyleSheet("QLabel { color: #ff6666; font-size: 11px; }");
    });

    m_searchHintLabel = new QLabel(ui->searchFilterWidget);
    m_searchHintLabel->setText("Search hint: letters/numbers only, max 10 chars.");
    m_searchHintLabel->setStyleSheet("QLabel { color: #8feecf; font-size: 11px; }");
    m_searchHintLabel->setVisible(false);
    ui->searchFilterLayout->insertWidget(2, m_searchHintLabel);
<<<<<<< HEAD
=======
    // ✅ ADD THIS LINE ONLY
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
>>>>>>> origin/waste
=======
>>>>>>> 5be580a (waste X Arduino)
}

bool MainWindow::initializeDatabase()
{
    return m_connection.createconnect();
}

bool MainWindow::ensureWasteTable()
{
    QSqlDatabase db = m_connection.getDatabase();
    if (!db.isOpen()) {
        qDebug() << "Database not open in ensureWasteTable";
        return false;
    }

    // For Oracle: just verify table exists by querying user_tables
    QSqlQuery query(db);
    query.exec("SELECT table_name FROM user_tables WHERE table_name='WASTE'");
<<<<<<< HEAD
    
=======

>>>>>>> 5be580a (waste X Arduino)
    if (query.next()) {
        qDebug() << "WASTE table exists in Oracle";
        return true;
    } else {
        qDebug() << "WASTE table not found. Please ensure it's created in Oracle.";
        return false;  // Table must be created in SQL Developer, not here
    }
}

bool MainWindow::ensurePickupScheduleTable()
{
    QSqlDatabase db = m_connection.getDatabase();
    if (!db.isOpen()) {
        qDebug() << "Database not open in ensurePickupScheduleTable";
        return false;
    }

    QSqlQuery existsQuery(db);
    existsQuery.exec("SELECT table_name FROM user_tables WHERE table_name='PICKUP_SCHEDULE'");
    if (existsQuery.next()) {
        return true;
    }

    QSqlQuery createQuery(db);
    const QString createSql =
        "BEGIN "
        "  EXECUTE IMMEDIATE 'CREATE TABLE PICKUP_SCHEDULE ("
        "    TICKET VARCHAR2(30) PRIMARY KEY, "
        "    WASTE_TYPE VARCHAR2(100) NOT NULL, "
        "    LOCATION VARCHAR2(120) NOT NULL, "
        "    URGENCY VARCHAR2(20) NOT NULL, "
        "    PRIORITY VARCHAR2(60) NOT NULL, "
        "    WINDOW_TEXT VARCHAR2(120) NOT NULL, "
        "    DEADLINE_AT DATE NOT NULL, "
        "    CREATED_AT DATE DEFAULT SYSDATE"
        "  )'; "
        "EXCEPTION WHEN OTHERS THEN "
        "  IF SQLCODE != -955 THEN RAISE; END IF; "
        "END;";

    if (!createQuery.exec(createSql)) {
        qDebug() << "Failed to create PICKUP_SCHEDULE:" << createQuery.lastError().text();
        return false;
    }

    return true;
}

void MainWindow::loadScheduledPickupsFromDb()
{
    m_scheduledPickups.clear();
<<<<<<< HEAD
=======
    QStringList ticketsToDelete;
>>>>>>> 5be580a (waste X Arduino)

    QSqlQuery query;
    query.prepare("SELECT TICKET, WASTE_TYPE, LOCATION, URGENCY, PRIORITY, WINDOW_TEXT, "
                  "TO_CHAR(DEADLINE_AT, 'YYYY-MM-DD HH24:MI') AS DEADLINE_AT "
                  "FROM PICKUP_SCHEDULE ORDER BY CREATED_AT ASC");

    if (!query.exec()) {
        qDebug() << "LOAD PICKUP_SCHEDULE ERROR:" << query.lastError().text();
        return;
    }

    int maxTicketNumber = 999;
    while (query.next()) {
        ScheduledPickup pickup;
        pickup.ticket = query.value("TICKET").toString();
        pickup.type = query.value("WASTE_TYPE").toString();
        pickup.location = query.value("LOCATION").toString();
        pickup.urgency = query.value("URGENCY").toString();
        pickup.priority = query.value("PRIORITY").toString();
        pickup.window = query.value("WINDOW_TEXT").toString();
        pickup.deadline = QDateTime::fromString(query.value("DEADLINE_AT").toString(), "yyyy-MM-dd HH:mm");
<<<<<<< HEAD
=======

        // Remove old scheduler rows created before percentage formatting (e.g. "78 (High)").
        if (!pickup.priority.contains('%')) {
            ticketsToDelete << pickup.ticket;
            continue;
        }

>>>>>>> 5be580a (waste X Arduino)
        m_scheduledPickups.append(pickup);

        if (pickup.ticket.startsWith("PK-")) {
            bool ok = false;
            const int ticketNumber = pickup.ticket.mid(3).toInt(&ok);
            if (ok) {
                maxTicketNumber = qMax(maxTicketNumber, ticketNumber);
            }
        }
    }

<<<<<<< HEAD
=======
    for (const QString &ticket : ticketsToDelete) {
        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM PICKUP_SCHEDULE WHERE TICKET = :ticket");
        deleteQuery.bindValue(":ticket", ticket);
        if (!deleteQuery.exec()) {
            qDebug() << "DELETE legacy PICKUP_SCHEDULE row ERROR:" << ticket << deleteQuery.lastError().text();
        }
    }

>>>>>>> 5be580a (waste X Arduino)
    m_nextPickupTicket = maxTicketNumber + 1;
}

bool MainWindow::saveScheduledPickupToDb(const ScheduledPickup &pickup)
{
    QSqlQuery query;
    query.prepare("INSERT INTO PICKUP_SCHEDULE (TICKET, WASTE_TYPE, LOCATION, URGENCY, PRIORITY, WINDOW_TEXT, DEADLINE_AT) "
                  "VALUES (:ticket, :waste_type, :location, :urgency, :priority, :window_text, TO_DATE(:deadline_at, 'YYYY-MM-DD HH24:MI'))");
    query.bindValue(":ticket", pickup.ticket);
    query.bindValue(":waste_type", pickup.type);
    query.bindValue(":location", pickup.location);
    query.bindValue(":urgency", pickup.urgency);
    query.bindValue(":priority", pickup.priority);
    query.bindValue(":window_text", pickup.window);
    query.bindValue(":deadline_at", pickup.deadline.toString("yyyy-MM-dd HH:mm"));

    if (!query.exec()) {
        qDebug() << "SAVE PICKUP_SCHEDULE ERROR:" << query.lastError().text();
        return false;
    }

    return true;
}

void MainWindow::setupWasteTable()
{
    ui->wasteTable->setColumnCount(8);
<<<<<<< HEAD
=======
    ui->wasteTable->setHorizontalHeaderLabels(QStringList()
                                              << "ID"
                                              << "Type"
                                              << "Category"
                                              << "Quantity"
                                              << "Weight (kg)"
                                              << "Collection Date"
                                              << "Location"
                                              << "Status");
>>>>>>> 5be580a (waste X Arduino)
    ui->wasteTable->horizontalHeader()->setStretchLastSection(true);
    ui->wasteTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::loadWasteToTable(const QList<Waste> &records)
{
    ui->wasteTable->setRowCount(records.size());

    for (int row = 0; row < records.size(); ++row) {
        const Waste &waste = records.at(row);
        ui->wasteTable->setItem(row, 0, new QTableWidgetItem(QString::number(waste.id())));
        ui->wasteTable->setItem(row, 1, new QTableWidgetItem(waste.type()));
        ui->wasteTable->setItem(row, 2, new QTableWidgetItem(waste.category()));
        ui->wasteTable->setItem(row, 3, new QTableWidgetItem(QString::number(waste.quantity())));
        ui->wasteTable->setItem(row, 4, new QTableWidgetItem(QString::number(waste.weightKg(), 'f', 2)));
        ui->wasteTable->setItem(row, 5, new QTableWidgetItem(waste.collectionDate().toString("yyyy-MM-dd")));
        ui->wasteTable->setItem(row, 6, new QTableWidgetItem(waste.location()));
        ui->wasteTable->setItem(row, 7, new QTableWidgetItem(waste.status()));
    }
}

void MainWindow::applyWasteSearchAndSort()
{
    QList<Waste> filtered = m_cachedWaste;
    const QString searchText = ui->searchBox->text().trimmed();

    QString sortMode = ui->sortComboBox->currentData().toString();
    if (sortMode.isEmpty()) {
        const QString sortText = ui->sortComboBox->currentText().toLower();
        if (sortText.contains("type")) {
            sortMode = "type_asc";
        } else if (sortText.contains("id")) {
            sortMode = "id_asc";
        } else if (sortText.contains("location")) {
            sortMode = "location_asc";
        } else if (sortText.contains("status")) {
            sortMode = "status_asc";
        } else {
            sortMode = "date_desc";
        }
    }

    if (!searchText.isEmpty()) {
        QList<Waste> matches;
        for (const Waste &waste : filtered) {
            bool fieldMatch = false;

            if (sortMode == "id_asc") {
                fieldMatch = QString::number(waste.id()).contains(searchText, Qt::CaseInsensitive);
            } else if (sortMode == "type_asc") {
                fieldMatch = waste.type().contains(searchText, Qt::CaseInsensitive);
            } else if (sortMode == "location_asc") {
                fieldMatch = waste.location().contains(searchText, Qt::CaseInsensitive);
            } else if (sortMode == "status_asc") {
                fieldMatch = waste.status().contains(searchText, Qt::CaseInsensitive);
            } else {
                fieldMatch = waste.collectionDate().toString("yyyy-MM-dd").contains(searchText, Qt::CaseInsensitive);
            }

            if (fieldMatch) {
                matches.append(waste);
            }
        }
        filtered = matches;
    }

    std::sort(filtered.begin(), filtered.end(), [sortMode](const Waste &left, const Waste &right) {
        if (sortMode == "date_desc") {
            return left.collectionDate() > right.collectionDate();
        }
        if (sortMode == "type_asc") {
            return QString::localeAwareCompare(left.type(), right.type()) < 0;
        }
        if (sortMode == "id_asc") {
            return left.id() < right.id();
        }
        if (sortMode == "location_asc") {
            return QString::localeAwareCompare(left.location(), right.location()) < 0;
        }
        return QString::localeAwareCompare(left.status(), right.status()) < 0;
    });

    loadWasteToTable(filtered);

    if (filtered.isEmpty()) {
        if (!searchText.isEmpty()) {
            statusBar()->showMessage("No matching records found.", 3000);
            if (m_searchHintLabel) {
                m_searchHintLabel->setVisible(true);
                m_searchHintLabel->setText("No matching records found.");
                m_searchHintLabel->setStyleSheet("QLabel { color: #ff6666; font-size: 11px; }");
            }
        } else {
            statusBar()->showMessage("No waste records available.", 3000);
            if (m_searchHintLabel) {
                m_searchHintLabel->setVisible(false);
            }
        }
    } else {
        statusBar()->clearMessage();
        if (m_searchHintLabel && searchText.isEmpty()) {
            m_searchHintLabel->setVisible(false);
        }
    }
}

bool MainWindow::collectWasteData(Waste &waste, bool forEdit)
{
    int wasteId = -1;
    QString defaultType;
    QString defaultCategory;
    int defaultQuantity = 0;
    double defaultWeight = 0.0;
    QString defaultCollectionDate = QDate::currentDate().toString("yyyy-MM-dd");
    QString defaultLocation;
    QString defaultStatus;
<<<<<<< HEAD
=======
    int defaultHumidity = 0;
    int defaultDistance = 0;
>>>>>>> 5be580a (waste X Arduino)

    if (forEdit) {
        if (!selectedWasteId(wasteId)) {
            QMessageBox::warning(this, "Edit waste", "Select a waste record row first.");
            return false;
        }

<<<<<<< HEAD
=======
        bool sensorFieldsResolved = false;
        for (const Waste &record : m_cachedWaste) {
            if (record.id() == wasteId) {
                defaultHumidity = record.humidityPercent();
                defaultDistance = record.distanceCm();
                sensorFieldsResolved = true;
                break;
            }
        }

        if (!sensorFieldsResolved && m_databaseReady) {
            const QList<Waste> fresh = Waste::readAll();
            for (const Waste &record : fresh) {
                if (record.id() == wasteId) {
                    defaultHumidity = record.humidityPercent();
                    defaultDistance = record.distanceCm();
                    break;
                }
            }
        }
    } else {
        defaultHumidity = 0;
        defaultDistance = 0;
    }

    if (forEdit) {
>>>>>>> 5be580a (waste X Arduino)
        const int row = ui->wasteTable->currentRow();
        defaultType = ui->wasteTable->item(row, 1)->text();
        defaultCategory = ui->wasteTable->item(row, 2)->text();
        defaultQuantity = ui->wasteTable->item(row, 3)->text().toInt();
        defaultWeight = ui->wasteTable->item(row, 4)->text().toDouble();
        defaultCollectionDate = ui->wasteTable->item(row, 5)->text();
        defaultLocation = ui->wasteTable->item(row, 6)->text();
        defaultStatus = ui->wasteTable->item(row, 7)->text();
    }

    QDialog dialog(this);
    dialog.setWindowTitle(forEdit ? "Edit Waste Record" : "Add Waste Record");
    dialog.setModal(true);

    QFormLayout *formLayout = new QFormLayout(&dialog);

    auto makeFieldWithHint = [&dialog](QWidget *field, const QString &hintText) {
        QWidget *container = new QWidget(&dialog);
        QVBoxLayout *layout = new QVBoxLayout(container);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(2);
        layout->addWidget(field);

        QLabel *hint = new QLabel(hintText, container);
        hint->setStyleSheet("QLabel { color: #8feecf; font-size: 10px; }");
        layout->addWidget(hint);
        return container;
    };

    QComboBox *typeCombo = new QComboBox(&dialog);
    QComboBox *categoryCombo = new QComboBox(&dialog);
    QSpinBox *quantitySpin = new QSpinBox(&dialog);
    QDoubleSpinBox *weightSpin = new QDoubleSpinBox(&dialog);
    QDateEdit *dateEdit = new QDateEdit(&dialog);
<<<<<<< HEAD
    QLineEdit *locationEdit = new QLineEdit(defaultLocation, &dialog);
    QComboBox *statusCombo = new QComboBox(&dialog);

    const QRegularExpression lettersRegex("^[A-Za-z ]{0,10}$");
    auto *lettersValidator = new QRegularExpressionValidator(lettersRegex, &dialog);

    locationEdit->setMaxLength(10);
    locationEdit->setValidator(lettersValidator);
=======
    QComboBox *locationCombo = new QComboBox(&dialog);
    QComboBox *statusCombo = new QComboBox(&dialog);

    locationCombo->setEditable(true);
    locationCombo->setInsertPolicy(QComboBox::NoInsert);
    locationCombo->setMaxVisibleItems(12);

    const QStringList tunisiaLocations = {
        "Ariana",
        "Beja",
        "Ben Arous",
        "Bizerte",
        "Gabes",
        "Gafsa",
        "Jendouba",
        "Kairouan",
        "Kasserine",
        "Kebili",
        "Kef",
        "Mahdia",
        "Manouba",
        "Medenine",
        "Monastir",
        "Nabeul",
        "Sfax",
        "Sidi Bouzid",
        "Siliana",
        "Sousse",
        "Tataouine",
        "Tozeur",
        "Tunis",
        "Zaghouan"
    };
    locationCombo->addItems(tunisiaLocations);

    QLineEdit *locationEdit = locationCombo->lineEdit();
    const QRegularExpression locationRegex(R"(^[A-Za-z \-]{0,100}$)");
    auto *locationValidator = new QRegularExpressionValidator(locationRegex, &dialog);
    locationEdit->setMaxLength(100);
    locationEdit->setValidator(locationValidator);
>>>>>>> 5be580a (waste X Arduino)

    const QStringList typeChoices = {"Organic", "Plastic", "Metal", "Glass"};
    typeCombo->addItem("-- Select Type --");
    typeCombo->addItems(typeChoices);
    typeCombo->setCurrentIndex(0);

<<<<<<< HEAD
    const QStringList categoryChoices = {"Household", "Industrial", "Medical", "Electronic"};
=======
    const QStringList categoryChoices = {
        "Household",
        "Food",
        "Industrial",
        "Medical",
        "Electronic",
        "Construction",
        "Agricultural",
        "Textile",
        "Chemical",
        "Paper",
        "Hazardous"
    };
>>>>>>> 5be580a (waste X Arduino)
    categoryCombo->addItem("-- Select Category --");
    categoryCombo->addItems(categoryChoices);
    categoryCombo->setCurrentIndex(0);

    quantitySpin->setRange(0, 1000000);
    quantitySpin->setValue(defaultQuantity);

    weightSpin->setRange(0.0, 1000000000.0);
    weightSpin->setDecimals(2);
    weightSpin->setValue(defaultWeight);

    const QDate parsedDate = QDate::fromString(defaultCollectionDate, "yyyy-MM-dd");
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    dateEdit->setDate(parsedDate.isValid() ? parsedDate : QDate::currentDate());

    const QStringList validStatuses = {"Pending", "Collected", "In Transit", "Disposed", "Recycled"};
    statusCombo->addItem("-- Select Status --");
    statusCombo->addItems(validStatuses);
    statusCombo->setCurrentIndex(0);

    if (forEdit) {
<<<<<<< HEAD
=======
        QLabel *sensorInfoLabel = new QLabel(
            QString("Humidity: %1% | Distance: %2 cm").arg(defaultHumidity).arg(defaultDistance),
            &dialog);
        sensorInfoLabel->setWordWrap(true);
        sensorInfoLabel->setStyleSheet(
            "QLabel { background: #0a1f18; color: #6bffb8; padding: 8px 10px; border-radius: 6px; border: 1px solid #1a3d2e; font-weight: 600; }");
        formLayout->addRow("Sensor info:", sensorInfoLabel);
    }

    if (forEdit) {
>>>>>>> 5be580a (waste X Arduino)
        const int typeIndex = typeCombo->findText(defaultType, Qt::MatchFixedString);
        if (typeIndex >= 0) {
            typeCombo->setCurrentIndex(typeIndex);
        }

        const int categoryIndex = categoryCombo->findText(defaultCategory, Qt::MatchFixedString);
        if (categoryIndex >= 0) {
            categoryCombo->setCurrentIndex(categoryIndex);
        }

        const int statusIndex = statusCombo->findText(defaultStatus, Qt::MatchFixedString);
        if (statusIndex >= 0) {
            statusCombo->setCurrentIndex(statusIndex);
        }
<<<<<<< HEAD
    }

    formLayout->addRow("Type:", makeFieldWithHint(typeCombo, "Choose 1 of 4 options."));
    formLayout->addRow("Category:", makeFieldWithHint(categoryCombo, "Choose 1 of 4 options."));
=======

        if (!defaultLocation.trimmed().isEmpty()) {
            if (locationCombo->findText(defaultLocation, Qt::MatchFixedString) < 0) {
                locationCombo->addItem(defaultLocation);
            }
            locationCombo->setCurrentText(defaultLocation);
        }
    } else {
        locationCombo->setCurrentIndex(-1);
        locationEdit->clear();
    }

    formLayout->addRow("Type:", makeFieldWithHint(typeCombo, "Choose 1 of 4 options."));
    formLayout->addRow("Category:", makeFieldWithHint(categoryCombo, QString("Choose 1 of %1 options.").arg(categoryChoices.size())));
>>>>>>> 5be580a (waste X Arduino)
    formLayout->addRow("Quantity:", makeFieldWithHint(quantitySpin, "Numbers only."));
    formLayout->addRow("Weight (kg):", makeFieldWithHint(weightSpin, "Decimal number, up to 2 digits after decimal."));
    formLayout->addRow("Collection Date:", makeFieldWithHint(dateEdit, "Pick a valid date."));

    QWidget *locationContainer = new QWidget(&dialog);
    QVBoxLayout *locationLayout = new QVBoxLayout(locationContainer);
    locationLayout->setContentsMargins(0, 0, 0, 0);
    locationLayout->setSpacing(2);
<<<<<<< HEAD
    locationLayout->addWidget(locationEdit);
    QLabel *locationHint = new QLabel("Location hint: letters/spaces only, max 10 characters.", locationContainer);
=======
    locationLayout->addWidget(locationCombo);
    QLabel *locationHint = new QLabel("Location hint: select a Tunisia location or type your own (letters/spaces/hyphen), max 100 characters.", locationContainer);
>>>>>>> 5be580a (waste X Arduino)
    locationHint->setStyleSheet("QLabel { color: #8feecf; font-size: 10px; }");
    locationHint->setVisible(false);
    locationLayout->addWidget(locationHint);

    QObject::connect(locationEdit, &QLineEdit::textChanged, [locationHint, locationEdit](const QString &value) {
        if (value.isEmpty()) {
            locationHint->setVisible(false);
            return;
        }

        if (value.length() >= locationEdit->maxLength()) {
            locationHint->setVisible(true);
<<<<<<< HEAD
            locationHint->setText("Maximum 10 characters reached.");
=======
            locationHint->setText("Maximum 100 characters reached.");
>>>>>>> 5be580a (waste X Arduino)
            locationHint->setStyleSheet("QLabel { color: #ff6666; font-size: 10px; }");
            return;
        }

        locationHint->setVisible(false);
    });

    QObject::connect(locationEdit, &QLineEdit::inputRejected, [locationHint, locationEdit]() {
        locationHint->setVisible(true);
        if (locationEdit->text().length() >= locationEdit->maxLength()) {
<<<<<<< HEAD
            locationHint->setText("Maximum 10 characters reached.");
        } else {
            locationHint->setText("Invalid character not allowed. Use letters and spaces only.");
=======
            locationHint->setText("Maximum 100 characters reached.");
        } else {
            locationHint->setText("Invalid character not allowed. Use letters, spaces, and hyphen only.");
>>>>>>> 5be580a (waste X Arduino)
        }
        locationHint->setStyleSheet("QLabel { color: #ff6666; font-size: 10px; }");
    });

    formLayout->addRow("Location:", locationContainer);
    formLayout->addRow("Status:", makeFieldWithHint(statusCombo, "Choose a valid status."));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    formLayout->addRow(buttonBox);

    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
<<<<<<< HEAD
    auto updateOkEnabled = [okButton, typeCombo, categoryCombo, statusCombo, locationEdit]() {
        const bool valid = typeCombo->currentIndex() > 0
                           && categoryCombo->currentIndex() > 0
                           && statusCombo->currentIndex() > 0
                           && !locationEdit->text().trimmed().isEmpty();
=======
    auto updateOkEnabled = [okButton, typeCombo, categoryCombo, statusCombo, locationCombo]() {
        const bool valid = typeCombo->currentIndex() > 0
                           && categoryCombo->currentIndex() > 0
                           && statusCombo->currentIndex() > 0
                           && !locationCombo->currentText().trimmed().isEmpty();
>>>>>>> 5be580a (waste X Arduino)
        okButton->setEnabled(valid);
    };

    updateOkEnabled();
    QObject::connect(typeCombo, qOverload<int>(&QComboBox::currentIndexChanged), &dialog, [updateOkEnabled](int) { updateOkEnabled(); });
    QObject::connect(categoryCombo, qOverload<int>(&QComboBox::currentIndexChanged), &dialog, [updateOkEnabled](int) { updateOkEnabled(); });
    QObject::connect(statusCombo, qOverload<int>(&QComboBox::currentIndexChanged), &dialog, [updateOkEnabled](int) { updateOkEnabled(); });
    QObject::connect(locationEdit, &QLineEdit::textChanged, &dialog, [updateOkEnabled](const QString &) { updateOkEnabled(); });

    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
<<<<<<< HEAD
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, [&dialog, typeCombo, categoryCombo, statusCombo, locationEdit]() {
        const QString location = locationEdit->text().trimmed();
=======
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, [&dialog, typeCombo, categoryCombo, statusCombo, locationCombo]() {
        const QString location = locationCombo->currentText().trimmed();
>>>>>>> 5be580a (waste X Arduino)

        if (typeCombo->currentIndex() <= 0 || categoryCombo->currentIndex() <= 0 || statusCombo->currentIndex() <= 0 || location.isEmpty()) {
            QMessageBox::warning(&dialog, "Validation", "Please choose Type, Category, Status and fill Location.");
            return;
        }

        dialog.accept();
    });

    if (dialog.exec() != QDialog::Accepted) {
        return false;
    }

    const QString type = typeCombo->currentText();
    const QString category = categoryCombo->currentText();
    const int quantity = quantitySpin->value();
    const double weightKg = weightSpin->value();
    const QDate collectionDate = dateEdit->date();
<<<<<<< HEAD
    const QString location = locationEdit->text().trimmed();
=======
    const QString location = locationCombo->currentText().trimmed();
>>>>>>> 5be580a (waste X Arduino)
    const QString status = statusCombo->currentText();

    waste.setId(wasteId);
    waste.setType(type);
    waste.setCategory(category);
    waste.setQuantity(quantity);
    waste.setWeightKg(weightKg);
    waste.setCollectionDate(collectionDate);
    waste.setLocation(location);
    waste.setStatus(status);
<<<<<<< HEAD
=======
    waste.setHumidityPercent(defaultHumidity);
    waste.setDistanceCm(defaultDistance);
>>>>>>> 5be580a (waste X Arduino)
    return true;
}

bool MainWindow::selectedWasteId(int &id) const
{
    const int row = ui->wasteTable->currentRow();
    if (row < 0 || !ui->wasteTable->item(row, 0)) {
        return false;
    }

    id = ui->wasteTable->item(row, 0)->text().toInt();
    return id > 0;
}

void MainWindow::onAddWasteClicked()
{
    if (!m_databaseReady) {
        QMessageBox::critical(this, "Database", "Database is not ready.");
        return;
    }

    Waste waste;
    if (!collectWasteData(waste, false)) {
        return;
    }

    if (!waste.create()) {
        QMessageBox::critical(this, "Create waste", "Unable to add waste record.");
        return;
    }

    onViewWasteClicked();
    QMessageBox::information(this, "Create waste", "Waste record created successfully.");
}

void MainWindow::onViewWasteClicked()
{
    if (!m_databaseReady) {
        ui->wasteTable->setRowCount(0);
        return;
    }

    m_cachedWaste = Waste::readAll();
    applyWasteSearchAndSort();
}

void MainWindow::onWasteStatsClicked()
{
    if (!m_databaseReady) {
        QMessageBox::critical(this, "Waste Statistics", "Database is not ready.");
        return;
    }

    const QList<Waste> records = Waste::readAll();
    if (records.isEmpty()) {
        QMessageBox::information(this, "Waste Statistics", "No waste records available to calculate statistics.");
        return;
    }

    int totalQuantity = 0;
    double totalWeight = 0.0;
    QMap<QString, int> byStatus;
    QMap<QString, int> byType;
    QMap<QString, int> byCategory;
    QMap<QString, int> byLocation;

    for (const Waste &waste : records) {
        totalQuantity += waste.quantity();
        totalWeight += waste.weightKg();
        byStatus[waste.status()] += 1;
        byType[waste.type()] += 1;
        byCategory[waste.category()] += 1;
        byLocation[waste.location()] += 1;
    }

<<<<<<< HEAD
    const double averageWeightPerRecord = records.isEmpty() ? 0.0 : (totalWeight / static_cast<double>(records.size()));
=======
    const int totalRecords = records.size();
    const double averageWeightPerRecord = records.isEmpty() ? 0.0 : (totalWeight / static_cast<double>(records.size()));
    auto toPercent = [totalRecords](int count) {
        if (totalRecords <= 0) {
            return 0.0;
        }
        return (100.0 * static_cast<double>(count)) / static_cast<double>(totalRecords);
    };
>>>>>>> 5be580a (waste X Arduino)

    QDialog statsDialog(this);
    statsDialog.setWindowTitle("Waste Statistics");
    const QRect available = QGuiApplication::primaryScreen()->availableGeometry();
    const int dialogWidth = qMax(900, static_cast<int>(available.width() * 0.9));
    const int dialogHeight = qMax(620, static_cast<int>(available.height() * 0.9));
    statsDialog.resize(dialogWidth, dialogHeight);
    statsDialog.setStyleSheet("QDialog { background-color: #020f0b; color: #e7fff6; }");

    QVBoxLayout *layout = new QVBoxLayout(&statsDialog);
    QLabel *title = new QLabel("Waste Statistics Dashboard", &statsDialog);
    title->setStyleSheet("QLabel { font-size: 20px; font-weight: 700; color: #00ff9c; padding: 4px 0; }");

    QFrame *summaryCard = new QFrame(&statsDialog);
    summaryCard->setStyleSheet("QFrame { border: 1px solid #00ff9c; border-radius: 10px; background: rgba(0, 255, 156, 0.06); }");
    QHBoxLayout *summaryLayout = new QHBoxLayout(summaryCard);

    QLabel *summaryText = new QLabel(summaryCard);
    summaryText->setStyleSheet("QLabel { color: #cffff0; font-size: 15px; border: none; }");
    summaryText->setText(
        QString("Total Records: %1    |    Total Quantity: %2    |    Total Weight: %3 kg    |    Avg Weight/Record: %4 kg")
            .arg(records.size())
            .arg(totalQuantity)
            .arg(QString::number(totalWeight, 'f', 2))
            .arg(QString::number(averageWeightPerRecord, 'f', 2)));
    summaryLayout->addWidget(summaryText);

    auto *statusSeries = new QPieSeries();
    for (auto it = byStatus.constBegin(); it != byStatus.constEnd(); ++it) {
<<<<<<< HEAD
        auto *slice = statusSeries->append(it.key(), it.value());
        slice->setLabel(QString("%1 (%2)").arg(it.key(), QString::number(it.value())));
        slice->setLabelVisible(true);
    }

    auto *statusChart = new QChart();
    statusChart->addSeries(statusSeries);
    statusChart->setTitle("Records by Status");
    statusChart->setAnimationOptions(QChart::AllAnimations);
    statusChart->legend()->setVisible(true);
    statusChart->legend()->setAlignment(Qt::AlignBottom);
=======
        const double percent = toPercent(it.value());
        auto *slice = statusSeries->append(it.key(), percent);
        slice->setLabel(QString("%1 (%2%)").arg(it.key(), QString::number(percent, 'f', 1)));
        slice->setLabelPosition(QPieSlice::LabelOutside);
        slice->setLabelVisible(true);
    }
    statusSeries->setPieSize(0.5);

    auto *statusChart = new QChart();
    statusChart->addSeries(statusSeries);
    statusChart->setTitle("Status Distribution (%)");
    statusChart->setAnimationOptions(QChart::AllAnimations);
    statusChart->legend()->setVisible(false);
    statusChart->setMargins(QMargins(22, 22, 22, 22));
>>>>>>> 5be580a (waste X Arduino)
    statusChart->setBackgroundBrush(QColor("#021a13"));
    statusChart->setTitleBrush(QBrush(QColor("#cffff0")));

    auto *statusChartView = new QChartView(statusChart, &statsDialog);
    statusChartView->setRenderHint(QPainter::Antialiasing, true);
    statusChartView->setStyleSheet("background: transparent;");
    statusChartView->setMinimumHeight(240);
    statusChartView->setMinimumWidth(360);

<<<<<<< HEAD
    auto *typeSet = new QBarSet("Type Count");
    QStringList typeCategories;
    int maxTypeCount = 0;
    for (auto it = byType.constBegin(); it != byType.constEnd(); ++it) {
        *typeSet << it.value();
        typeCategories << it.key();
        if (it.value() > maxTypeCount) {
            maxTypeCount = it.value();
        }
=======
    auto *typeSet = new QBarSet("Type %");
    QStringList typeCategories;
    for (auto it = byType.constBegin(); it != byType.constEnd(); ++it) {
        *typeSet << toPercent(it.value());
        typeCategories << it.key();
>>>>>>> 5be580a (waste X Arduino)
    }

    auto *typeSeries = new QBarSeries();
    typeSeries->append(typeSet);

    auto *typeChart = new QChart();
    typeChart->addSeries(typeSeries);
<<<<<<< HEAD
    typeChart->setTitle("Records by Type");
=======
    typeChart->setTitle("Type Distribution (%)");
>>>>>>> 5be580a (waste X Arduino)
    typeChart->setAnimationOptions(QChart::SeriesAnimations);
    typeChart->legend()->setVisible(false);
    typeChart->setBackgroundBrush(QColor("#021a13"));
    typeChart->setTitleBrush(QBrush(QColor("#cffff0")));

    auto *axisX = new QBarCategoryAxis();
    axisX->append(typeCategories);
    auto *axisY = new QValueAxis();
<<<<<<< HEAD
    axisY->setRange(0, qMax(1, maxTypeCount + 1));
    axisY->setTickCount(qMin(10, qMax(2, maxTypeCount + 2)));
=======
    axisY->setRange(0, 100);
    axisY->setTickCount(6);
    axisY->setLabelFormat("%.0f%%");
>>>>>>> 5be580a (waste X Arduino)

    typeChart->addAxis(axisX, Qt::AlignBottom);
    typeChart->addAxis(axisY, Qt::AlignLeft);
    typeSeries->attachAxis(axisX);
    typeSeries->attachAxis(axisY);

    auto *typeChartView = new QChartView(typeChart, &statsDialog);
    typeChartView->setRenderHint(QPainter::Antialiasing, true);
    typeChartView->setStyleSheet("background: transparent;");
    typeChartView->setMinimumHeight(240);
    typeChartView->setMinimumWidth(360);

    QHBoxLayout *chartsLayout = new QHBoxLayout();
    chartsLayout->addWidget(statusChartView, 1);
    chartsLayout->addWidget(typeChartView, 1);

    auto *categorySeries = new QPieSeries();
    for (auto it = byCategory.constBegin(); it != byCategory.constEnd(); ++it) {
<<<<<<< HEAD
        auto *slice = categorySeries->append(it.key(), it.value());
        slice->setLabel(QString("%1 (%2)").arg(it.key(), QString::number(it.value())));
        slice->setLabelVisible(true);
    }

    auto *categoryChart = new QChart();
    categoryChart->addSeries(categorySeries);
    categoryChart->setTitle("Records by Category");
    categoryChart->setAnimationOptions(QChart::AllAnimations);
    categoryChart->legend()->setVisible(true);
    categoryChart->legend()->setAlignment(Qt::AlignBottom);
=======
        const double percent = toPercent(it.value());
        auto *slice = categorySeries->append(it.key(), percent);
        slice->setLabel(QString("%1 (%2%)").arg(it.key(), QString::number(percent, 'f', 1)));
        slice->setLabelPosition(QPieSlice::LabelOutside);
        slice->setLabelVisible(true);
    }
    categorySeries->setPieSize(0.5);

    auto *categoryChart = new QChart();
    categoryChart->addSeries(categorySeries);
    categoryChart->setTitle("Category Distribution (%)");
    categoryChart->setAnimationOptions(QChart::AllAnimations);
    categoryChart->legend()->setVisible(false);
    categoryChart->setMargins(QMargins(22, 22, 22, 22));
>>>>>>> 5be580a (waste X Arduino)
    categoryChart->setBackgroundBrush(QColor("#021a13"));
    categoryChart->setTitleBrush(QBrush(QColor("#cffff0")));

    auto *categoryChartView = new QChartView(categoryChart, &statsDialog);
    categoryChartView->setRenderHint(QPainter::Antialiasing, true);
    categoryChartView->setStyleSheet("background: transparent;");
    categoryChartView->setMinimumHeight(240);

    QString locationBreakdown = "Location Breakdown: ";
    bool firstLocation = true;
    for (auto it = byLocation.constBegin(); it != byLocation.constEnd(); ++it) {
        if (!firstLocation) {
            locationBreakdown += " | ";
        }
<<<<<<< HEAD
        locationBreakdown += QString("%1: %2").arg(it.key(), QString::number(it.value()));
=======
        locationBreakdown += QString("%1: %2% (%3)")
                                 .arg(it.key(), QString::number(toPercent(it.value()), 'f', 1), QString::number(it.value()));
>>>>>>> 5be580a (waste X Arduino)
        firstLocation = false;
    }

    QLabel *locationLabel = new QLabel(locationBreakdown, &statsDialog);
    locationLabel->setWordWrap(true);
    locationLabel->setStyleSheet("QLabel { color: #b8fbe4; font-size: 14px; }");

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Close, &statsDialog);
    connect(buttons, &QDialogButtonBox::rejected, &statsDialog, &QDialog::reject);
    connect(buttons, &QDialogButtonBox::accepted, &statsDialog, &QDialog::accept);

    layout->addWidget(title);
    layout->addWidget(summaryCard);
    layout->addLayout(chartsLayout);
    layout->addWidget(categoryChartView);
    layout->addWidget(locationLabel);
    layout->addWidget(buttons);

    statsDialog.exec();
}

void MainWindow::onSmartPickupSchedulerClicked()
{
    if (!m_databaseReady) {
        QMessageBox::critical(this, "Smart Pickup Scheduler", "Database is not ready.");
        return;
    }

    loadScheduledPickupsFromDb();

    const QList<Waste> records = Waste::readAll();

    QStringList knownTypes;
    QStringList knownLocations;
    for (const Waste &waste : records) {
        if (!waste.type().trimmed().isEmpty() && !knownTypes.contains(waste.type())) {
            knownTypes << waste.type();
        }
        if (!waste.location().trimmed().isEmpty() && !knownLocations.contains(waste.location())) {
            knownLocations << waste.location();
        }
    }

    if (knownTypes.isEmpty()) {
        knownTypes << "General" << "Recyclable" << "Organic" << "Hazardous";
    }

    if (knownLocations.isEmpty()) {
        knownLocations << "Zone A" << "Zone B" << "Zone C";
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Smart Pickup Scheduler");
<<<<<<< HEAD
    dialog.resize(980, 650);
    dialog.setStyleSheet(
        "QDialog { background-color: #020f0b; color: #e7fff6; }"
        "QLabel { color: #cffff0; }"
=======
    dialog.resize(1020, 690);
    dialog.setStyleSheet(
        "QDialog { background-color: #020f0b; color: #e7fff6; }"
        "QLabel { color: #cffff0; background: transparent; }"
>>>>>>> 5be580a (waste X Arduino)
        "QComboBox, QSpinBox, QDateTimeEdit {"
        "  min-height: 30px;"
        "  border: 1px solid #0f6b50;"
        "  border-radius: 6px;"
        "  padding: 4px 8px;"
        "  background-color: #063022;"
        "  color: #d7fff0;"
        "}"
        "QComboBox::drop-down { border: none; width: 24px; }"
        "QComboBox QAbstractItemView {"
        "  background-color: #073a2a;"
        "  color: #d7fff0;"
        "  border: 1px solid #0f6b50;"
        "  outline: 0;"
        "  selection-background-color: #00d184;"
        "  selection-color: #02160f;"
        "}"
<<<<<<< HEAD
        "QComboBox QAbstractItemView::item { min-height: 28px; padding: 6px 8px; }");

    QVBoxLayout *rootLayout = new QVBoxLayout(&dialog);
=======
        "QComboBox QAbstractItemView::item { min-height: 28px; padding: 6px 8px; }"
        "QPushButton { min-height: 36px; }");

    QVBoxLayout *rootLayout = new QVBoxLayout(&dialog);
    rootLayout->setContentsMargins(12, 12, 12, 12);
    rootLayout->setSpacing(10);
>>>>>>> 5be580a (waste X Arduino)

    QLabel *title = new QLabel("Smart Pickup Scheduler + Priority Engine", &dialog);
    title->setStyleSheet("QLabel { font-size: 20px; font-weight: 700; color: #00ff9c; }");

    QLabel *subtitle = new QLabel("Set a real deadline, then calculate priority and live SLA status (On Track / Warning / Delayed).", &dialog);
    subtitle->setWordWrap(true);
    subtitle->setStyleSheet("QLabel { font-size: 13px; color: #b8fbe4; }");

    QFrame *formCard = new QFrame(&dialog);
    formCard->setObjectName("schedulerFormCard");
    formCard->setStyleSheet("#schedulerFormCard { border: 1px solid #00ff9c; border-radius: 10px; background: rgba(0, 255, 156, 0.05); }");
    QFormLayout *form = new QFormLayout(formCard);
<<<<<<< HEAD
=======
    form->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    form->setFormAlignment(Qt::AlignTop);
    form->setHorizontalSpacing(14);
    form->setVerticalSpacing(9);
    form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    auto makeRowLabel = [&formCard](const QString &text) {
        QLabel *label = new QLabel(text, formCard);
        label->setMinimumWidth(120);
        label->setStyleSheet("QLabel { color: #d7fff0; font-size: 14px; font-weight: 600; background: transparent; }");
        return label;
    };
>>>>>>> 5be580a (waste X Arduino)

    QComboBox *typeCombo = new QComboBox(formCard);
    typeCombo->addItems(knownTypes);
    typeCombo->setMaxVisibleItems(8);

    QComboBox *locationCombo = new QComboBox(formCard);
    locationCombo->addItems(knownLocations);
    locationCombo->setMaxVisibleItems(8);

    QSpinBox *quantitySpin = new QSpinBox(formCard);
    quantitySpin->setRange(1, 10000);
    quantitySpin->setValue(10);

    QComboBox *urgencyCombo = new QComboBox(formCard);
    urgencyCombo->addItems(QStringList() << "Low" << "Normal" << "High" << "Critical");
    urgencyCombo->setCurrentText("Normal");
    urgencyCombo->setMaxVisibleItems(8);

    QDateTimeEdit *deadlineEdit = new QDateTimeEdit(QDateTime::currentDateTime().addSecs(2 * 60 * 60), formCard);
    deadlineEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
    deadlineEdit->setCalendarPopup(true);

<<<<<<< HEAD
    QLabel *priorityLabel = new QLabel("Priority Score: 0 (Low)", formCard);
=======
    QLabel *priorityLabel = new QLabel("Priority Score: 0% (Low)", formCard);
>>>>>>> 5be580a (waste X Arduino)
    priorityLabel->setStyleSheet("QLabel { color: #00ff9c; font-weight: 600; }");

    QLabel *windowLabel = new QLabel("Suggested Pickup Window: Pending calculation", formCard);
    windowLabel->setStyleSheet("QLabel { color: #9ef6d9; font-weight: 500; }");

    QLabel *deadlineHint = new QLabel("Deadline = exact due time. SLA: On Track (>15 min left), Warning (<=15 min), Delayed (past deadline).", formCard);
    deadlineHint->setWordWrap(true);
    deadlineHint->setStyleSheet("QLabel { color: #8feecf; font-size: 11px; }");

<<<<<<< HEAD
    form->addRow("Waste Type:", typeCombo);
    form->addRow("Location:", locationCombo);
    form->addRow("Quantity:", quantitySpin);
    form->addRow("Urgency:", urgencyCombo);
    form->addRow("Deadline:", deadlineEdit);
=======
    form->addRow(makeRowLabel("Waste Type:"), typeCombo);
    form->addRow(makeRowLabel("Location:"), locationCombo);
    form->addRow(makeRowLabel("Quantity:"), quantitySpin);
    form->addRow(makeRowLabel("Urgency:"), urgencyCombo);
    form->addRow(makeRowLabel("Deadline:"), deadlineEdit);
>>>>>>> 5be580a (waste X Arduino)
    form->addRow(deadlineHint);
    form->addRow(priorityLabel);
    form->addRow(windowLabel);

    QHBoxLayout *actionRow = new QHBoxLayout();
    QPushButton *btnEvaluate = new QPushButton("Evaluate Priority", &dialog);
    QPushButton *btnAddToQueue = new QPushButton("Schedule Pickup", &dialog);
    btnEvaluate->setStyleSheet("QPushButton { border: 1px solid #00ff9c; color: #00ff9c; padding: 8px 14px; border-radius: 7px; }");
    btnAddToQueue->setStyleSheet("QPushButton { border: 1px solid #00ff9c; color: #020f0b; background: #00ff9c; padding: 8px 14px; border-radius: 7px; font-weight: 700; }");
    actionRow->addWidget(btnEvaluate);
    actionRow->addWidget(btnAddToQueue);
    actionRow->addStretch();

    QTableWidget *queueTable = new QTableWidget(&dialog);
    queueTable->setColumnCount(7);
    queueTable->setHorizontalHeaderLabels(QStringList() << "Ticket" << "Type" << "Location" << "Urgency" << "Priority" << "Window" << "SLA");
    queueTable->horizontalHeader()->setStretchLastSection(true);
    queueTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    queueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    queueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
<<<<<<< HEAD
    queueTable->setStyleSheet("QTableWidget { background-color: #031912; color: #d7fff0; gridline-color: #0f4534; border: 1px solid #0f4534; }");
=======
    queueTable->verticalHeader()->setVisible(false);
    queueTable->setAlternatingRowColors(true);
    queueTable->setStyleSheet(
        "QTableWidget {"
        "  background-color: #031912;"
        "  color: #d7fff0;"
        "  gridline-color: #0f4534;"
        "  border: 1px solid #0f4534;"
        "  alternate-background-color: #07271d;"
        "}"
        "QHeaderView::section {"
        "  background-color: #05251b;"
        "  color: #00ff9c;"
        "  padding: 6px;"
        "  border: 1px solid #0f4534;"
        "  font-weight: 700;"
        "}");
>>>>>>> 5be580a (waste X Arduino)

    auto slaFromDeadline = [](const QDateTime &deadline) {
        const QDateTime now = QDateTime::currentDateTime();
        const qint64 remainingMinutes = now.secsTo(deadline) / 60;
        if (now > deadline) {
            return QString("Delayed");
        }
        if (remainingMinutes <= 15) {
            return QString("Warning");
        }
        return QString("On Track");
    };

    auto appendScheduledRow = [=](const ScheduledPickup &pickup) {
        const int row = queueTable->rowCount();
        queueTable->insertRow(row);
        queueTable->setItem(row, 0, new QTableWidgetItem(pickup.ticket));
        queueTable->setItem(row, 1, new QTableWidgetItem(pickup.type));
        queueTable->setItem(row, 2, new QTableWidgetItem(pickup.location));
        queueTable->setItem(row, 3, new QTableWidgetItem(pickup.urgency));
        queueTable->setItem(row, 4, new QTableWidgetItem(pickup.priority));
        queueTable->setItem(row, 5, new QTableWidgetItem(QString("%1 | Deadline: %2")
<<<<<<< HEAD
                                                          .arg(pickup.window)
                                                          .arg(pickup.deadline.toString("yyyy-MM-dd HH:mm"))));
=======
                                                             .arg(pickup.window)
                                                             .arg(pickup.deadline.toString("yyyy-MM-dd HH:mm"))));
>>>>>>> 5be580a (waste X Arduino)
        queueTable->setItem(row, 6, new QTableWidgetItem(slaFromDeadline(pickup.deadline)));
    };

    for (const ScheduledPickup &pickup : m_scheduledPickups) {
        appendScheduledRow(pickup);
    }

    auto evaluatePriority = [=]() {
        const QString typeText = typeCombo->currentText().toLower();
        const QString urgencyText = urgencyCombo->currentText();
        const int quantity = quantitySpin->value();
        const QDateTime now = QDateTime::currentDateTime();
        const QDateTime deadline = deadlineEdit->dateTime();
        const qint64 minutesToDeadline = now.secsTo(deadline) / 60;

        int typeWeight = 35;
        if (typeText.contains("hazard") || typeText.contains("chemical") || typeText.contains("medical")) {
            typeWeight = 65;
        } else if (typeText.contains("recycl")) {
            typeWeight = 45;
        } else if (typeText.contains("organic")) {
            typeWeight = 40;
        }

        int urgencyWeight = 20;
        if (urgencyText == "Critical") {
            urgencyWeight = 60;
        } else if (urgencyText == "High") {
            urgencyWeight = 45;
        } else if (urgencyText == "Normal") {
            urgencyWeight = 30;
        }

        const int quantityWeight = qMin(20, quantity / 25);
        int deadlinePressureWeight = 0;
        if (minutesToDeadline <= 60) {
            deadlinePressureWeight = 20;
        } else if (minutesToDeadline <= 180) {
            deadlinePressureWeight = 12;
        } else if (minutesToDeadline <= 360) {
            deadlinePressureWeight = 6;
        }

        const int score = qBound(1, typeWeight + urgencyWeight + quantityWeight + deadlinePressureWeight, 100);

        QString priorityBand = "Low";
        QString timeWindow = "Within 24 hours";
        QString slaState = "On Track";

        if (score >= 80) {
            priorityBand = "Critical";
            timeWindow = "Within 2 hours";
        } else if (score >= 60) {
            priorityBand = "High";
            timeWindow = "Within 6 hours";
        } else if (score >= 40) {
            priorityBand = "Medium";
            timeWindow = "Within 12 hours";
        }

        slaState = slaFromDeadline(deadline);

<<<<<<< HEAD
        priorityLabel->setText(QString("Priority Score: %1 (%2)").arg(score).arg(priorityBand));
        windowLabel->setText(QString("Suggested Pickup Window: %1 | Deadline: %2 | SLA: %3")
                     .arg(timeWindow)
                     .arg(deadline.toString("yyyy-MM-dd HH:mm"))
                     .arg(slaState));
=======
        priorityLabel->setText(QString("Priority Score: %1% (%2)").arg(score).arg(priorityBand));
        windowLabel->setText(QString("Suggested Pickup Window: %1 | Deadline: %2 | SLA: %3")
                                 .arg(timeWindow)
                                 .arg(deadline.toString("yyyy-MM-dd HH:mm"))
                                 .arg(slaState));
>>>>>>> 5be580a (waste X Arduino)

        return QPair<QPair<int, QString>, QPair<QString, QString>>(
            QPair<int, QString>(score, priorityBand),
            QPair<QString, QString>(timeWindow, slaState));
    };

    connect(btnEvaluate, &QPushButton::clicked, &dialog, [=]() {
        evaluatePriority();
    });

    connect(btnAddToQueue, &QPushButton::clicked, &dialog, [=, &dialog]() {
        const auto evaluation = evaluatePriority();
        const int score = evaluation.first.first;
        const QString band = evaluation.first.second;
        const QString window = evaluation.second.first;
        const QString sla = evaluation.second.second;

        ScheduledPickup pickup;
        pickup.ticket = QString("PK-%1").arg(m_nextPickupTicket++);
        pickup.type = typeCombo->currentText();
        pickup.location = locationCombo->currentText();
        pickup.urgency = urgencyCombo->currentText();
<<<<<<< HEAD
        pickup.priority = QString("%1 (%2)").arg(score).arg(band);
=======
        pickup.priority = QString("%1% (%2)").arg(score).arg(band);
>>>>>>> 5be580a (waste X Arduino)
        pickup.window = window;
        pickup.deadline = deadlineEdit->dateTime();

        if (!saveScheduledPickupToDb(pickup)) {
            QMessageBox::critical(&dialog,
                                  "Smart Pickup Scheduler",
                                  "Could not save this pickup to database.");
            return;
        }

        m_scheduledPickups.append(pickup);
        appendScheduledRow(pickup);

        QTableWidgetItem *slaItem = queueTable->item(queueTable->rowCount() - 1, 6);
        if (slaItem) {
            slaItem->setText(sla);
        }
    });

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Close, &dialog);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);

    rootLayout->addWidget(title);
    rootLayout->addWidget(subtitle);
    rootLayout->addWidget(formCard);
    rootLayout->addLayout(actionRow);
    rootLayout->addWidget(queueTable, 1);
    rootLayout->addWidget(buttons);

    dialog.exec();
}

void MainWindow::onEditWasteClicked()
{
    if (!m_databaseReady) {
        QMessageBox::critical(this, "Database", "Database is not ready.");
        return;
    }

    Waste waste;
    if (!collectWasteData(waste, true)) {
        return;
    }

    if (!waste.update()) {
        QMessageBox::critical(this, "Edit waste", "Unable to update waste record.");
        return;
    }

    onViewWasteClicked();
    QMessageBox::information(this, "Edit waste", "Waste record updated successfully.");
}

void MainWindow::onDeleteWasteClicked()
{
    if (!m_databaseReady) {
        QMessageBox::critical(this, "Database", "Database is not ready.");
        return;
    }

    int wasteId = -1;
    if (!selectedWasteId(wasteId)) {
        QMessageBox::warning(this, "Delete waste", "Select a waste record row first.");
        return;
    }

    const auto response = QMessageBox::question(this,
                                                "Delete waste",
                                                "Are you sure you want to delete this waste record?",
                                                QMessageBox::Yes | QMessageBox::No);
    if (response != QMessageBox::Yes) {
        return;
    }

    if (!Waste::remove(wasteId)) {
        QMessageBox::critical(this, "Delete waste", "Unable to delete waste record.");
        return;
    }

    onViewWasteClicked();
}

void MainWindow::onClearWasteClicked()
{
    ui->searchBox->clear();
    ui->sortComboBox->setCurrentIndex(0);
    ui->wasteTable->clearSelection();
    ui->wasteTable->setCurrentCell(-1, -1);

    if (m_databaseReady) {
        m_cachedWaste = Waste::readAll();
    }
    applyWasteSearchAndSort();

    statusBar()->showMessage("Filters and selection cleared", 2000);
}

void MainWindow::onExportWastePdfClicked()
{
    if (!ui->wasteTable || ui->wasteTable->rowCount() == 0) {
        QMessageBox::information(this, "Export PDF", "No data to export.");
        return;
    }

    const QString defaultName = QString("waste_records_%1.pdf")
                                    .arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));
    const QString filePath = QFileDialog::getSaveFileName(this,
                                                          "Export Waste Table to PDF",
                                                          defaultName,
                                                          "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }

    QString targetPath = filePath;
    if (!targetPath.endsWith(".pdf", Qt::CaseInsensitive)) {
        targetPath += ".pdf";
    }

    QPdfWriter writer(targetPath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageOrientation(QPageLayout::Landscape);
    writer.setResolution(120);
    writer.setTitle("Waste Records Export");

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Export PDF", "Unable to create PDF file.");
        return;
    }

    const int left = 60;
    const int top = 80;
    const int rowHeight = 32;
    const int pageWidth = writer.width();
    const int pageHeight = writer.height();
    const int tableWidth = pageWidth - (left * 2);

    painter.setPen(Qt::black);
    QFont titleFont = painter.font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(left, top, "Waste Records");

    QFont textFont = painter.font();
    textFont.setPointSize(9);
    textFont.setBold(false);
    painter.setFont(textFont);

    const int columnCount = ui->wasteTable->columnCount();
    if (columnCount <= 0) {
        painter.end();
        QMessageBox::information(this, "Export PDF", "No columns to export.");
        return;
    }

    const int colWidth = tableWidth / columnCount;
    int y = top + 30;

    auto drawHeader = [&]() {
        painter.setPen(Qt::black);
        painter.drawRect(left, y, tableWidth, rowHeight);
        for (int col = 0; col < columnCount; ++col) {
            const int x = left + (col * colWidth);
            if (col > 0) {
                painter.drawLine(x, y, x, y + rowHeight);
            }
            QTableWidgetItem *headerItem = ui->wasteTable->horizontalHeaderItem(col);
            const QString headerText = headerItem ? headerItem->text() : QString("Column %1").arg(col + 1);
            painter.drawText(x + 4, y + 21, headerText);
        }
        y += rowHeight;
    };

    drawHeader();

    for (int row = 0; row < ui->wasteTable->rowCount(); ++row) {
        if (y + rowHeight > pageHeight - 60) {
            writer.newPage();
            y = top;
            drawHeader();
        }

        painter.drawRect(left, y, tableWidth, rowHeight);
        for (int col = 0; col < columnCount; ++col) {
            const int x = left + (col * colWidth);
            if (col > 0) {
                painter.drawLine(x, y, x, y + rowHeight);
            }
            QTableWidgetItem *item = ui->wasteTable->item(row, col);
            const QString cellText = item ? item->text() : QString();
            painter.drawText(x + 4, y + 21, cellText);
        }

        y += rowHeight;
    }

    painter.end();
    QMessageBox::information(this, "Export PDF", QString("Export completed:\n%1").arg(targetPath));
}

void MainWindow::onViewOnMapClicked()
{
<<<<<<< HEAD
        if (!ui->wasteTable || !ui->wasteTable->selectionModel()) {
                QMessageBox::warning(this, "View on Map", "Waste table is not ready.");
                return;
        }

        const QModelIndexList selectedRows = ui->wasteTable->selectionModel()->selectedRows();
        if (selectedRows.isEmpty()) {
                QMessageBox::warning(this, "View on Map", "Please select a row first.");
                return;
        }

        const int row = selectedRows.first().row();
        QTableWidgetItem *locationItem = ui->wasteTable->item(row, 6);
        const QString locationName = locationItem ? locationItem->text().trimmed() : QString();
        if (locationName.isEmpty()) {
                QMessageBox::warning(this, "View on Map", "Selected row has no location value.");
                return;
        }

        const QMap<QString, QPair<double, double>> cityCoords = {
                {"tunis", {36.8065, 10.1815}},
                {"ariana", {36.8665, 10.1647}},
                {"nabeul", {36.4561, 10.7376}},
                {"sousse", {35.8256, 10.6084}},
                {"sfax", {34.7406, 10.7603}},
                {"bizerta", {37.2744, 9.8739}},
                {"monastir", {35.7643, 10.8113}},
                {"kairouan", {35.6781, 10.0963}},
                {"gabes", {33.8815, 10.0982}},
                {"beja", {36.7333, 9.1833}}
        };

        const QString key = locationName.trimmed().toLower();
        double latitude = 0.0;
        double longitude = 0.0;
        bool hasCoordinates = false;

        if (cityCoords.contains(key)) {
            latitude = cityCoords.value(key).first;
            longitude = cityCoords.value(key).second;
            hasCoordinates = true;
        } else {
            QNetworkAccessManager network;
            QUrl url("https://nominatim.openstreetmap.org/search");
            QUrlQuery query;
            query.addQueryItem("q", locationName + ", Tunisia");
            query.addQueryItem("format", "json");
            query.addQueryItem("limit", "1");
            query.addQueryItem("countrycodes", "tn");
            url.setQuery(query);

            QNetworkRequest request(url);
            request.setRawHeader("User-Agent", "ManarWasteApp/1.0 (educational project)");

            QNetworkReply *reply = network.get(request);
            QEventLoop loop;
            QTimer timeout;
            timeout.setSingleShot(true);
            QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            QObject::connect(&timeout, &QTimer::timeout, &loop, &QEventLoop::quit);
            timeout.start(7000);
            loop.exec();

            if (timeout.isActive() && reply->error() == QNetworkReply::NoError) {
                const QByteArray body = reply->readAll();
                const QJsonDocument jsonDoc = QJsonDocument::fromJson(body);
                if (jsonDoc.isArray()) {
                    const QJsonArray results = jsonDoc.array();
                    if (!results.isEmpty()) {
                        const QJsonObject first = results.first().toObject();
                        bool latOk = false;
                        bool lonOk = false;
                        latitude = first.value("lat").toString().toDouble(&latOk);
                        longitude = first.value("lon").toString().toDouble(&lonOk);
                        hasCoordinates = latOk && lonOk;
                    }
                }
            }

            reply->deleteLater();
        }

        if (!hasCoordinates) {
            QMessageBox::warning(this,
                         "View on Map",
                         QString("Could not find coordinates for '%1' in Tunisia.\n"
                             "Tip: check spelling (e.g. Korba, Kelibia, Mahdia).")
                         .arg(locationName));
            return;
        }

        QDialog *mapDialog = new QDialog(this);
        mapDialog->setAttribute(Qt::WA_DeleteOnClose, true);
        mapDialog->setWindowTitle(QString("Map - %1").arg(locationName));
        mapDialog->resize(940, 700);

        QVBoxLayout *layout = new QVBoxLayout(mapDialog);
        layout->setContentsMargins(8, 8, 8, 8);
        layout->setSpacing(8);

        QLabel *hint = new QLabel("Use mouse wheel to zoom and left-drag to move the map.", mapDialog);
        hint->setStyleSheet("QLabel { color: #9ef6d9; font-size: 12px; }");

        QHBoxLayout *toolbar = new QHBoxLayout();
        QPushButton *zoomInBtn = new QPushButton("+", mapDialog);
        QPushButton *zoomOutBtn = new QPushButton("-", mapDialog);
        QPushButton *resetBtn = new QPushButton("Reset", mapDialog);
        const QString btnStyle = "QPushButton { min-width: 34px; min-height: 30px; border: 1px solid #00d084; color: #d8fff1; background-color: #06241b; border-radius: 6px; }"
                                "QPushButton:hover { background-color: #0b3327; }";
        zoomInBtn->setStyleSheet(btnStyle);
        zoomOutBtn->setStyleSheet(btnStyle);
        resetBtn->setStyleSheet(btnStyle);
        toolbar->addWidget(zoomInBtn);
        toolbar->addWidget(zoomOutBtn);
        toolbar->addWidget(resetBtn);
        toolbar->addStretch();

        OSMTileMapWidget *mapWidget = new OSMTileMapWidget(mapDialog);
        mapWidget->setMarker(latitude, longitude, locationName);

        QObject::connect(zoomInBtn, &QPushButton::clicked, mapWidget, [mapWidget]() { mapWidget->zoomIn(); });
        QObject::connect(zoomOutBtn, &QPushButton::clicked, mapWidget, [mapWidget]() { mapWidget->zoomOut(); });
        QObject::connect(resetBtn, &QPushButton::clicked, mapWidget, [mapWidget]() { mapWidget->resetView(); });

        layout->addLayout(toolbar);
        layout->addWidget(hint);
        layout->addWidget(mapWidget, 1);
        mapDialog->show();
=======
    if (!ui->wasteTable || !ui->wasteTable->selectionModel()) {
        QMessageBox::warning(this, "View on Map", "Waste table is not ready.");
        return;
    }

    const QModelIndexList selectedRows = ui->wasteTable->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "View on Map", "Please select a row first.");
        return;
    }

    const int row = selectedRows.first().row();
    QTableWidgetItem *locationItem = ui->wasteTable->item(row, 6);
    const QString locationName = locationItem ? locationItem->text().trimmed() : QString();
    if (locationName.isEmpty()) {
        QMessageBox::warning(this, "View on Map", "Selected row has no location value.");
        return;
    }

    const QMap<QString, QPair<double, double>> cityCoords = {
        {"tunis", {36.8065, 10.1815}},
        {"ariana", {36.8665, 10.1647}},
        {"nabeul", {36.4561, 10.7376}},
        {"sousse", {35.8256, 10.6084}},
        {"sfax", {34.7406, 10.7603}},
        {"bizerta", {37.2744, 9.8739}},
        {"monastir", {35.7643, 10.8113}},
        {"kairouan", {35.6781, 10.0963}},
        {"gabes", {33.8815, 10.0982}},
        {"beja", {36.7333, 9.1833}}
    };

    const QString key = locationName.trimmed().toLower();
    double latitude = 0.0;
    double longitude = 0.0;
    bool hasCoordinates = false;

    if (cityCoords.contains(key)) {
        latitude = cityCoords.value(key).first;
        longitude = cityCoords.value(key).second;
        hasCoordinates = true;
    } else {
        QNetworkAccessManager network;
        QUrl url("https://nominatim.openstreetmap.org/search");
        QUrlQuery query;
        query.addQueryItem("q", locationName + ", Tunisia");
        query.addQueryItem("format", "json");
        query.addQueryItem("limit", "1");
        query.addQueryItem("countrycodes", "tn");
        url.setQuery(query);

        QNetworkRequest request(url);
        request.setRawHeader("User-Agent", "ManarWasteApp/1.0 (educational project)");

        QNetworkReply *reply = network.get(request);
        QEventLoop loop;
        QTimer timeout;
        timeout.setSingleShot(true);
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        QObject::connect(&timeout, &QTimer::timeout, &loop, &QEventLoop::quit);
        timeout.start(7000);
        loop.exec();

        if (timeout.isActive() && reply->error() == QNetworkReply::NoError) {
            const QByteArray body = reply->readAll();
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(body);
            if (jsonDoc.isArray()) {
                const QJsonArray results = jsonDoc.array();
                if (!results.isEmpty()) {
                    const QJsonObject first = results.first().toObject();
                    bool latOk = false;
                    bool lonOk = false;
                    latitude = first.value("lat").toString().toDouble(&latOk);
                    longitude = first.value("lon").toString().toDouble(&lonOk);
                    hasCoordinates = latOk && lonOk;
                }
            }
        }

        reply->deleteLater();
    }

    if (!hasCoordinates) {
        QMessageBox::warning(this,
                             "View on Map",
                             QString("Could not find coordinates for '%1' in Tunisia.\n"
                                     "Tip: check spelling (e.g. Korba, Kelibia, Mahdia).")
                                 .arg(locationName));
        return;
    }

    QDialog *mapDialog = new QDialog(this);
    mapDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mapDialog->setWindowTitle(QString("Map - %1").arg(locationName));
    mapDialog->resize(940, 700);

    QVBoxLayout *layout = new QVBoxLayout(mapDialog);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(8);

    QLabel *hint = new QLabel("Use mouse wheel to zoom and left-drag to move the map.", mapDialog);
    hint->setStyleSheet("QLabel { color: #9ef6d9; font-size: 12px; }");

    QHBoxLayout *toolbar = new QHBoxLayout();
    QPushButton *zoomInBtn = new QPushButton("+", mapDialog);
    QPushButton *zoomOutBtn = new QPushButton("-", mapDialog);
    QPushButton *resetBtn = new QPushButton("Reset", mapDialog);
    const QString btnStyle = "QPushButton { min-width: 34px; min-height: 30px; border: 1px solid #00d084; color: #d8fff1; background-color: #06241b; border-radius: 6px; }"
                             "QPushButton:hover { background-color: #0b3327; }";
    zoomInBtn->setStyleSheet(btnStyle);
    zoomOutBtn->setStyleSheet(btnStyle);
    resetBtn->setStyleSheet(btnStyle);
    toolbar->addWidget(zoomInBtn);
    toolbar->addWidget(zoomOutBtn);
    toolbar->addWidget(resetBtn);
    toolbar->addStretch();

    OSMTileMapWidget *mapWidget = new OSMTileMapWidget(mapDialog);
    mapWidget->setMarker(latitude, longitude, locationName);

    QObject::connect(zoomInBtn, &QPushButton::clicked, mapWidget, [mapWidget]() { mapWidget->zoomIn(); });
    QObject::connect(zoomOutBtn, &QPushButton::clicked, mapWidget, [mapWidget]() { mapWidget->zoomOut(); });
    QObject::connect(resetBtn, &QPushButton::clicked, mapWidget, [mapWidget]() { mapWidget->resetView(); });

    layout->addLayout(toolbar);
    layout->addWidget(hint);
    layout->addWidget(mapWidget, 1);
    mapDialog->show();
>>>>>>> 5be580a (waste X Arduino)
}

void MainWindow::on_btnClearSelection_clicked()
{
    onClearWasteClicked();
}

void MainWindow::on_btnEmpClear_clicked()
{
    onClearWasteClicked();
}

void MainWindow::onWasteSearchChanged(const QString &text)
{
    if (m_searchHintLabel) {
        if (text.isEmpty()) {
            m_searchHintLabel->setVisible(false);
            applyWasteSearchAndSort();
            return;
        }

        QString sortMode = ui->sortComboBox->currentData().toString();
        if (sortMode.isEmpty()) {
            const QString sortText = ui->sortComboBox->currentText().toLower();
            if (sortText.contains("type")) {
                sortMode = "type_asc";
            } else if (sortText.contains("id")) {
                sortMode = "id_asc";
            } else if (sortText.contains("location")) {
                sortMode = "location_asc";
            } else if (sortText.contains("status")) {
                sortMode = "status_asc";
            } else {
                sortMode = "date_desc";
            }
        }

        QRegularExpression allowedPattern;
        if (sortMode == "id_asc") {
            allowedPattern = QRegularExpression("^[0-9]{0,10}$");
        } else if (sortMode == "date_desc") {
            allowedPattern = QRegularExpression("^[0-9\\-]{0,10}$");
        } else {
            allowedPattern = QRegularExpression("^[A-Za-z ]{0,10}$");
        }

        if (!allowedPattern.match(text).hasMatch()) {
            m_searchHintLabel->setVisible(true);
            if (sortMode == "id_asc") {
                m_searchHintLabel->setText("Invalid input: ID search accepts numbers only (max 10).");
            } else if (sortMode == "date_desc") {
                m_searchHintLabel->setText("Invalid input: Date search accepts digits and '-' only (max 10).");
            } else {
                m_searchHintLabel->setText("Invalid input: this search accepts letters/spaces only (max 10).");
            }
            m_searchHintLabel->setStyleSheet("QLabel { color: #ff6666; font-size: 11px; }");
        } else if (text.length() >= ui->searchBox->maxLength()) {
            m_searchHintLabel->setVisible(true);
            m_searchHintLabel->setText("Maximum 10 characters reached.");
            m_searchHintLabel->setStyleSheet("QLabel { color: #ff6666; font-size: 11px; }");
        } else {
            m_searchHintLabel->setVisible(false);
        }
    }

    applyWasteSearchAndSort();
}

void MainWindow::onWasteSortChanged(int index)
{
    Q_UNUSED(index)

    QString sortMode = ui->sortComboBox->currentData().toString();
    if (sortMode.isEmpty()) {
        const QString sortText = ui->sortComboBox->currentText().toLower();
        if (sortText.contains("type")) {
            sortMode = "type_asc";
        } else if (sortText.contains("id")) {
            sortMode = "id_asc";
        } else if (sortText.contains("location")) {
            sortMode = "location_asc";
        } else if (sortText.contains("status")) {
            sortMode = "status_asc";
        } else {
            sortMode = "date_desc";
        }
    }

    if (sortMode == "id_asc") {
        ui->searchBox->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,10}$"), this));
    } else if (sortMode == "date_desc") {
        ui->searchBox->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9\\-]{0,10}$"), this));
    } else {
        ui->searchBox->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-z ]{0,10}$"), this));
    }

    ui->searchBox->clear();

    applyWasteSearchAndSort();
}

void MainWindow::showWastePage()
{
    ui->stackedwidget->setCurrentWidget(ui->wastemanagement);
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
void MainWindow::showMachinePage()
{
    ui->stackedwidget->setCurrentWidget(ui->machinePage);
}
<<<<<<< HEAD
void MainWindow::showSupplierPage()
{
    ui->stackedwidget->setCurrentWidget(ui->supplier);
}
=======
=======

>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
// ================= YOUR ORIGINAL FUNCTIONS =================

>>>>>>> origin/waste
void MainWindow::showLoginPage()
{
    ui->stackedwidget->setCurrentWidget(ui->connection);
=======
void MainWindow::showLoginPage()
{
    ui->stackedwidget->setCurrentWidget(ui->main);
>>>>>>> 5be580a (waste X Arduino)
}

void MainWindow::showRecoveryPage()
{
    ui->stackedwidget->setCurrentWidget(ui->recoverpwd);
}

void MainWindow::showVerificationPage()
{
    ui->stackedwidget->setCurrentWidget(ui->verification);
}

void MainWindow::showMainMenu()
{
<<<<<<< HEAD
    ui->stackedwidget->setCurrentWidget(ui->main);
=======
    ui->stackedwidget->setCurrentWidget(ui->wastemanagement);
>>>>>>> 5be580a (waste X Arduino)
}

void MainWindow::showEmployeePage()
{
    ui->stackedwidget->setCurrentWidget(ui->employe);
}
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
void MainWindow::showVehiclePage()
{
    ui->stackedwidget->setCurrentWidget(ui->vehiclePage);
}
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
=======
>>>>>>> 5be580a (waste X Arduino)

void MainWindow::showCustomerPage()
{
    // When you create the customer page, navigate to it
    // ui->stackedwidget->setCurrentWidget(ui->customer);
}

void MainWindow::onLoginClicked()
{
    QString username = ui->loginUsername->text();
    QString password = ui->loginPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        return;
    }

    showMainMenu();
}

void MainWindow::onVerifyClicked()
{
    QString code = ui->verifyCode->text();

    if (code.isEmpty()) {
        return;
    }

    showMainMenu();
}
<<<<<<< HEAD
=======


// ═══════════════════════════════════════════════════════════════════════════
// Arduino Sensor – member function implementations
// ═══════════════════════════════════════════════════════════════════════════

void MainWindow::setupArduinoSensor()
{
    m_arduino = new ArduinoSensor(this);

    m_arduinoStatus = new QLabel("Arduino: not connected", this);
    m_arduinoStatus->setStyleSheet("color: #ff6b6b; padding: 0 6px;");
    statusBar()->addPermanentWidget(m_arduinoStatus);

    connect(m_arduino, &ArduinoSensor::connectionChanged,
            this,      &MainWindow::onArduinoConnectionChanged);

    connect(m_arduino, &ArduinoSensor::readingReady,
            this,      &MainWindow::onSensorAutoSave);

    // Do not auto-open a serial port at startup — let the user initiate
    // a connection from the Sensor Details dialog. Auto-opening can fail
    // when another program (e.g. Arduino IDE) already holds the port.
}

void MainWindow::onSensorAutoSave(ArduinoSensor::Reading reading)
{
    if (!reading.isValid || !m_databaseReady || m_suppressArduinoAutoSave)
        return;

    Waste waste;
    waste.setType(reading.isWet ? "Organic" : "Plastic");
    waste.setCategory("Household");
    waste.setQuantity(0);
    waste.setWeightKg(0.0);
    waste.setCollectionDate(QDate::currentDate());
    waste.setLocation("Auto");
    waste.setStatus("Pending");
    waste.setHumidityPercent(reading.humidity);
    waste.setDistanceCm(reading.distance);

    if (waste.create()) {
        qDebug() << "Auto-saved waste from sensor: humidity=" << reading.humidity
                 << "distance=" << reading.distance;
        onViewWasteClicked(); // refresh the table
    } else {
        qWarning() << "Auto-save failed!";
    }

    // Request next reading automatically
    m_arduino->requestReading(8000);
}

// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::onSensorDetailsClicked()
{
    if (!m_databaseReady) {
        QMessageBox::critical(this, "Sensor Details", "Database is not ready.");
        return;
    }

    const QList<Waste> all = Waste::readAll();
    if (all.isEmpty()) {
        QMessageBox::information(this, "Sensor Details", "No waste records available.");
        return;
    }

    int selectedId = -1;
    if (!selectedWasteId(selectedId)) {
        selectedId = all.first().id();
    }

    QHash<int, Waste> wasteById;
    for (const Waste &waste : all) {
        wasteById.insert(waste.id(), waste);
    }

    if (!wasteById.contains(selectedId)) {
        selectedId = all.first().id();
    }

    Waste selectedWaste = wasteById.value(selectedId);

    // ── 2. Build dialog ───────────────────────────────────────────────────────
    QDialog dialog(this);
    dialog.setWindowTitle("Sensor Details — Waste #" + QString::number(selectedWaste.id()));
    dialog.setMinimumWidth(500);
    dialog.setStyleSheet("QDialog { background: #050d0a; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setSpacing(14);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Title
    QLabel *title = new QLabel("Sensor Details — Waste #" + QString::number(selectedWaste.id()), &dialog);
    title->setStyleSheet("font-size: 16px; font-weight: bold; color: #ffffff; border: none;");
    mainLayout->addWidget(title);

    QLabel *selectLabel = new QLabel("Select waste (ID or location):", &dialog);
    selectLabel->setStyleSheet("QLabel { color: #b8fbe4; font-size: 12px; }");
    mainLayout->addWidget(selectLabel);

    QComboBox *wasteCombo = new QComboBox(&dialog);
    wasteCombo->setEditable(true);
    wasteCombo->setInsertPolicy(QComboBox::NoInsert);
    wasteCombo->setMaxVisibleItems(12);
    for (const Waste &waste : all) {
        const QString display = QString("#%1 - %2 (%3)")
        .arg(waste.id())
            .arg(waste.location().isEmpty() ? "Unknown" : waste.location())
            .arg(waste.type().isEmpty() ? "Unknown" : waste.type());
        wasteCombo->addItem(display, waste.id());
    }
    const int initialIndex = wasteCombo->findData(selectedId);
    if (initialIndex >= 0) {
        wasteCombo->setCurrentIndex(initialIndex);
    }
    mainLayout->addWidget(wasteCombo);

    // Selected waste info banner
    QLabel *infoBanner = new QLabel(
        QString("Selected: <b>%1</b> · %2 · %3")
            .arg(selectedWaste.type(), selectedWaste.category(), selectedWaste.location()),
        &dialog);
    infoBanner->setStyleSheet("QLabel { background: #0a1f18; color: #66ffcc; padding: 8px 12px; border-radius: 8px; border: 1px solid #1a3d2e; }");
    infoBanner->setTextFormat(Qt::RichText);
    mainLayout->addWidget(infoBanner);

    auto updateSelectedWaste = [&](int id) {
        if (!wasteById.contains(id)) {
            return;
        }
        selectedId = id;
        selectedWaste = wasteById.value(id);
        title->setText("Sensor Details — Waste #" + QString::number(selectedWaste.id()));
        infoBanner->setText(
            QString("Selected: <b>%1</b> · %2 · %3")
                .arg(selectedWaste.type(), selectedWaste.category(), selectedWaste.location()));
    };

    QObject::connect(wasteCombo, qOverload<int>(&QComboBox::currentIndexChanged), &dialog, [=, &updateSelectedWaste](int) {
        updateSelectedWaste(wasteCombo->currentData().toInt());
    });

    QLineEdit *wasteEdit = wasteCombo->lineEdit();
    QObject::connect(wasteEdit, &QLineEdit::textChanged, &dialog, [=, &updateSelectedWaste](const QString &text) {
        const QString trimmed = text.trimmed();
        if (trimmed.isEmpty()) {
            return;
        }

        bool ok = false;
        const int typedId = trimmed.toInt(&ok);
        if (ok && wasteById.contains(typedId)) {
            const int idx = wasteCombo->findData(typedId);
            if (idx >= 0) {
                wasteCombo->setCurrentIndex(idx);
            }
            updateSelectedWaste(typedId);
            return;
        }

        for (const Waste &waste : all) {
            if (waste.location().compare(trimmed, Qt::CaseInsensitive) == 0) {
                const int idx = wasteCombo->findData(waste.id());
                if (idx >= 0) {
                    wasteCombo->setCurrentIndex(idx);
                }
                updateSelectedWaste(waste.id());
                return;
            }
        }
    });

    // ── 3. Sensor reading cards (live) ────────────────────────────────────────
    QFrame *cardsFrame = new QFrame(&dialog);
    QHBoxLayout *cardsLayout = new QHBoxLayout(cardsFrame);
    cardsLayout->setSpacing(10);
    cardsLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *humCard  = new QLabel("Humidity\n—", &dialog);
    QLabel *distCard = new QLabel("Distance\n—", &dialog);
    QLabel *typeCard = new QLabel("Type\n—", &dialog);

    const QString cardStyle = "QLabel { background: #0a1f18; border: 1px solid #1a3d2e; border-radius: 10px; "
                              "padding: 14px; color: #66ffcc; font-size: 13px; min-width: 110px; }";
    humCard->setStyleSheet(cardStyle);
    distCard->setStyleSheet(cardStyle);
    typeCard->setStyleSheet(cardStyle);
    humCard->setAlignment(Qt::AlignCenter);
    distCard->setAlignment(Qt::AlignCenter);
    typeCard->setAlignment(Qt::AlignCenter);

    cardsLayout->addWidget(humCard);
    cardsLayout->addWidget(distCard);
    cardsLayout->addWidget(typeCard);
    mainLayout->addWidget(cardsFrame);

    // ── 4. Status label ───────────────────────────────────────────────────────
    const bool arduinoConnected = m_arduino && m_arduino->isConnected();
    QLabel *statusLabel = new QLabel("", &dialog);
    statusLabel->setWordWrap(true);
    statusLabel->setStyleSheet("QLabel { background: transparent; color: #66ffcc; padding: 0; border: none; }");
    statusLabel->setVisible(false);
    mainLayout->addWidget(statusLabel);

    // ── 5. "Read Sensor" button ───────────────────────────────────────────────
    QPushButton *readBtn = new QPushButton(
        arduinoConnected ? "Read Sensor" : "Plug in Arduino & Read Sensor",
        &dialog);
    readBtn->setStyleSheet(
        "QPushButton { background: #0a1f18; border: 1px solid #00ff9c; border-radius: 10px; "
        "padding: 12px 20px; color: #00ff9c; font-weight: bold; }"
        "QPushButton:hover { background: rgba(0,255,156,0.1); }"
        "QPushButton:disabled { border-color: #1a3d2e; color: #1a3d2e; }");
    mainLayout->addWidget(readBtn);

    // ── 6. Save button ────────────────────────────────────────────────────────
    QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, &dialog);
    QPushButton *saveBtn = btnBox->button(QDialogButtonBox::Save);
    saveBtn->setEnabled(false);
    saveBtn->setStyleSheet(
        "QPushButton { background: #00ff9c; color: #050d0a; border-radius: 8px; padding: 10px 24px; font-weight: bold; border: none; }"
        "QPushButton:hover { background: #33ffcc; }"
        "QPushButton:disabled { background: #0a1f18; color: #1a3d2e; border: 1px solid #1a3d2e; }");
    btnBox->button(QDialogButtonBox::Cancel)->setStyleSheet(
        "QPushButton { background: transparent; color: #ff6666; border: 1px solid #ff6666; border-radius: 8px; padding: 10px 24px; }"
        "QPushButton:hover { background: rgba(255,102,102,0.1); }");
    mainLayout->addWidget(btnBox);

    QObject::connect(btnBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // ── 7. Shared reading state ───────────────────────────────────────────────
    ArduinoSensor::Reading capturedReading;

    // ── 8. Read button logic ──────────────────────────────────────────────────
    QObject::connect(readBtn, &QPushButton::clicked, [&]() {
        m_suppressArduinoAutoSave = true;

        // Try to connect if not already
        if (!m_arduino->isConnected()) {
            const QStringList ports = ArduinoSensor::availablePorts();
            if (ports.isEmpty()) {
                m_suppressArduinoAutoSave = false;
                statusLabel->setVisible(true);
                statusLabel->setText("No serial ports found. Plug in the Arduino and try again.");
                statusLabel->setStyleSheet("QLabel { background: #1a0000; color: #ff6666; padding: 10px 14px; border-radius: 8px; border: none; }");
                return;
            }

            const QString preferredPort = "COM7";
            if (ports.contains(preferredPort, Qt::CaseInsensitive)) {
                if (!m_arduino->openPort(preferredPort)) {
                    m_suppressArduinoAutoSave = false;
                    statusLabel->setVisible(true);
                    statusLabel->setText("Failed to open " + preferredPort + ". Check the connection and try again.");
                    statusLabel->setStyleSheet("QLabel { background: #1a0000; color: #ff6666; padding: 10px 14px; border-radius: 8px; border: none; }");
                    return;
                }
            } else if (ports.size() == 1) {
                if (!m_arduino->openPort(ports.first())) {
                    m_suppressArduinoAutoSave = false;
                    statusLabel->setVisible(true);
                    statusLabel->setText("Failed to open " + ports.first() + ". Check the connection and try again.");
                    statusLabel->setStyleSheet("QLabel { background: #1a0000; color: #ff6666; padding: 10px 14px; border-radius: 8px; border: none; }");
                    return;
                }
            } else {
                onArduinoConnect();
                if (!m_arduino->isConnected()) {
                    m_suppressArduinoAutoSave = false;
                    statusLabel->setVisible(true);
                    statusLabel->setText("No serial port selected. Please choose a port and try again.");
                    statusLabel->setStyleSheet("QLabel { background: #1a0000; color: #ff6666; padding: 10px 14px; border-radius: 8px; border: none; }");
                    return;
                }
            }
        }

        readBtn->setEnabled(false);
        readBtn->setText("Reading sensor...");
        statusLabel->setVisible(true);
        statusLabel->setText("Waiting for sensor reading (up to 12 seconds)...");
        statusLabel->setStyleSheet("QLabel { background: #0a1f18; color: #66ffcc; padding: 10px 14px; border-radius: 8px; border: none; }");

        capturedReading.isValid = false;

        QEventLoop loop;
        QTimer::singleShot(12000, &loop, &QEventLoop::quit);
        const QMetaObject::Connection readConn = QObject::connect(
            m_arduino,
            &ArduinoSensor::readingReady,
            &loop,
            [&](ArduinoSensor::Reading r) {
                capturedReading = r;
                loop.quit();
            });

        m_arduino->requestReading(12000);
        loop.exec();
        QObject::disconnect(readConn);

        if (!capturedReading.isValid) {
            const QString rawLine = m_arduino->lastRawLine().trimmed();
            const QString parseError = m_arduino->lastParseError().trimmed();
            QString diagnostic = "No valid sensor reading received. Check the selected COM port and keep the object in front of the sensor, then try again.";
            statusLabel->setVisible(true);
            if (!parseError.isEmpty()) {
                diagnostic += "\nParse error: " + parseError;
            }
            if (!rawLine.isEmpty()) {
                diagnostic += "\nSerial line: " + rawLine;
            }
            readBtn->setEnabled(true);
            readBtn->setText("Retry — Read Sensor Again");
            statusLabel->setText(diagnostic);
            statusLabel->setStyleSheet("QLabel { background: #1a0a00; color: #ffcc66; padding: 10px 14px; border-radius: 8px; border: none; }");
            return;
        }

        // Update cards
        humCard->setText(QString("Humidity\n%1%").arg(capturedReading.humidity));
        humCard->setStyleSheet(cardStyle + "QLabel { border-color: #00ff9c; color: #00ff9c; font-weight: bold; }");
        distCard->setText(QString("Distance\n%1 cm").arg(capturedReading.distance));
        distCard->setStyleSheet(cardStyle + "QLabel { border-color: #00ff9c; color: #00ff9c; font-weight: bold; }");

        const QString wetDry = capturedReading.isWet ? "WET" : "DRY";
        const QString wetColor = capturedReading.isWet ? "#6bffb8" : "#ffcc66";
        typeCard->setText(QString("Type\n%1").arg(wetDry));
        typeCard->setStyleSheet(QString("QLabel { background: #0a1f18; border: 1px solid %1; border-radius: 10px; "
                                        "padding: 14px; color: %1; font-size: 13px; font-weight: bold; min-width: 110px; }").arg(wetColor));

        // Update status
        const QString desc = capturedReading.isWet
                                 ? "WET waste — classified as Organic. Click Save to update this record."
                                 : "DRY waste — classified as Plastic/Recyclable. Click Save to update this record.";
        statusLabel->setVisible(true);
        statusLabel->setText(desc);
        statusLabel->setStyleSheet(capturedReading.isWet
                                       ? "QLabel { background: #0d3526; color: #6bffb8; padding: 10px 14px; border-radius: 8px; border: none; font-weight: bold; }"
                                       : "QLabel { background: #3a2a00; color: #ffcc66; padding: 10px 14px; border-radius: 8px; border: none; font-weight: bold; }");

        readBtn->setText("Read Sensor Again");
        readBtn->setEnabled(true);
        saveBtn->setEnabled(true);
    });

    // ── 9. Save button logic ──────────────────────────────────────────────────
    QObject::connect(saveBtn, &QPushButton::clicked, [&]() {
        if (!capturedReading.isValid) return;
        dialog.accept();
    });

    if (dialog.exec() != QDialog::Accepted) return;

    // ── 10. Update the selected waste record in Oracle ────────────────────────
    // Load existing waste to preserve all other fields
    Waste target;
    bool found = false;
    for (const Waste &w : all) {
        if (w.id() == selectedId) { target = w; found = true; break; }
    }
    if (!found) {
        QMessageBox::critical(this, "Sensor Details", "Could not find waste record #" + QString::number(selectedId));
        return;
    }

    // Only update humidity, distance, and type from sensor — keep everything else
    target.setHumidityPercent(capturedReading.humidity);
    target.setDistanceCm(capturedReading.distance);
    target.setType(capturedReading.isWet ? "Organic" : "Plastic");

    if (target.update()) {
        onViewWasteClicked();
        qDebug() << "Sensor Details saved: id=" << selectedId
                 << "humidity=" << capturedReading.humidity
                 << "distance=" << capturedReading.distance
                 << "type=" << (capturedReading.isWet ? "Organic" : "Plastic");
        QMessageBox::information(this, "Sensor Details",
                                 QString("Waste #%1 updated!\nHumidity: %2%  |  Distance: %3 cm  |  Type: %4")
                                     .arg(selectedId)
                                     .arg(capturedReading.humidity)
                                     .arg(capturedReading.distance)
                                     .arg(capturedReading.isWet ? "Organic (WET)" : "Plastic (DRY)"));
    } else {
        QMessageBox::critical(this, "Sensor Details", "Failed to update record in Oracle.");
    }
}

void MainWindow::onArduinoConnect()
{
    const QStringList ports = ArduinoSensor::availablePorts();
    if (ports.isEmpty()) {
        QMessageBox::warning(this, "Arduino Sensor",
                             "No serial ports found.\n"
                             "Make sure the Arduino is plugged in.");
        return;
    }

    bool ok = false;
    const QString chosen = QInputDialog::getItem(
        this, "Arduino Sensor", "Select serial port:", ports, 0, false, &ok);
    if (!ok || chosen.isEmpty()) return;

    if (!m_arduino->openPort(chosen)) {
        QMessageBox::critical(this, "Arduino Sensor",
                              "Could not open port " + chosen + ".\n"
                                                                "Check the device is connected and the port is free.");
    }
}

void MainWindow::onArduinoDisconnect()
{
    m_arduino->closePort();
}

void MainWindow::onArduinoConnectionChanged(bool connected)
{
    if (connected) {
        m_arduinoStatus->setText("Arduino: " + m_arduino->currentPort());
        m_arduinoStatus->setStyleSheet("color: #6bffb8; padding: 0 6px;");
        m_arduino->requestReading(8000);
    } else {
        m_arduinoStatus->setText("Arduino: not connected");
        m_arduinoStatus->setStyleSheet("color: #ff6b6b; padding: 0 6px;");
    }
}

>>>>>>> 5be580a (waste X Arduino)
