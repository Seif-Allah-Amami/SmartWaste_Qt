#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customer.h"
#include <QAbstractItemView>
#include <QDate>
#include <QMessageBox>
#include <QTableWidgetItem>

#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>

// QtCharts includes
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

void MainWindow::onSortComboBox5Changed(int)
{
    // Re-filter and sort using the current search text
    onSearchBox5TextChanged(ui->searchBox_5->text());
}

void MainWindow::onSearchBox5TextChanged(const QString &text)
{
    QList<Customer> filtered;
    QString search = text.trimmed();
    for (const Customer &c : allCustomers_) {
        if (search.isEmpty() ||
            QString::number(c.customerId()).contains(search, Qt::CaseInsensitive) ||
            c.name().contains(search, Qt::CaseInsensitive) ||
            c.email().contains(search, Qt::CaseInsensitive) ||
            c.phone().contains(search, Qt::CaseInsensitive)) {
            filtered.append(c);
        }
    }
    updateCustomersTable(filtered);
}

void MainWindow::updateCustomersTable(const QList<Customer> &customers)
{
    ui->customersTable->setSortingEnabled(false);
    ui->customersTable->setRowCount(0);

    auto setItem = [this](int row, int column, const QString &text) {
        auto *item = new QTableWidgetItem(text);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->customersTable->setItem(row, column, item);
    };

    QList<Customer> sorted = customers;
    int sortIndex = ui->sortComboBox_5->currentIndex();
    std::sort(sorted.begin(), sorted.end(), [sortIndex](const Customer &a, const Customer &b) {
        switch (sortIndex) {
        case 0: // Name (A-Z)
            return a.name().toLower() < b.name().toLower();
        case 1: // Type
            return a.reportType().toLower() < b.reportType().toLower();
        case 2: // Date (Newest)
            return a.reportDate() > b.reportDate();
        default:
            return a.name().toLower() < b.name().toLower();
        }
    });
    for (int i = 0; i < sorted.size(); ++i) {
        const Customer &customer = sorted.at(i);
        ui->customersTable->insertRow(i);
        setItem(i, 0, QString::number(customer.customerId()));
        setItem(i, 1, customer.name());
        setItem(i, 2, customer.email());
        setItem(i, 3, customer.phone());
        setItem(i, 4, customer.address());
        setItem(i, 5, customer.reportType());
        setItem(i, 6, QString());
        setItem(i, 7, customer.reportDate().isValid() ? customer.reportDate().toString("yyyy-MM-dd") : QString());
        setItem(i, 8, QString::number(customer.satisfactionScore(), 'f', 2));
        setItem(i, 9, QString::number(customer.employeeId()));
    }
    ui->customersTable->resizeColumnsToContents();
    ui->customersTable->setSortingEnabled(true);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->customersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->btnViewCustomers, &QPushButton::clicked, this, &MainWindow::loadCustomers);
    connect(ui->btnAddCustomer, &QPushButton::clicked, this, &MainWindow::onAddCustomer);
    connect(ui->btnEditCustomer, &QPushButton::clicked, this, &MainWindow::onEditCustomer);
    connect(ui->btnDeleteCustomer, &QPushButton::clicked, this, &MainWindow::onDeleteCustomer);
    connect(ui->searchBox_5, &QLineEdit::textChanged, this, &MainWindow::onSearchBox5TextChanged);
    connect(ui->sortComboBox_5, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onSortComboBox5Changed);
    connect(ui->btnClearSelection_5, &QPushButton::clicked, this, &MainWindow::onClearSelection5Clicked);
    connect(ui->btnExportPDF_5, &QPushButton::clicked, this, &MainWindow::onExportPDFClicked);
    connect(ui->btnReportStatus, &QPushButton::clicked, this, &MainWindow::onReportStatusClicked);
    loadCustomers();
}

// ...existing code...

void MainWindow::onReportStatusClicked()
{
    // Count report types
    QMap<QString, int> typeCounts;
    for (const Customer &c : allCustomers_) {
        typeCounts[c.reportType()]++;
    }

    QPieSeries *series = new QPieSeries();
    for (auto it = typeCounts.begin(); it != typeCounts.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Report Status Distribution");
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Show chart in a dialog
    QDialog dialog(this);
    dialog.setWindowTitle("Report Status Pie Chart");
    QVBoxLayout layout;
    layout.addWidget(chartView);
    dialog.setLayout(&layout);
    dialog.resize(500, 400);
    dialog.exec();
}

void MainWindow::onExportPDFClicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Export Customers to PDF",
        "customers.pdf",
        "PDF Files (*.pdf)");

    if (fileName.isEmpty())
        return;

    QPdfWriter pdfWriter(fileName);

    // ===== Page Setup =====
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageOrientation(QPageLayout::Landscape);
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    const int margin = 60;
    const int rowHeight = 60;   // Bigger rows

    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();

    int tableWidth = pageWidth - (2 * margin);

    int y = margin;

    // ===== BIG TITLE =====
    painter.setFont(QFont("Arial", 30, QFont::Bold));
    painter.drawText(QRect(margin, y, tableWidth, 80),
                     Qt::AlignCenter,
                     "Customer List");
    y += 100;

    // ===== HEADERS =====
    QStringList headers = {
        "ID", "Name", "Email", "Phone",
        "Address", "Type", "Date",
        "Score", "Employee"
    };

    // Custom column widths (proportional)
    QVector<int> columnWidths = {
        tableWidth * 0.06,  // ID
        tableWidth * 0.14,  // Name
        tableWidth * 0.18,  // Email
        tableWidth * 0.12,  // Phone
        tableWidth * 0.20,  // Address
        tableWidth * 0.10,  // Type
        tableWidth * 0.10,  // Date
        tableWidth * 0.05,  // Score
        tableWidth * 0.05   // Employee
    };

    auto drawHeader = [&]() {
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.fillRect(QRect(margin, y, tableWidth, rowHeight),
                         QColor(210, 210, 210));

        int x = margin;

        for (int i = 0; i < headers.size(); ++i) {
            QRect rect(x, y, columnWidths[i], rowHeight);
            painter.drawRect(rect);
            painter.drawText(rect,
                             Qt::AlignCenter,
                             headers[i]);
            x += columnWidths[i];
        }

        y += rowHeight;
        painter.setFont(QFont("Arial", 14));
    };

    drawHeader();

    // ===== DATA =====
    bool alternate = false;

    for (const Customer &c : allCustomers_) {

        // New page if needed
        if (y + rowHeight > pageHeight - margin) {
            pdfWriter.newPage();
            y = margin;
            drawHeader();
        }

        if (alternate) {
            painter.fillRect(QRect(margin, y, tableWidth, rowHeight),
                             QColor(245, 245, 245));
        }

        QStringList row = {
            QString::number(c.customerId()),
            c.name(),
            c.email(),
            c.phone(),
            c.address(),
            c.reportType(),
            c.reportDate().isValid()
                ? c.reportDate().toString("yyyy-MM-dd")
                : "",
            QString::number(c.satisfactionScore(), 'f', 2),
            QString::number(c.employeeId())
        };

        int x = margin;

        for (int i = 0; i < row.size(); ++i) {
            QRect rect(x, y, columnWidths[i], rowHeight);
            painter.drawRect(rect);

            painter.drawText(
                rect.adjusted(10, 8, -10, -8),
                Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignVCenter,
                row[i]
                );

            x += columnWidths[i];
        }

        y += rowHeight;
        alternate = !alternate;
    }

    painter.end();

    QMessageBox::information(this,
                             "Export PDF",
                             "Large professional PDF exported successfully.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClearSelection5Clicked()
{
    ui->searchBox_5->clear();
    updateCustomersTable(allCustomers_);
}

void MainWindow::loadCustomers()
{
    QString errorMessage;
    allCustomers_.clear();
    if (!Customer::fetchAll(allCustomers_, &errorMessage)) {
        QMessageBox::warning(this, "Customers", "Failed to load customers.\n" + errorMessage);
        return;
    }
    updateCustomersTable(allCustomers_);
}

void MainWindow::onAddCustomer()
{
    AddCustomerDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    Customer customer = dialog.customer();
    QString errorMessage;
    if (!customer.add(&errorMessage)) {
        QMessageBox::warning(this, "Customers", "Failed to add customer.\n" + errorMessage);
        return;
    }

    loadCustomers();
}

void MainWindow::onEditCustomer()
{
    int row = ui->customersTable->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Customers", "Select a customer to edit.");
        return;
    }

    auto itemText = [this, row](int column) {
        QTableWidgetItem *item = ui->customersTable->item(row, column);
        return item ? item->text().trimmed() : QString();
    };

    Customer customer(
        itemText(0).toInt(),
        itemText(1),
        itemText(2),
        itemText(3),
        itemText(4),
        itemText(5),
        QDate::fromString(itemText(7), "yyyy-MM-dd"),
        itemText(8).toDouble(),
        itemText(9).toInt());

    AddCustomerDialog dialog(this);
    dialog.setCustomer(customer);
    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    Customer updated = dialog.customer();
    QString errorMessage;
    if (!updated.update(&errorMessage)) {
        QMessageBox::warning(this, "Customers", "Failed to update customer.\n" + errorMessage);
        return;
    }

    loadCustomers();
}

void MainWindow::onDeleteCustomer()
{
    int row = ui->customersTable->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Customers", "Select a customer to delete.");
        return;
    }

    QTableWidgetItem *idItem = ui->customersTable->item(row, 0);
    if (!idItem) {
        QMessageBox::warning(this, "Customers", "Unable to read customer ID.");
        return;
    }

    int customerId = idItem->text().toInt();
    auto confirm = QMessageBox::question(this, "Customers", "Delete the selected customer?");
    if (confirm != QMessageBox::Yes) {
        return;
    }

    QString errorMessage;
    if (!Customer::remove(customerId, &errorMessage)) {
        QMessageBox::warning(this, "Customers", "Failed to delete customer.\n" + errorMessage);
        return;
    }

    loadCustomers();
}
