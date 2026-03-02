#include "mainwindow.h"
#include "ui_mainwindow.h"

<<<<<<< HEAD
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
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QMap>
#include <QHBoxLayout>
#include <QFrame>
#include <QGuiApplication>
#include <QScreen>

#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QValueAxis>

#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_databaseReady(false)
    , m_searchHintLabel(nullptr)
=======
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
>>>>>>> origin/waste
{
    ui->setupUi(this);

    // Start on login page
    ui->stackedwidget->setCurrentIndex(0);

    // Connect all navigation buttons
    setupConnections();
<<<<<<< HEAD

    setupWasteTable();
    m_databaseReady = initializeDatabase() && ensureWasteTable();
    onViewWasteClicked();
=======
>>>>>>> origin/waste
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
    connect(ui->btnMenuEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnMenuCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
    connect(ui->btnMenuWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);

    // Employee Page Sidebar Navigation
    connect(ui->btnEmpDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnEmpLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
<<<<<<< HEAD
    connect(ui->btnEmpEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->btnEmpCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);

=======
    connect(ui->btnEmpCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
>>>>>>> origin/waste
    // Waste Management Sidebar Navigation
    connect(ui->btnDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
<<<<<<< HEAD
    connect(ui->btnWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
    connect(ui->btnViewWaste, &QPushButton::clicked, this, &MainWindow::onViewWasteClicked);
    connect(ui->btnAddWaste, &QPushButton::clicked, this, &MainWindow::onAddWasteClicked);
    connect(ui->btnWasteStats, &QPushButton::clicked, this, &MainWindow::onWasteStatsClicked);
    connect(ui->btnEditWaste, &QPushButton::clicked, this, &MainWindow::onEditWasteClicked);
    connect(ui->btnDeleteWaste, &QPushButton::clicked, this, &MainWindow::onDeleteWasteClicked);
    connect(ui->btnExportPDF, &QPushButton::clicked, this, &MainWindow::onExportWastePdfClicked);
    connect(ui->btnClearSelection, &QPushButton::clicked, this, &MainWindow::onClearWasteClicked);
    connect(ui->btnClearSelection, &QPushButton::clicked, this, &MainWindow::on_btnClearSelection_clicked);
    connect(ui->btnEmpClear, &QPushButton::clicked, this, &MainWindow::on_btnEmpClear_clicked);
    connect(ui->searchBox, &QLineEdit::textChanged, this, &MainWindow::onWasteSearchChanged);
    connect(ui->sortComboBox,
            qOverload<int>(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::onWasteSortChanged);

    ui->sortComboBox->setItemData(0, "date_desc");
    ui->sortComboBox->setItemData(1, "type_asc");
    ui->sortComboBox->setItemData(2, "location_asc");
    ui->sortComboBox->setItemData(3, "status_asc");

    if (ui->sortComboBox->findText("Sort: ID") < 0) {
        ui->sortComboBox->addItem("Sort: ID");
    }
    const int sortIdIndex = ui->sortComboBox->findText("Sort: ID");
    if (sortIdIndex >= 0) {
        ui->sortComboBox->setItemData(sortIdIndex, "id_asc");
    }

    ui->searchBox->setMaxLength(10);
    ui->searchBox->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9-]{0,10}$"), this));

    connect(ui->searchBox, &QLineEdit::inputRejected, this, [this]() {
        if (!m_searchHintLabel) {
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

        m_searchHintLabel->setVisible(true);
        if (ui->searchBox->text().length() >= ui->searchBox->maxLength()) {
            m_searchHintLabel->setText("Maximum 10 characters reached.");
        } else if (sortMode == "id_asc") {
            m_searchHintLabel->setText("Invalid character. ID search accepts numbers only.");
        } else if (sortMode == "date_desc") {
            m_searchHintLabel->setText("Invalid character. Date search accepts digits and '-'.");
        } else {
            m_searchHintLabel->setText("Invalid character. This search accepts letters and spaces only.");
        }
        m_searchHintLabel->setStyleSheet("QLabel { color: #ff6666; font-size: 11px; }");
    });

    m_searchHintLabel = new QLabel(ui->searchFilterWidget);
    m_searchHintLabel->setText("Search hint: letters/numbers only, max 10 chars.");
    m_searchHintLabel->setStyleSheet("QLabel { color: #8feecf; font-size: 11px; }");
    m_searchHintLabel->setVisible(false);
    ui->searchFilterLayout->insertWidget(2, m_searchHintLabel);
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
    
    if (query.next()) {
        qDebug() << "WASTE table exists in Oracle";
        return true;
    } else {
        qDebug() << "WASTE table not found. Please ensure it's created in Oracle.";
        return false;  // Table must be created in SQL Developer, not here
    }
}

void MainWindow::setupWasteTable()
{
    ui->wasteTable->setColumnCount(8);
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

    if (forEdit) {
        if (!selectedWasteId(wasteId)) {
            QMessageBox::warning(this, "Edit waste", "Select a waste record row first.");
            return false;
        }

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
    QLineEdit *locationEdit = new QLineEdit(defaultLocation, &dialog);
    QComboBox *statusCombo = new QComboBox(&dialog);

    const QRegularExpression lettersRegex("^[A-Za-z ]{0,10}$");
    auto *lettersValidator = new QRegularExpressionValidator(lettersRegex, &dialog);

    locationEdit->setMaxLength(10);
    locationEdit->setValidator(lettersValidator);

    const QStringList typeChoices = {"Organic", "Plastic", "Metal", "Glass"};
    typeCombo->addItem("-- Select Type --");
    typeCombo->addItems(typeChoices);
    typeCombo->setCurrentIndex(0);

    const QStringList categoryChoices = {"Household", "Industrial", "Medical", "Electronic"};
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
    }

    formLayout->addRow("Type:", makeFieldWithHint(typeCombo, "Choose 1 of 4 options."));
    formLayout->addRow("Category:", makeFieldWithHint(categoryCombo, "Choose 1 of 4 options."));
    formLayout->addRow("Quantity:", makeFieldWithHint(quantitySpin, "Numbers only."));
    formLayout->addRow("Weight (kg):", makeFieldWithHint(weightSpin, "Decimal number, up to 2 digits after decimal."));
    formLayout->addRow("Collection Date:", makeFieldWithHint(dateEdit, "Pick a valid date."));

    QWidget *locationContainer = new QWidget(&dialog);
    QVBoxLayout *locationLayout = new QVBoxLayout(locationContainer);
    locationLayout->setContentsMargins(0, 0, 0, 0);
    locationLayout->setSpacing(2);
    locationLayout->addWidget(locationEdit);
    QLabel *locationHint = new QLabel("Location hint: letters/spaces only, max 10 characters.", locationContainer);
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
            locationHint->setText("Maximum 10 characters reached.");
            locationHint->setStyleSheet("QLabel { color: #ff6666; font-size: 10px; }");
            return;
        }

        locationHint->setVisible(false);
    });

    QObject::connect(locationEdit, &QLineEdit::inputRejected, [locationHint, locationEdit]() {
        locationHint->setVisible(true);
        if (locationEdit->text().length() >= locationEdit->maxLength()) {
            locationHint->setText("Maximum 10 characters reached.");
        } else {
            locationHint->setText("Invalid character not allowed. Use letters and spaces only.");
        }
        locationHint->setStyleSheet("QLabel { color: #ff6666; font-size: 10px; }");
    });

    formLayout->addRow("Location:", locationContainer);
    formLayout->addRow("Status:", makeFieldWithHint(statusCombo, "Choose a valid status."));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    formLayout->addRow(buttonBox);

    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    auto updateOkEnabled = [okButton, typeCombo, categoryCombo, statusCombo, locationEdit]() {
        const bool valid = typeCombo->currentIndex() > 0
                           && categoryCombo->currentIndex() > 0
                           && statusCombo->currentIndex() > 0
                           && !locationEdit->text().trimmed().isEmpty();
        okButton->setEnabled(valid);
    };

    updateOkEnabled();
    QObject::connect(typeCombo, qOverload<int>(&QComboBox::currentIndexChanged), &dialog, [updateOkEnabled](int) { updateOkEnabled(); });
    QObject::connect(categoryCombo, qOverload<int>(&QComboBox::currentIndexChanged), &dialog, [updateOkEnabled](int) { updateOkEnabled(); });
    QObject::connect(statusCombo, qOverload<int>(&QComboBox::currentIndexChanged), &dialog, [updateOkEnabled](int) { updateOkEnabled(); });
    QObject::connect(locationEdit, &QLineEdit::textChanged, &dialog, [updateOkEnabled](const QString &) { updateOkEnabled(); });

    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, [&dialog, typeCombo, categoryCombo, statusCombo, locationEdit]() {
        const QString location = locationEdit->text().trimmed();

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
    const QString location = locationEdit->text().trimmed();
    const QString status = statusCombo->currentText();

    waste.setId(wasteId);
    waste.setType(type);
    waste.setCategory(category);
    waste.setQuantity(quantity);
    waste.setWeightKg(weightKg);
    waste.setCollectionDate(collectionDate);
    waste.setLocation(location);
    waste.setStatus(status);
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

    const double averageWeightPerRecord = records.isEmpty() ? 0.0 : (totalWeight / static_cast<double>(records.size()));

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
    statusChart->setBackgroundBrush(QColor("#021a13"));
    statusChart->setTitleBrush(QBrush(QColor("#cffff0")));

    auto *statusChartView = new QChartView(statusChart, &statsDialog);
    statusChartView->setRenderHint(QPainter::Antialiasing, true);
    statusChartView->setStyleSheet("background: transparent;");
    statusChartView->setMinimumHeight(240);
    statusChartView->setMinimumWidth(360);

    auto *typeSet = new QBarSet("Type Count");
    QStringList typeCategories;
    int maxTypeCount = 0;
    for (auto it = byType.constBegin(); it != byType.constEnd(); ++it) {
        *typeSet << it.value();
        typeCategories << it.key();
        if (it.value() > maxTypeCount) {
            maxTypeCount = it.value();
        }
    }

    auto *typeSeries = new QBarSeries();
    typeSeries->append(typeSet);

    auto *typeChart = new QChart();
    typeChart->addSeries(typeSeries);
    typeChart->setTitle("Records by Type");
    typeChart->setAnimationOptions(QChart::SeriesAnimations);
    typeChart->legend()->setVisible(false);
    typeChart->setBackgroundBrush(QColor("#021a13"));
    typeChart->setTitleBrush(QBrush(QColor("#cffff0")));

    auto *axisX = new QBarCategoryAxis();
    axisX->append(typeCategories);
    auto *axisY = new QValueAxis();
    axisY->setRange(0, qMax(1, maxTypeCount + 1));
    axisY->setTickCount(qMin(10, qMax(2, maxTypeCount + 2)));

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
        locationBreakdown += QString("%1: %2").arg(it.key(), QString::number(it.value()));
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
=======


    // ✅ ADD THIS LINE ONLY
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
}


// ================= ADD THIS FUNCTION ONLY =================
>>>>>>> origin/waste

void MainWindow::showWastePage()
{
    ui->stackedwidget->setCurrentWidget(ui->wastemanagement);
}

<<<<<<< HEAD
=======

// ================= YOUR ORIGINAL FUNCTIONS =================

>>>>>>> origin/waste
void MainWindow::showLoginPage()
{
    ui->stackedwidget->setCurrentWidget(ui->connection);
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
    ui->stackedwidget->setCurrentWidget(ui->main);
}

void MainWindow::showEmployeePage()
{
    ui->stackedwidget->setCurrentWidget(ui->employe);
}

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
