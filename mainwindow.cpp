#include "mainwindow.h"
#include "ui_mainwindow.h"
<<<<<<< HEAD
#include "supplier.h"
#include "emailsender.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QRegularExpression>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QMap>
#include <QTimer>
#include <QChartView>
#include <QChart>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QPieSeries>
#include <QPieSlice>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QPageLayout>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    ui->suppliersTable->setModel(supplier::afficher());

    // ─── Contract expiry checker — runs on startup + every 24h ───
    QTimer* contractTimer = new QTimer(this);
    connect(contractTimer, &QTimer::timeout, this, &MainWindow::checkExpiringContracts);
    contractTimer->start(24 * 60 * 60 * 1000);
    checkExpiringContracts();

    // ─────────────────────────────────────────────────────────────
    // ADD SUPPLIER
    // ─────────────────────────────────────────────────────────────
    connect(ui->btnAddSupplier, &QPushButton::clicked, this, [=]() {
        ui->lineEdit_id->clear();
        ui->lineEdit_name->clear();
        ui->lineEdit_email->clear();
        ui->lineEdit_phone->clear();
        ui->lineEdit_product->clear();
        ui->lineEdit_contract->clear();
        ui->lineEdit_rating->clear();
        ui->dateEdit_date->setDate(QDate::currentDate());
        ui->dateEdit_endDate->setDate(QDate::currentDate().addYears(1));
        ui->stackedWidget->setCurrentIndex(1);
    });

    // ─────────────────────────────────────────────────────────────
    // SAVE (add or edit)
    // ─────────────────────────────────────────────────────────────
    connect(ui->btnSaveSupplier, &QPushButton::clicked, this, [=]() {
        QString name      = ui->lineEdit_name->text().trimmed();
        QString email     = ui->lineEdit_email->text().trimmed();
        QString phone     = ui->lineEdit_phone->text().trimmed();
        QString product   = ui->lineEdit_product->text().trimmed();
        QString contract  = ui->lineEdit_contract->text().trimmed();
        QString date      = ui->dateEdit_date->date().toString("yyyy-MM-dd");
        QString endDate   = ui->dateEdit_endDate->date().toString("yyyy-MM-dd");
        QString ratingStr = ui->lineEdit_rating->text().trimmed();

        QStringList errors;

        if (name.isEmpty())
            errors << "• Name is required.";
        else if (!QRegularExpression("^[A-Za-z\\s]+$").match(name).hasMatch())
            errors << "• Name must contain letters only (no numbers or symbols).";

        if (email.isEmpty())
            errors << "• Email is required.";
        else if (!QRegularExpression("^[\\w._%+\\-]+@[\\w.\\-]+\\.[a-zA-Z]{2,}$").match(email).hasMatch())
            errors << "• Email format is invalid (e.g. name@example.com).";

        if (phone.isEmpty())
            errors << "• Phone is required.";
        else if (!QRegularExpression("^[0-9]{8,15}$").match(phone).hasMatch())
            errors << "• Phone must contain 8 to 15 digits only.";

        if (product.isEmpty())
            errors << "• Product type is required.";

        if (contract.isEmpty())
            errors << "• Contract is required.";

        if (ui->dateEdit_date->date() > QDate::currentDate())
            errors << "• Start date cannot be in the future.";

        if (ui->dateEdit_endDate->date() < QDate::currentDate())
            errors << "• End date cannot be in the past.";

        if (ui->dateEdit_endDate->date() <= ui->dateEdit_date->date())
            errors << "• End date must be after the start date.";

        if (ratingStr.isEmpty()) {
            errors << "• Rating is required.";
        } else {
            bool ok;
            double r = ratingStr.toDouble(&ok);
            if (!ok)
                errors << "• Rating must be a number.";
            else if (r < 0 || r > 5)
                errors << "• Rating must be between 0 and 5.";
        }

        if (!errors.isEmpty()) {
            QMessageBox::warning(this, "Validation Error",
                                 "Please fix the following:\n\n" + errors.join("\n"));
            return;
        }

        double rating = ratingStr.toDouble();
        supplier s(name, email, phone, product, contract, date, endDate, rating);

        if (ui->lineEdit_id->text().isEmpty()) {
            if (s.ajouter())
                QMessageBox::information(this, "Success", "Supplier added successfully.");
        } else {
            if (s.modifier(ui->lineEdit_id->text().toInt()))
                QMessageBox::information(this, "Success", "Supplier updated successfully.");
        }

        auto* old = ui->suppliersTable->model();
        ui->suppliersTable->setModel(supplier::afficher());
        delete old;
        ui->stackedWidget->setCurrentIndex(0);
    });

    // ─────────────────────────────────────────────────────────────
    // EDIT
    // ─────────────────────────────────────────────────────────────
    connect(ui->btnEditSupplier, &QPushButton::clicked, this, [=]() {
        QModelIndex index = ui->suppliersTable->currentIndex();
        if (!index.isValid()) return;

        int row  = index.row();
        auto* m  = ui->suppliersTable->model();

        ui->lineEdit_id->setText(m->data(m->index(row, 0)).toString());
        ui->lineEdit_name->setText(m->data(m->index(row, 1)).toString());
        ui->lineEdit_email->setText(m->data(m->index(row, 2)).toString());
        ui->lineEdit_phone->setText(m->data(m->index(row, 3)).toString());
        ui->lineEdit_product->setText(m->data(m->index(row, 4)).toString());
        ui->lineEdit_contract->setText(m->data(m->index(row, 5)).toString());

        QDate d = QDate::fromString(m->data(m->index(row, 6)).toString(), "yyyy-MM-dd");
        ui->dateEdit_date->setDate(d.isValid() ? d : QDate::currentDate());

        ui->lineEdit_rating->setText(m->data(m->index(row, 7)).toString());

        QDate ed = QDate::fromString(m->data(m->index(row, 8)).toString(), "yyyy-MM-dd");
        ui->dateEdit_endDate->setDate(ed.isValid() ? ed : QDate::currentDate().addYears(1));

        ui->stackedWidget->setCurrentIndex(1);
    });

    // ─────────────────────────────────────────────────────────────
    // DELETE
    // ─────────────────────────────────────────────────────────────
    connect(ui->btnDeleteSupplier, &QPushButton::clicked, this, [=]() {
        QModelIndex index = ui->suppliersTable->currentIndex();
        if (!index.isValid()) {
            QMessageBox::warning(this, "Delete", "Please select a supplier to delete.");
            return;
        }

        auto confirm = QMessageBox::question(this, "Delete",
                                             "Are you sure you want to delete this supplier?");
        if (confirm != QMessageBox::Yes) return;

        int id = ui->suppliersTable->model()->data(
                                                ui->suppliersTable->model()->index(index.row(), 0)).toInt();

        supplier s;
        if (s.supprimer(id))
            QMessageBox::information(this, "Deleted", "Supplier deleted successfully.");

        auto* old = ui->suppliersTable->model();
        ui->suppliersTable->setModel(supplier::afficher());
        delete old;
    });

    // ─────────────────────────────────────────────────────────────
    // RATE — Custom Star Dialog
    // ─────────────────────────────────────────────────────────────
    connect(ui->btnRateSupplier, &QPushButton::clicked, this, [=]() {
        QModelIndex index = ui->suppliersTable->currentIndex();
        if (!index.isValid()) {
            QMessageBox::warning(this, "Rate", "Please select a supplier to rate.");
            return;
        }

        int id = ui->suppliersTable->model()->data(
                                                ui->suppliersTable->model()->index(index.row(), 0)).toInt();
        double current = ui->suppliersTable->model()->data(
                                                        ui->suppliersTable->model()->index(index.row(), 7)).toDouble();

        QDialog* dialog = new QDialog(this);
        dialog->setWindowTitle("Rate Supplier");
        dialog->setFixedSize(360, 190);
        dialog->setStyleSheet("QDialog { background-color: #0d1f0d; border: 1px solid #00ff88; }");

        QVBoxLayout* layout = new QVBoxLayout(dialog);
        layout->setSpacing(16);
        layout->setContentsMargins(28, 22, 28, 22);

        QLabel* title = new QLabel("Rate Supplier");
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet("font-size: 15px; font-weight: bold; color: #ffffff; letter-spacing: 1px;");
        layout->addWidget(title);

        QHBoxLayout* starRow = new QHBoxLayout();
        starRow->setSpacing(6);
        starRow->setAlignment(Qt::AlignCenter);

        const int MAX_STARS = 5;
        int* selectedRating = new int(qMax(1, qRound(current)));

        QList<QPushButton*> stars;
        for (int i = 1; i <= MAX_STARS; i++) {
            QPushButton* star = new QPushButton();
            star->setFixedSize(46, 46);
            star->setFlat(true);
            star->setCursor(Qt::PointingHandCursor);
            star->setProperty("starIndex", i);
            stars.append(star);
            starRow->addWidget(star);
        }

        auto refreshStars = [stars, selectedRating]() {
            for (QPushButton* s : stars) {
                int idx = s->property("starIndex").toInt();
                bool filled = (idx <= *selectedRating);
                s->setText(filled ? "★" : "☆");
                s->setStyleSheet(QString(
                                     "font-size: 32px; border: none; background: transparent; color: %1;")
                                     .arg(filled ? "#00ff88" : "#1a4d2e"));
            }
        };

        refreshStars();

        for (QPushButton* star : stars) {
            connect(star, &QPushButton::clicked, dialog, [=]() {
                *selectedRating = star->property("starIndex").toInt();
                refreshStars();
            });
        }

        layout->addLayout(starRow);

        QHBoxLayout* btnRow = new QHBoxLayout();
        btnRow->setSpacing(12);

        QPushButton* cancelBtn  = new QPushButton("Cancel");
        QPushButton* confirmBtn = new QPushButton("Confirm");
        cancelBtn->setFixedHeight(36);
        confirmBtn->setFixedHeight(36);

        cancelBtn->setStyleSheet(
            "QPushButton { background: transparent; color: #00ff88; border: 1px solid #00ff88;"
            "border-radius: 6px; font-size: 13px; }"
            "QPushButton:hover { background: #00ff8822; }");
        confirmBtn->setStyleSheet(
            "QPushButton { background: #00ff88; color: #0d1f0d; border: none;"
            "border-radius: 6px; font-size: 13px; font-weight: bold; }"
            "QPushButton:hover { background: #00cc6a; }");

        btnRow->addWidget(cancelBtn);
        btnRow->addWidget(confirmBtn);
        layout->addLayout(btnRow);

        connect(cancelBtn,  &QPushButton::clicked, dialog, &QDialog::reject);
        connect(confirmBtn, &QPushButton::clicked, dialog, &QDialog::accept);

        if (dialog->exec() == QDialog::Accepted) {
            supplier s;
            s.updateRating(id, static_cast<double>(*selectedRating));
            auto* old = ui->suppliersTable->model();
            ui->suppliersTable->setModel(supplier::afficher());
            delete old;
        }

        delete selectedRating;
        delete dialog;
    });

    // ─────────────────────────────────────────────────────────────
    // SEARCH (live)
    // ─────────────────────────────────────────────────────────────
    connect(ui->searchBox, &QLineEdit::textChanged, this, [=](QString text) {
        auto* old = ui->suppliersTable->model();
        ui->suppliersTable->setModel(supplier::rechercher(text));
        delete old;
    });

    // ─────────────────────────────────────────────────────────────
    // SORT
    // ─────────────────────────────────────────────────────────────
    connect(ui->sortComboBox, &QComboBox::currentTextChanged, this, [=](QString text) {
        auto* old = ui->suppliersTable->model();
        ui->suppliersTable->setModel(supplier::trier(text));
        delete old;
    });

    // ─────────────────────────────────────────────────────────────
    // NAVIGATION
    // ─────────────────────────────────────────────────────────────
    connect(ui->btnCancelForm, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btnViewSuppliers, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btnClearSelection, &QPushButton::clicked, this, [=]() {
        ui->suppliersTable->clearSelection();
    });

    connect(ui->btnExportPDF, &QPushButton::clicked, this, &MainWindow::exportPDF);

    // ─────────────────────────────────────────────────────────────
    // STATS POPUP
    // ─────────────────────────────────────────────────────────────
    connect(ui->btnSupplierStats, &QPushButton::clicked, this, [=]() {

        QSqlQueryModel* model = supplier::afficher();

        QMap<QString, int>    productCount;
        QMap<QString, double> productRatingSum;
        QMap<QString, int>    productRatingCount;
        int totalSuppliers = model->rowCount();

        for (int i = 0; i < totalSuppliers; i++) {
            QString product = model->data(model->index(i, 4)).toString();
            double  rating  = model->data(model->index(i, 7)).toDouble();
            productCount[product]++;
            productRatingSum[product]   += rating;
            productRatingCount[product]++;
        }

        QDialog* dialog = new QDialog(this);
        dialog->setWindowTitle("Supplier Statistics");
        dialog->resize(750, 520);
        dialog->setStyleSheet(
            "QDialog { background-color: #0a1a0a; border: 1px solid #00ff88; }"
            "QTabWidget::pane { border: 1px solid #00ff88; background: #0d1f0d; }"
            "QTabBar::tab { background: #0a1a0a; color: #00ff88; border: 1px solid #00ff88;"
            "border-bottom: none; padding: 6px 18px; font-size: 12px; margin-right: 2px; }"
            "QTabBar::tab:selected { background: #00ff88; color: #0a1a0a; font-weight: bold; }"
            "QTabBar::tab:hover:!selected { background: #00ff8822; }");

        auto styleChart = [](QChart* chart) {
            chart->setBackgroundBrush(QBrush(QColor("#0d1f0d")));
            chart->setPlotAreaBackgroundBrush(QBrush(QColor("#0d1f0d")));
            chart->setPlotAreaBackgroundVisible(true);
            chart->setTitleBrush(QBrush(QColor("#00ff88")));
            chart->setTitleFont(QFont("Arial", 11, QFont::Bold));
            chart->legend()->setLabelColor(QColor("#00ff88"));
            chart->legend()->setColor(QColor("#0d1f0d"));
        };

        auto styleAxes = [](QAbstractAxis* axisX, QAbstractAxis* axisY) {
            QPen axisPen(QColor("#00ff88")); axisPen.setWidth(1);
            axisX->setLinePen(axisPen); axisY->setLinePen(axisPen);
            axisX->setGridLinePen(QPen(QColor("#1a4d2e"), 1, Qt::DashLine));
            axisY->setGridLinePen(QPen(QColor("#1a4d2e"), 1, Qt::DashLine));
            axisX->setLabelsColor(QColor("#00ff88")); axisY->setLabelsColor(QColor("#00ff88"));
            axisX->setTitleBrush(QBrush(QColor("#00ff88")));
            axisY->setTitleBrush(QBrush(QColor("#00ff88")));
        };

        QVBoxLayout* mainLayout = new QVBoxLayout(dialog);
        mainLayout->setContentsMargins(12, 12, 12, 12);
        mainLayout->setSpacing(10);
        QTabWidget* tabs = new QTabWidget();

        // Tab 1: Bar — percentage of suppliers per product type
        {
            QChart* chart = new QChart();
            chart->setTitle("Suppliers by Product Type (%)");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            styleChart(chart);

            QBarSet* set = new QBarSet("Share (%)");
            set->setColor(QColor("#00ff88"));
            set->setBorderColor(QColor("#00cc6a"));
            QStringList labels;

            for (auto it = productCount.begin(); it != productCount.end(); ++it) {
                double pct = totalSuppliers > 0 ? (it.value() * 100.0 / totalSuppliers) : 0.0;
                *set << pct;
                labels << it.key();
            }

            QBarSeries* series = new QBarSeries();
            series->append(set);
            series->setLabelsVisible(true);
            series->setLabelsFormat("@value%");
            series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
            chart->addSeries(series);

            QBarCategoryAxis* axisX = new QBarCategoryAxis();
            axisX->append(labels);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            QValueAxis* axisY = new QValueAxis();
            axisY->setTitleText("Percentage (%)");
            axisY->setRange(0, 100);
            axisY->setLabelFormat("%.0f%%");
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);

            styleAxes(axisX, axisY);
            chart->legend()->setVisible(false);

            QChartView* view = new QChartView(chart);
            view->setRenderHint(QPainter::Antialiasing);
            view->setBackgroundBrush(QBrush(QColor("#0d1f0d")));
            tabs->addTab(view, "Suppliers per Product");
        }

        // Tab 2: Pie — distribution
        {
            QChart* chart = new QChart();
            chart->setTitle("Supplier Distribution by Product Type");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            styleChart(chart);

            QPieSeries* series = new QPieSeries();
            QList<QColor> palette = {
                QColor("#00ff88"), QColor("#00cc6a"), QColor("#009950"),
                QColor("#006633"), QColor("#1a4d2e")
            };
            int colorIdx = 0;

            for (auto it = productCount.begin(); it != productCount.end(); ++it) {
                double pct = totalSuppliers > 0 ? (it.value() * 100.0 / totalSuppliers) : 0.0;
                QPieSlice* slice = series->append(it.key(), it.value());
                slice->setLabelVisible(true);
                slice->setLabel(QString("%1 (%2%)").arg(it.key()).arg(QString::number(pct, 'f', 1)));
                slice->setLabelColor(QColor("#ffffff"));
                slice->setBrush(palette[colorIdx % palette.size()]);
                slice->setBorderColor(QColor("#0a1a0a"));
                colorIdx++;
            }

            chart->addSeries(series);
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignRight);

            QChartView* view = new QChartView(chart);
            view->setRenderHint(QPainter::Antialiasing);
            view->setBackgroundBrush(QBrush(QColor("#0d1f0d")));
            tabs->addTab(view, "Distribution");
        }

        // Tab 3: Bar — average rating as percentage of 5
        {
            QChart* chart = new QChart();
            chart->setTitle("Average Rating by Product Type (% of 5)");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            styleChart(chart);

            QBarSet* set = new QBarSet("Performance (%)");
            set->setColor(QColor("#00ff88"));
            set->setBorderColor(QColor("#00cc6a"));
            QStringList labels;

            for (auto it = productRatingSum.begin(); it != productRatingSum.end(); ++it) {
                double avg = it.value() / productRatingCount[it.key()];
                double pct = (avg / 5.0) * 100.0;
                *set << pct;
                labels << it.key();
            }

            QBarSeries* series = new QBarSeries();
            series->append(set);
            series->setLabelsVisible(true);
            series->setLabelsFormat("@value%");
            series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
            chart->addSeries(series);

            QBarCategoryAxis* axisX = new QBarCategoryAxis();
            axisX->append(labels);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            QValueAxis* axisY = new QValueAxis();
            axisY->setTitleText("Performance (%)");
            axisY->setRange(0, 100);
            axisY->setLabelFormat("%.0f%%");
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);

            styleAxes(axisX, axisY);
            chart->legend()->setVisible(false);

            QChartView* view = new QChartView(chart);
            view->setRenderHint(QPainter::Antialiasing);
            view->setBackgroundBrush(QBrush(QColor("#0d1f0d")));
            tabs->addTab(view, "Avg Rating");
        }

        mainLayout->addWidget(tabs);

        QPushButton* closeBtn = new QPushButton("Close");
        closeBtn->setFixedHeight(38);
        closeBtn->setStyleSheet(
            "QPushButton { background: transparent; color: #00ff88; border: 1px solid #00ff88;"
            "border-radius: 6px; font-size: 13px; }"
            "QPushButton:hover { background: #00ff8822; }");
        connect(closeBtn, &QPushButton::clicked, dialog, &QDialog::accept);
        mainLayout->addWidget(closeBtn);

        dialog->exec();
        delete model;
    });
=======

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Start on login page
    ui->stackedwidget->setCurrentIndex(0);

    // Connect all navigation buttons
    setupConnections();
>>>>>>> origin/supplier
}

MainWindow::~MainWindow()
{
    delete ui;
}

<<<<<<< HEAD
// ─────────────────────────────────────────────────────────────────
// CONTRACT EXPIRY CHECK + EMAIL SENDER
// ─────────────────────────────────────────────────────────────────
void MainWindow::checkExpiringContracts()
{
    QSqlQueryModel* model = supplier::getExpiringContracts(3);
    int count = 0;

    for (int i = 0; i < model->rowCount(); i++) {
        QString name     = model->data(model->index(i, 1)).toString();
        QString email    = model->data(model->index(i, 2)).toString();
        QString contract = model->data(model->index(i, 3)).toString();
        QString expiry   = model->data(model->index(i, 4)).toString();

        if (EmailSender::sendMail(email, name, contract, expiry))
            count++;
    }

    if (count > 0)
        QMessageBox::information(this, "Contract Alerts",
                                 QString("%1 expiry reminder(s) sent automatically.").arg(count));

    delete model;
}

// ─────────────────────────────────────────────────────────────────
// EXPORT PDF
// ─────────────────────────────────────────────────────────────────
void MainWindow::exportPDF()
{
    const QString filePath = QFileDialog::getSaveFileName(
        this, "Export Suppliers PDF", "suppliers.pdf", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) return;

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageOrientation(QPageLayout::Landscape);
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    const int margin = 60, rowHeight = 60;
    int pageWidth  = pdfWriter.width();
    int pageHeight = pdfWriter.height();
    int tableWidth = pageWidth - (2 * margin);
    int y = margin;

    painter.setFont(QFont("Arial", 30, QFont::Bold));
    painter.drawText(QRect(margin, y, tableWidth, 80), Qt::AlignCenter, "Suppliers List");
    y += 100;

    QStringList headers = {"ID", "Name", "Email", "Phone", "Product", "Contract", "Date", "End Date", "Rating"};
    QVector<int> columnWidths = {
        (int)(tableWidth * 0.05),
        (int)(tableWidth * 0.12),
        (int)(tableWidth * 0.18),
        (int)(tableWidth * 0.10),
        (int)(tableWidth * 0.10),
        (int)(tableWidth * 0.10),
        (int)(tableWidth * 0.10),
        (int)(tableWidth * 0.10),
        (int)(tableWidth * 0.08)
    };

    auto drawHeader = [&]() {
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.fillRect(QRect(margin, y, tableWidth, rowHeight), QColor(235, 235, 235));
        int x = margin;
        for (int i = 0; i < headers.size(); ++i) {
            QRect rect(x, y, columnWidths[i], rowHeight);
            painter.drawRect(rect);
            painter.drawText(rect, Qt::AlignCenter, headers[i]);
            x += columnWidths[i];
        }
        y += rowHeight;
        painter.setFont(QFont("Arial", 13));
    };

    drawHeader();

    QSqlQueryModel* model = supplier::afficher();
    for (int r = 0; r < model->rowCount(); ++r) {
        if (y + rowHeight > pageHeight - margin) {
            pdfWriter.newPage();
            y = margin;
            drawHeader();
        }
        int x = margin;
        for (int c = 0; c < headers.size(); ++c) {
            QRect rect(x, y, columnWidths[c], rowHeight);
            painter.drawRect(rect);
            painter.drawText(rect.adjusted(8, 8, -8, -8),
                             Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignVCenter,
                             model->data(model->index(r, c)).toString());
            x += columnWidths[c];
        }
        y += rowHeight;
    }
    delete model;

    painter.end();
    QMessageBox::information(this, "Export PDF", "Suppliers list exported successfully.");
=======
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
    connect(ui->btnEmpCustomer, &QPushButton::clicked, this, &MainWindow::showCustomerPage);
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
    // Waste Management Sidebar Navigation
    connect(ui->btnDashboard, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->btnEmployee, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
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


    // ✅ ADD THIS LINE ONLY
    connect(ui->btnEmpWaste, &QPushButton::clicked, this, &MainWindow::showWastePage);
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544
}


// ================= ADD THIS FUNCTION ONLY =================

void MainWindow::showWastePage()
{
    ui->stackedwidget->setCurrentWidget(ui->wastemanagement);
}

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
>>>>>>> origin/supplier
}
