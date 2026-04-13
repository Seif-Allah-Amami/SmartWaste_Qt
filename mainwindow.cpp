#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "vehicle.h"

#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QFrame>
#include <QGridLayout>
#include <QMap>
#include <QMessageBox>
#include <QPageLayout>
#include <QPageSize>
#include <QPainter>
#include <QPdfWriter>
#include <QProgressBar>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSizePolicy>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QPieSeries>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , vehicleTabWidget(nullptr)
    , vehicleListTab(nullptr)
    , vehicleAddTab(nullptr)
    , addVehicleTitleLabel(nullptr)
    , addVehicleIdEdit(nullptr)
    , addVehiclePlateEdit(nullptr)
    , addVehicleTypeCombo(nullptr)
    , addVehicleModelEdit(nullptr)
    , addVehicleFuelCombo(nullptr)
    , addVehicleStatusCombo(nullptr)
    , addVehicleNextMaintEdit(nullptr)
    , addVehicleEmployeeIdEdit(nullptr)
    , addVehicleSaveBtn(nullptr)
    , addVehicleClearBtn(nullptr)
    , isEditMode(false)
    , editingVehicleId(0)
{
    ui->setupUi(this);
    setupVehicleTabs();
    bindVehicleUi();
    refreshVehiclesTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupVehicleTabs()
{
    if (!ui->mainContentWidget_2 || !ui->mainContentLayout_2) {
        return;
    }

    vehicleTabWidget = new QTabWidget(ui->mainContentWidget_2);
    vehicleTabWidget->setObjectName("vehicleTabWidget");
    vehicleTabWidget->setDocumentMode(true);

    vehicleListTab = new QWidget(vehicleTabWidget);
    vehicleAddTab = new QWidget(vehicleTabWidget);

    QVBoxLayout *listLayout = new QVBoxLayout(vehicleListTab);
    listLayout->setContentsMargins(0, 0, 0, 0);
    listLayout->setSpacing(20);

    const int insertIndex = ui->mainContentLayout_2->indexOf(ui->searchFilterWidget_2);

    ui->mainContentLayout_2->removeWidget(ui->searchFilterWidget_2);
    ui->searchFilterWidget_2->setParent(vehicleListTab);
    listLayout->addWidget(ui->searchFilterWidget_2);

    ui->mainContentLayout_2->removeItem(ui->tableActionsLayout_2);
    QWidget *tableActionsContainer = new QWidget(vehicleListTab);
    tableActionsContainer->setObjectName("tableActionsContainer_2");
    tableActionsContainer->setLayout(ui->tableActionsLayout_2);
    listLayout->addWidget(tableActionsContainer);

    setupAddVehicleForm(vehicleAddTab);

    vehicleTabWidget->addTab(vehicleListTab, "Vehicle List");
    vehicleTabWidget->addTab(vehicleAddTab, "Add Vehicle");

    if (insertIndex >= 0) {
        ui->mainContentLayout_2->insertWidget(insertIndex, vehicleTabWidget);
    } else {
        ui->mainContentLayout_2->addWidget(vehicleTabWidget);
    }
}

void MainWindow::setupAddVehicleForm(QWidget *parent)
{
    QVBoxLayout *rootLayout = new QVBoxLayout(parent);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(20);

    addVehicleTitleLabel = new QLabel("Add Vehicle", parent);
    addVehicleTitleLabel->setObjectName("pageTitle");
    rootLayout->addWidget(addVehicleTitleLabel);

    QWidget *formContainer = new QWidget(parent);
    QFormLayout *formLayout = new QFormLayout(formContainer);
    formLayout->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    formLayout->setFormAlignment(Qt::AlignTop);
    formLayout->setHorizontalSpacing(20);
    formLayout->setVerticalSpacing(12);

    addVehicleIdEdit = new QLineEdit(formContainer);
    addVehicleIdEdit->setPlaceholderText("e.g., 1001");
    addVehicleIdEdit->setMaxLength(10);
    addVehicleIdEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{1,10}$"), addVehicleIdEdit));

    addVehiclePlateEdit = new QLineEdit(formContainer);
    addVehiclePlateEdit->setPlaceholderText("e.g., 123-TN-456");
    addVehiclePlateEdit->setMaxLength(15);
    addVehiclePlateEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9 -]{3,15}$"), addVehiclePlateEdit));

    addVehicleTypeCombo = new QComboBox(formContainer);
    addVehicleTypeCombo->addItems({"Car", "Truck", "Van", "Bus", "Other"});

    addVehicleModelEdit = new QLineEdit(formContainer);
    addVehicleModelEdit->setPlaceholderText("e.g., Hilux");
    addVehicleModelEdit->setMaxLength(30);

    addVehicleFuelCombo = new QComboBox(formContainer);
    addVehicleFuelCombo->addItems({"Gasoline", "Diesel", "Hybrid", "Electric", "Other"});

    addVehicleStatusCombo = new QComboBox(formContainer);
    addVehicleStatusCombo->addItems({"Active", "In Maintenance", "Out of Service"});

    addVehicleNextMaintEdit = new QDateEdit(QDate::currentDate(), formContainer);
    addVehicleNextMaintEdit->setCalendarPopup(true);

    addVehicleEmployeeIdEdit = new QLineEdit(formContainer);
    addVehicleEmployeeIdEdit->setPlaceholderText("e.g., 42");

    formLayout->addRow("Vehicle ID", addVehicleIdEdit);
    formLayout->addRow("Plate Number", addVehiclePlateEdit);
    formLayout->addRow("Type", addVehicleTypeCombo);
    formLayout->addRow("Model", addVehicleModelEdit);
    formLayout->addRow("Fuel Type", addVehicleFuelCombo);
    formLayout->addRow("Status", addVehicleStatusCombo);
    formLayout->addRow("Next Maintenance", addVehicleNextMaintEdit);
    formLayout->addRow("Employee ID", addVehicleEmployeeIdEdit);

    rootLayout->addWidget(formContainer);

    QHBoxLayout *actionsLayout = new QHBoxLayout();
    actionsLayout->addStretch();

    addVehicleClearBtn = new QPushButton("Clear", parent);
    addVehicleSaveBtn = new QPushButton("Save Vehicle", parent);
    addVehicleSaveBtn->setObjectName("primaryBtn");

    actionsLayout->addWidget(addVehicleClearBtn);
    actionsLayout->addWidget(addVehicleSaveBtn);

    rootLayout->addLayout(actionsLayout);
    rootLayout->addStretch();
}

void MainWindow::showVehicleStatsDialog()
{
    const QList<Vehicle> vehicles = Vehicle::readAll();
    const int totalCount = vehicles.size();

    int activeCount = 0;
    int maintenanceCount = 0;
    int outOfServiceCount = 0;
    QMap<QString, int> typeCounts;
    QMap<int, int> yearCounts;

    for (const Vehicle &vehicle : vehicles) {
        const QString status = vehicle.status();
        if (status == "Active") {
            ++activeCount;
        } else if (status == "In Maintenance") {
            ++maintenanceCount;
        } else if (status == "Out of Service") {
            ++outOfServiceCount;
        }

        typeCounts[vehicle.type()] += 1;

        const QDate maintenanceDate = vehicle.nextMaintenance();
        const int year = maintenanceDate.isValid() ? maintenanceDate.year() : QDate::currentDate().year();
        yearCounts[year] += 1;
    }

    const double availabilityPercent = totalCount > 0
                                           ? (100.0 * static_cast<double>(activeCount) / static_cast<double>(totalCount))
                                           : 0.0;

    QDialog dialog(this);
    dialog.setWindowTitle("Vehicle Fleet Statistics");
    dialog.resize(980, 700);
    dialog.setStyleSheet(
        "QDialog { background-color: #03110b; color: #66ffcc; }"
        "QWidget#statCard { background-color: #04170f; border: 2px solid #00cc7a; border-radius: 10px; }"
        "QLabel#statTitle { color: #9fffd9; font-size: 12px; font-weight: 700; }"
        "QLabel#statValue { color: #00ff9c; font-size: 30px; font-weight: 800; }"
        "QFrame#chartPanel { background-color: #04170f; border: 2px solid #00cc7a; border-radius: 10px; }"
        "QLabel#panelTitle { color: #c9ffe9; font-size: 18px; font-weight: 800; }"
        "QLabel#chartTitle { color: #9fffd9; font-size: 16px; font-weight: 700; }"
        "QLabel#availabilityLabel { color: #9fffd9; font-size: 14px; font-weight: 700; }"
        "QLabel#availabilityValue { color: #00ff9c; font-size: 52px; font-weight: 900; }"
        "QProgressBar { border: 2px solid #00cc7a; border-radius: 10px; background-color: #021008; height: 20px; }"
        "QProgressBar::chunk { background-color: #00ff9c; border-radius: 8px; }"
    );

    QVBoxLayout *rootLayout = new QVBoxLayout(&dialog);
    rootLayout->setContentsMargins(14, 14, 14, 14);
    rootLayout->setSpacing(10);

    QLabel *titleLabel = new QLabel("Vehicle Fleet Statistics", &dialog);
    titleLabel->setObjectName("panelTitle");
    rootLayout->addWidget(titleLabel);

    auto createCard = [&dialog](const QString &title, const QString &value) {
        QWidget *card = new QWidget(&dialog);
        card->setObjectName("statCard");

        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setContentsMargins(16, 14, 16, 14);
        cardLayout->setSpacing(6);

        QLabel *titleLabel = new QLabel(title, card);
        titleLabel->setObjectName("statTitle");
        titleLabel->setAlignment(Qt::AlignCenter);

        QLabel *valueLabel = new QLabel(value, card);
        valueLabel->setObjectName("statValue");
        valueLabel->setAlignment(Qt::AlignCenter);

        cardLayout->addWidget(titleLabel);
        cardLayout->addWidget(valueLabel);
        return card;
    };

    QHBoxLayout *cardsLayout = new QHBoxLayout();
    cardsLayout->setSpacing(10);
    cardsLayout->addWidget(createCard("TOTAL VEHICLES", QString::number(totalCount)));
    cardsLayout->addWidget(createCard("ACTIVE", QString::number(activeCount)));
    cardsLayout->addWidget(createCard("MAINTENANCE", QString::number(maintenanceCount)));
    cardsLayout->addWidget(createCard("OUT OF SERVICE", QString::number(outOfServiceCount)));
    rootLayout->addLayout(cardsLayout);

    auto styleChart = [](QChart *chart) {
        chart->setBackgroundVisible(true);
        chart->setBackgroundBrush(QColor("#04170f"));
        chart->setPlotAreaBackgroundVisible(true);
        chart->setPlotAreaBackgroundBrush(QColor("#03140d"));
        chart->setMargins(QMargins(8, 8, 8, 8));
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->legend()->setLabelColor(QColor("#9fffd9"));
        chart->setTitleBrush(QColor("#9fffd9"));
        chart->setTitleFont(QFont("Segoe UI", 10, QFont::Bold));
    };

    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(10);

    QFrame *statusPanel = new QFrame(&dialog);
    statusPanel->setObjectName("chartPanel");
    QVBoxLayout *statusPanelLayout = new QVBoxLayout(statusPanel);
    statusPanelLayout->setContentsMargins(10, 10, 10, 10);
    QLabel *statusTitle = new QLabel("Status Breakdown", statusPanel);
    statusTitle->setObjectName("chartTitle");
    statusPanelLayout->addWidget(statusTitle);

    QPieSeries *statusSeries = new QPieSeries(statusPanel);
    statusSeries->append(QString("Active (%1)").arg(activeCount), activeCount);
    statusSeries->append(QString("Out of Service (%1)").arg(outOfServiceCount), outOfServiceCount);
    statusSeries->append(QString("Under Maintenance (%1)").arg(maintenanceCount), maintenanceCount);

    const QList<QColor> statusColors = {QColor("#27d9c3"), QColor("#1f6fb0"), QColor("#2c95ff")};
    const auto statusSlices = statusSeries->slices();
    for (int index = 0; index < statusSlices.size() && index < statusColors.size(); ++index) {
        statusSlices[index]->setBrush(statusColors[index]);
        statusSlices[index]->setLabelVisible(true);
        statusSlices[index]->setPen(QPen(QColor("#05251a"), 1));
    }

    QChart *statusChart = new QChart();
    statusChart->addSeries(statusSeries);
    statusChart->legend()->setVisible(true);
    styleChart(statusChart);

    QChartView *statusView = new QChartView(statusChart, statusPanel);
    statusView->setRenderHint(QPainter::Antialiasing);
    statusView->setStyleSheet("background: transparent; border: none;");
    statusPanelLayout->addWidget(statusView);

    QFrame *typePanel = new QFrame(&dialog);
    typePanel->setObjectName("chartPanel");
    QVBoxLayout *typePanelLayout = new QVBoxLayout(typePanel);
    typePanelLayout->setContentsMargins(10, 10, 10, 10);
    QLabel *typeTitle = new QLabel("Vehicles by Type", typePanel);
    typeTitle->setObjectName("chartTitle");
    typePanelLayout->addWidget(typeTitle);

    QBarSet *typeSet = new QBarSet("Count", typePanel);
    typeSet->setColor(QColor("#27d9c3"));
    QStringList typeLabels;
    int typeMax = 0;
    for (auto it = typeCounts.constBegin(); it != typeCounts.constEnd(); ++it) {
        typeLabels << it.key();
        *typeSet << it.value();
        typeMax = qMax(typeMax, it.value());
    }
    if (typeLabels.isEmpty()) {
        typeLabels << "No Data";
        *typeSet << 0;
    }

    QBarSeries *typeSeries = new QBarSeries(typePanel);
    typeSeries->append(typeSet);

    QChart *typeChart = new QChart();
    typeChart->addSeries(typeSeries);
    typeChart->legend()->setVisible(false);
    styleChart(typeChart);

    QBarCategoryAxis *typeAxisX = new QBarCategoryAxis(typeChart);
    typeAxisX->append(typeLabels);
    typeAxisX->setLabelsColor(QColor("#9fffd9"));
    typeAxisX->setGridLineColor(QColor("#00cc7a"));
    typeChart->addAxis(typeAxisX, Qt::AlignBottom);
    typeSeries->attachAxis(typeAxisX);

    QValueAxis *typeAxisY = new QValueAxis(typeChart);
    typeAxisY->setMin(0);
    typeAxisY->setMax(qMax(1, typeMax + 1));
    typeAxisY->setLabelFormat("%d");
    typeAxisY->setLabelsColor(QColor("#9fffd9"));
    typeAxisY->setGridLineColor(QColor("#00cc7a"));
    typeChart->addAxis(typeAxisY, Qt::AlignLeft);
    typeSeries->attachAxis(typeAxisY);

    QChartView *typeView = new QChartView(typeChart, typePanel);
    typeView->setRenderHint(QPainter::Antialiasing);
    typeView->setStyleSheet("background: transparent; border: none;");
    typePanelLayout->addWidget(typeView);

    QFrame *yearPanel = new QFrame(&dialog);
    yearPanel->setObjectName("chartPanel");
    QVBoxLayout *yearPanelLayout = new QVBoxLayout(yearPanel);
    yearPanelLayout->setContentsMargins(10, 10, 10, 10);
    QLabel *yearTitle = new QLabel("Vehicles by Year", yearPanel);
    yearTitle->setObjectName("chartTitle");
    yearPanelLayout->addWidget(yearTitle);

    QBarSet *yearSet = new QBarSet("Count", yearPanel);
    yearSet->setColor(QColor("#2069a6"));
    QStringList yearLabels;
    int yearMax = 0;
    for (auto it = yearCounts.constBegin(); it != yearCounts.constEnd(); ++it) {
        yearLabels << QString::number(it.key());
        *yearSet << it.value();
        yearMax = qMax(yearMax, it.value());
    }
    if (yearLabels.isEmpty()) {
        yearLabels << QString::number(QDate::currentDate().year());
        *yearSet << 0;
    }

    QBarSeries *yearSeries = new QBarSeries(yearPanel);
    yearSeries->append(yearSet);

    QChart *yearChart = new QChart();
    yearChart->addSeries(yearSeries);
    yearChart->legend()->setVisible(false);
    styleChart(yearChart);

    QBarCategoryAxis *yearAxisX = new QBarCategoryAxis(yearChart);
    yearAxisX->append(yearLabels);
    yearAxisX->setLabelsColor(QColor("#9fffd9"));
    yearAxisX->setGridLineColor(QColor("#00cc7a"));
    yearChart->addAxis(yearAxisX, Qt::AlignBottom);
    yearSeries->attachAxis(yearAxisX);

    QValueAxis *yearAxisY = new QValueAxis(yearChart);
    yearAxisY->setMin(0);
    yearAxisY->setMax(qMax(1, yearMax + 1));
    yearAxisY->setLabelFormat("%d");
    yearAxisY->setLabelsColor(QColor("#9fffd9"));
    yearAxisY->setGridLineColor(QColor("#00cc7a"));
    yearChart->addAxis(yearAxisY, Qt::AlignLeft);
    yearSeries->attachAxis(yearAxisY);

    QChartView *yearView = new QChartView(yearChart, yearPanel);
    yearView->setRenderHint(QPainter::Antialiasing);
    yearView->setStyleSheet("background: transparent; border: none;");
    yearPanelLayout->addWidget(yearView);

    QFrame *availabilityPanel = new QFrame(&dialog);
    availabilityPanel->setObjectName("chartPanel");
    QVBoxLayout *availabilityLayout = new QVBoxLayout(availabilityPanel);
    availabilityLayout->setContentsMargins(12, 12, 12, 12);
    availabilityLayout->addStretch();

    QLabel *availabilityTitle = new QLabel("Fleet Availability Rate", availabilityPanel);
    availabilityTitle->setObjectName("availabilityLabel");
    availabilityTitle->setAlignment(Qt::AlignCenter);
    availabilityLayout->addWidget(availabilityTitle);

    QLabel *availabilityValue = new QLabel(QString("%1%").arg(qRound(availabilityPercent)), availabilityPanel);
    availabilityValue->setObjectName("availabilityValue");
    availabilityValue->setAlignment(Qt::AlignCenter);
    availabilityLayout->addWidget(availabilityValue);

    QProgressBar *availabilityBar = new QProgressBar(availabilityPanel);
    availabilityBar->setRange(0, 100);
    availabilityBar->setValue(qRound(availabilityPercent));
    availabilityBar->setTextVisible(false);
    availabilityLayout->addWidget(availabilityBar);
    availabilityLayout->addStretch();

    grid->addWidget(statusPanel, 0, 0);
    grid->addWidget(typePanel, 0, 1);
    grid->addWidget(yearPanel, 1, 0);
    grid->addWidget(availabilityPanel, 1, 1);
    rootLayout->addLayout(grid, 1);

    QPushButton *closeButton = new QPushButton("Close", &dialog);
    closeButton->setObjectName("primaryBtn");
    closeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    rootLayout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    dialog.exec();
}

void MainWindow::bindVehicleUi()
{
    if (ui->btnAddVehicle && vehicleTabWidget && vehicleAddTab) {
        connect(ui->btnAddVehicle, &QPushButton::clicked, this, [this]() {
            vehicleTabWidget->setCurrentWidget(vehicleAddTab);
        });
    }

    if (ui->btnViewVehicles && vehicleTabWidget && vehicleListTab) {
        connect(ui->btnViewVehicles, &QPushButton::clicked, this, [this]() {
            vehicleTabWidget->setCurrentWidget(vehicleListTab);
            refreshVehiclesTable();
        });
    }

    if (addVehicleClearBtn) {
        connect(addVehicleClearBtn, &QPushButton::clicked, this, &MainWindow::clearAddVehicleForm);
    }

    if (ui->btnEditVehicle) {
        connect(ui->btnEditVehicle, &QPushButton::clicked, this, [this]() {
            const int row = ui->vehiclesTable ? ui->vehiclesTable->currentRow() : -1;
            if (row < 0) {
                QMessageBox::information(this, "Edit Vehicle", "Select a vehicle row first.");
                return;
            }

            populateFormFromRow(row);
            setEditMode(true);
            vehicleTabWidget->setCurrentWidget(vehicleAddTab);
        });
    }

    if (ui->btnDeleteVehicle) {
        connect(ui->btnDeleteVehicle, &QPushButton::clicked, this, [this]() {
            const int id = selectedVehicleId();
            if (id <= 0) {
                QMessageBox::information(this, "Delete Vehicle", "Select a vehicle row first.");
                return;
            }

            const auto choice = QMessageBox::question(this,
                                                      "Delete Vehicle",
                                                      "Delete the selected vehicle?",
                                                      QMessageBox::Yes | QMessageBox::No);
            if (choice != QMessageBox::Yes) {
                return;
            }

            if (!Vehicle::remove(id)) {
                const QString details = Vehicle::lastError().isEmpty()
                                            ? "Delete failed. Check database connection."
                                            : Vehicle::lastError();
                QMessageBox::warning(this, "Delete failed", details);
                return;
            }

            refreshVehiclesTable();
        });
    }

    if (ui->sortComboBox_2) {
        connect(ui->sortComboBox_2, &QComboBox::currentIndexChanged, this, [this]() {
            applySortFromCombo();
        });
    }

    if (ui->searchBox_2) {
        connect(ui->searchBox_2, &QLineEdit::textChanged, this, [this]() {
            applySearchFilter();
        });
    }

    if (addVehicleSaveBtn) {
        connect(addVehicleSaveBtn, &QPushButton::clicked, this, [this]() {
            const QString plate = addVehiclePlateEdit->text().trimmed();
            const QString model = addVehicleModelEdit->text().trimmed();
            bool okId = false;
            const int idVehicle = addVehicleIdEdit->text().toInt(&okId);

            if (!okId) {
                QMessageBox::warning(this, "Validation", "Vehicle ID must be a number.");
                return;
            }

            if (plate.isEmpty() || model.isEmpty()) {
                QMessageBox::warning(this, "Validation", "Plate number and model are required.");
                return;
            }

            if (!addVehiclePlateEdit->hasAcceptableInput()) {
                QMessageBox::warning(this,
                                     "Validation",
                                     "Plate number must be 3-15 characters (letters, numbers, dash, space).");
                return;
            }

            if (model.size() < 2) {
                QMessageBox::warning(this, "Validation", "Model must be at least 2 characters.");
                return;
            }

            int employeeId = 0;
            const QString employeeText = addVehicleEmployeeIdEdit->text().trimmed();
            if (!employeeText.isEmpty()) {
                bool okEmployee = false;
                employeeId = employeeText.toInt(&okEmployee);
                if (!okEmployee) {
                    QMessageBox::warning(this, "Validation", "Employee ID must be a number.");
                    return;
                }
            }

            const int effectiveId = isEditMode ? editingVehicleId : idVehicle;
            Vehicle vehicle(effectiveId,
                            plate,
                            addVehicleTypeCombo->currentText(),
                            model,
                            addVehicleFuelCombo->currentText(),
                            addVehicleStatusCombo->currentText(),
                            addVehicleNextMaintEdit->date(),
                            employeeId);

            const bool saved = isEditMode ? vehicle.update() : vehicle.create();
            if (!saved) {
                const QString details = Vehicle::lastError().isEmpty()
                                            ? "Save failed. Check database connection."
                                            : Vehicle::lastError();
                QMessageBox::warning(this, "Save failed", details);
                return;
            }

            const QString successMsg = isEditMode ? "Vehicle updated successfully." : "Vehicle saved successfully.";
            QMessageBox::information(this, "Saved", successMsg);

            clearAddVehicleForm();
            refreshVehiclesTable();
            vehicleTabWidget->setCurrentWidget(vehicleListTab);
        });
    }

    if (ui->btnExportPDF_2) {
        connect(ui->btnExportPDF_2, &QPushButton::clicked, this, &MainWindow::exportVehiclesToPdf);
    }

    if (ui->statistic_btn) {
        connect(ui->statistic_btn, &QPushButton::clicked, this, [this]() {
            showVehicleStatsDialog();
        });
    }
}

void MainWindow::refreshVehiclesTable()
{
    if (!ui->vehiclesTable) {
        return;
    }

    ui->vehiclesTable->setColumnCount(8);
    ui->vehiclesTable->setHorizontalHeaderLabels({
        "ID",
        "Num Plate",
        "Type",
        "Model",
        "Fuel Type",
        "Status",
        "Next Maintenance",
        "Employee ID"
    });

    ui->vehiclesTable->setRowCount(0);
    const QList<Vehicle> vehicles = Vehicle::readAll();

    for (int i = 0; i < vehicles.size(); ++i) {
        const Vehicle &vehicle = vehicles.at(i);
        ui->vehiclesTable->insertRow(i);

        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(vehicle.idVehicle()));
        idItem->setData(Qt::EditRole, vehicle.idVehicle());
        ui->vehiclesTable->setItem(i, 0, idItem);
        ui->vehiclesTable->setItem(i, 1, new QTableWidgetItem(vehicle.plateNum()));
        ui->vehiclesTable->setItem(i, 2, new QTableWidgetItem(vehicle.type()));
        ui->vehiclesTable->setItem(i, 3, new QTableWidgetItem(vehicle.model()));
        ui->vehiclesTable->setItem(i, 4, new QTableWidgetItem(vehicle.fuelType()));
        ui->vehiclesTable->setItem(i, 5, new QTableWidgetItem(vehicle.status()));

        const QDate nextMaintDate = vehicle.nextMaintenance();
        const QString nextMaint = nextMaintDate.isValid()
                                      ? nextMaintDate.toString("yyyy-MM-dd")
                                      : "";
        QTableWidgetItem *maintItem = new QTableWidgetItem(nextMaint);
        maintItem->setData(Qt::EditRole, nextMaintDate);
        ui->vehiclesTable->setItem(i, 6, maintItem);

        const QString employeeId = vehicle.employeeId() > 0
                                       ? QString::number(vehicle.employeeId())
                                       : "";
        ui->vehiclesTable->setItem(i, 7, new QTableWidgetItem(employeeId));
    }

    ui->vehiclesTable->setSortingEnabled(true);
    applySortFromCombo();
    applySearchFilter();
}

void MainWindow::setEditMode(bool enabled)
{
    isEditMode = enabled;

    if (addVehicleTitleLabel) {
        addVehicleTitleLabel->setText(enabled ? "Edit Vehicle" : "Add Vehicle");
    }

    if (addVehicleSaveBtn) {
        addVehicleSaveBtn->setText(enabled ? "Update Vehicle" : "Save Vehicle");
    }

    if (addVehicleIdEdit) {
        addVehicleIdEdit->setEnabled(!enabled);
    }
}

void MainWindow::populateFormFromRow(int row)
{
    if (!ui->vehiclesTable || row < 0) {
        return;
    }

    const QTableWidgetItem *idItem = ui->vehiclesTable->item(row, 0);
    const QTableWidgetItem *plateItem = ui->vehiclesTable->item(row, 1);
    const QTableWidgetItem *typeItem = ui->vehiclesTable->item(row, 2);
    const QTableWidgetItem *modelItem = ui->vehiclesTable->item(row, 3);
    const QTableWidgetItem *fuelItem = ui->vehiclesTable->item(row, 4);
    const QTableWidgetItem *statusItem = ui->vehiclesTable->item(row, 5);
    const QTableWidgetItem *maintItem = ui->vehiclesTable->item(row, 6);
    const QTableWidgetItem *empItem = ui->vehiclesTable->item(row, 7);

    const int id = idItem ? idItem->text().toInt() : 0;
    editingVehicleId = id;

    if (addVehicleIdEdit) {
        addVehicleIdEdit->setText(idItem ? idItem->text() : "");
    }
    if (addVehiclePlateEdit) {
        addVehiclePlateEdit->setText(plateItem ? plateItem->text() : "");
    }
    if (addVehicleTypeCombo && typeItem) {
        const int index = addVehicleTypeCombo->findText(typeItem->text());
        addVehicleTypeCombo->setCurrentIndex(index >= 0 ? index : 0);
    }
    if (addVehicleModelEdit) {
        addVehicleModelEdit->setText(modelItem ? modelItem->text() : "");
    }
    if (addVehicleFuelCombo && fuelItem) {
        const int index = addVehicleFuelCombo->findText(fuelItem->text());
        addVehicleFuelCombo->setCurrentIndex(index >= 0 ? index : 0);
    }
    if (addVehicleStatusCombo && statusItem) {
        const int index = addVehicleStatusCombo->findText(statusItem->text());
        addVehicleStatusCombo->setCurrentIndex(index >= 0 ? index : 0);
    }
    if (addVehicleNextMaintEdit) {
        const QDate date = maintItem ? QDate::fromString(maintItem->text(), "yyyy-MM-dd") : QDate();
        addVehicleNextMaintEdit->setDate(date.isValid() ? date : QDate::currentDate());
    }
    if (addVehicleEmployeeIdEdit) {
        addVehicleEmployeeIdEdit->setText(empItem ? empItem->text() : "");
    }
}

int MainWindow::selectedVehicleId() const
{
    if (!ui->vehiclesTable) {
        return 0;
    }

    const int row = ui->vehiclesTable->currentRow();
    if (row < 0) {
        return 0;
    }

    const QTableWidgetItem *idItem = ui->vehiclesTable->item(row, 0);
    if (!idItem) {
        return 0;
    }

    return idItem->text().toInt();
}

void MainWindow::applySortFromCombo()
{
    if (!ui->vehiclesTable || !ui->sortComboBox_2) {
        return;
    }

    const int index = ui->sortComboBox_2->currentIndex();
    int column = 0;
    switch (index) {
    case 0:
        column = 0;
        break;
    case 1:
        column = 3;
        break;
    case 2:
        column = 2;
        break;
    case 3:
        column = 6;
        break;
    default:
        column = 0;
        break;
    }

    ui->vehiclesTable->sortItems(column, Qt::AscendingOrder);
}

void MainWindow::applySearchFilter()
{
    if (!ui->vehiclesTable || !ui->searchBox_2) {
        return;
    }

    const QString searchText = ui->searchBox_2->text().trimmed();
    for (int row = 0; row < ui->vehiclesTable->rowCount(); ++row) {
        const QTableWidgetItem *idItem = ui->vehiclesTable->item(row, 0);
        const QTableWidgetItem *plateItem = ui->vehiclesTable->item(row, 1);
        const QTableWidgetItem *modelItem = ui->vehiclesTable->item(row, 3);

        const QString idText = idItem ? idItem->text() : "";
        const QString plateText = plateItem ? plateItem->text() : "";
        const QString modelText = modelItem ? modelItem->text() : "";

        const bool matches = searchText.isEmpty()
                             || idText.contains(searchText, Qt::CaseInsensitive)
                             || plateText.contains(searchText, Qt::CaseInsensitive)
                             || modelText.contains(searchText, Qt::CaseInsensitive);

        ui->vehiclesTable->setRowHidden(row, !matches);
    }
}

void MainWindow::clearAddVehicleForm()
{
    setEditMode(false);
    editingVehicleId = 0;

    if (addVehicleIdEdit) {
        addVehicleIdEdit->clear();
    }
    if (addVehiclePlateEdit) {
        addVehiclePlateEdit->clear();
    }
    if (addVehicleTypeCombo) {
        addVehicleTypeCombo->setCurrentIndex(0);
    }
    if (addVehicleModelEdit) {
        addVehicleModelEdit->clear();
    }
    if (addVehicleFuelCombo) {
        addVehicleFuelCombo->setCurrentIndex(0);
    }
    if (addVehicleStatusCombo) {
        addVehicleStatusCombo->setCurrentIndex(0);
    }
    if (addVehicleNextMaintEdit) {
        addVehicleNextMaintEdit->setDate(QDate::currentDate());
    }
    if (addVehicleEmployeeIdEdit) {
        addVehicleEmployeeIdEdit->clear();
    }
}

void MainWindow::exportVehiclesToPdf()
{
    if (!ui->vehiclesTable) {
        return;
    }

    if (ui->vehiclesTable->rowCount() == 0) {
        QMessageBox::information(this, "Export PDF", "There is no data to export.");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Export PDF",
                                                    QDir::homePath() + "/vehicles.pdf",
                                                    "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }

    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf";
    }

    QPdfWriter writer(filePath);
    writer.setResolution(300);
    writer.setPageLayout(QPageLayout(QPageSize(QPageSize::A4),
                                     QPageLayout::Portrait,
                                     QMarginsF(18, 18, 18, 18)));

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Export PDF", "Unable to create the PDF file.");
        return;
    }

    QTableWidget *table = ui->vehiclesTable;

    const QRect pageRect = writer.pageLayout().paintRectPixels(writer.resolution());
    const int pageLeft = pageRect.left();
    const int pageTop = pageRect.top();
    const int pageWidth = pageRect.width();
    const int pageHeight = pageRect.height();

    const QVector<int> sourceColumns = {0, 1, 2, 5, 3, 6};
    const QStringList exportHeaders = {
        "ID",
        "Plate Number",
        "Type",
        "Status",
        "Model",
        "Next Maintenance"
    };
    const QVector<qreal> widthWeights = {0.8, 2.0, 1.4, 1.8, 1.2, 1.8};

    int maxRowsPerPage = 0;
    const int titleHeight = 54;
    const int tableHeaderHeight = 44;
    const int rowHeight = 36;
    const int bottomPadding = 28;

    const int tableWidth = static_cast<int>(pageWidth * 0.72);
    const int tableLeft = pageLeft + (pageWidth - tableWidth) / 2;
    const int titleTop = pageTop + 8;
    const int tableTop = titleTop + titleHeight + 14;

    maxRowsPerPage = (pageHeight - (tableTop - pageTop) - tableHeaderHeight - bottomPadding) / rowHeight;
    if (maxRowsPerPage <= 0) {
        QMessageBox::warning(this, "Export PDF", "Page layout is too small for export.");
        return;
    }

    const int totalRows = table->rowCount();
    const int pageCount = (totalRows + maxRowsPerPage - 1) / maxRowsPerPage;

    const qreal totalWeight = std::accumulate(widthWeights.cbegin(), widthWeights.cend(), 0.0);
    QVector<int> columnWidths;
    columnWidths.reserve(widthWeights.size());

    int allocatedWidth = 0;
    for (int i = 0; i < widthWeights.size(); ++i) {
        int width = static_cast<int>((widthWeights.at(i) / totalWeight) * tableWidth);
        if (i == widthWeights.size() - 1) {
            width = tableWidth - allocatedWidth;
        }
        columnWidths.append(width);
        allocatedWidth += width;
    }

    const QColor headerColor(51, 230, 153);
    const QColor headerTextColor(0, 0, 0);
    const QColor cellColor(255, 255, 255);
    const QColor borderColor(40, 40, 40);

    for (int page = 0; page < pageCount; ++page) {
        if (page > 0) {
            writer.newPage();
        }

        painter.fillRect(pageRect, Qt::white);

        QFont titleFont = painter.font();
        titleFont.setBold(true);
        titleFont.setPointSize(16);
        painter.setFont(titleFont);
        painter.setPen(Qt::black);
        painter.drawText(QRect(tableLeft, titleTop, tableWidth, titleHeight),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         "Vehicle Management Report");

        QFont headerFont = painter.font();
        headerFont.setBold(true);
        headerFont.setPointSize(10);
        painter.setFont(headerFont);

        int x = tableLeft;
        for (int col = 0; col < exportHeaders.size(); ++col) {
            const QRect cellRect(x, tableTop, columnWidths.at(col), tableHeaderHeight);
            painter.fillRect(cellRect, headerColor);
            painter.setPen(borderColor);
            painter.drawRect(cellRect);
            painter.setPen(headerTextColor);
            painter.drawText(cellRect.adjusted(8, 0, -8, 0), Qt::AlignLeft | Qt::AlignVCenter, exportHeaders.at(col));
            x += columnWidths.at(col);
        }

        QFont bodyFont = painter.font();
        bodyFont.setBold(false);
        bodyFont.setPointSize(9);
        painter.setFont(bodyFont);

        const int startRow = page * maxRowsPerPage;
        const int endRow = qMin(startRow + maxRowsPerPage, totalRows);

        for (int row = startRow; row < endRow; ++row) {
            const int y = tableTop + tableHeaderHeight + ((row - startRow) * rowHeight);
            int cellX = tableLeft;

            for (int col = 0; col < sourceColumns.size(); ++col) {
                const QRect cellRect(cellX, y, columnWidths.at(col), rowHeight);
                painter.fillRect(cellRect, cellColor);
                painter.setPen(borderColor);
                painter.drawRect(cellRect);

                const int sourceCol = sourceColumns.at(col);
                const QTableWidgetItem *item = table->item(row, sourceCol);
                const QString text = item ? item->text() : "";

                painter.setPen(Qt::black);
                painter.drawText(cellRect.adjusted(8, 0, -8, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
                cellX += columnWidths.at(col);
            }
        }
    }

    painter.end();
    QMessageBox::information(this, "Export PDF", "PDF exported successfully.");
}
