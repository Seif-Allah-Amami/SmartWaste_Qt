/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainHorizontalLayout;
    QGroupBox *sidebarGroup;
    QVBoxLayout *sidebarLayout;
    QLabel *sidebarLogo;
    QPushButton *btnDashboard;
    QPushButton *btnReports;
    QPushButton *btnCustomers;
    QPushButton *btnOrders;
    QPushButton *btnInventory;
    QPushButton *btnMachines;
    QPushButton *btnSuppliers;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnLogout;
    QWidget *mainContentWidget;
    QVBoxLayout *mainContentLayout;
    QHBoxLayout *headerLayout;
    QVBoxLayout *titleLayout;
    QLabel *pageTitle;
    QLabel *pageSubtitle;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *topActionsLayout;
    QPushButton *btnViewSuppliers;
    QPushButton *btnAddSupplier;
    QPushButton *btnSupplierStats;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *stackedWidget;
    QWidget *pageTable;
    QVBoxLayout *pageTableLayout;
    QWidget *searchFilterWidget;
    QVBoxLayout *searchFilterLayout;
    QLabel *lblSuppliersList;
    QHBoxLayout *searchLayout;
    QLineEdit *searchBox;
    QComboBox *sortComboBox;
    QHBoxLayout *tableActionsLayout;
    QTableView *suppliersTable;
    QFrame *actionsPanel;
    QVBoxLayout *actionsPanelLayout;
    QLabel *lblActions;
    QPushButton *btnEditSupplier;
    QPushButton *btnDeleteSupplier;
    QPushButton *btnClearSelection;
    QPushButton *btnRateSupplier;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btnExportPDF;
    QWidget *pageForm;
    QVBoxLayout *pageFormLayout;
    QFrame *formPanel;
    QVBoxLayout *formPanelLayout;
    QLabel *lblFormTitle;
    QHBoxLayout *formRow1;
    QVBoxLayout *colId;
    QLabel *lblId;
    QLineEdit *lineEdit_id;
    QVBoxLayout *colName;
    QLabel *lblName;
    QLineEdit *lineEdit_name;
    QHBoxLayout *formRow2;
    QVBoxLayout *colEmail;
    QLabel *lblEmail;
    QLineEdit *lineEdit_email;
    QVBoxLayout *colPhone;
    QLabel *lblPhone;
    QLineEdit *lineEdit_phone;
    QHBoxLayout *formRow3;
    QVBoxLayout *colProduct;
    QLabel *lblProduct;
    QLineEdit *lineEdit_product;
    QVBoxLayout *colContract;
    QLabel *lblContract;
    QLineEdit *lineEdit_contract;
    QHBoxLayout *formRow4;
    QVBoxLayout *colDate;
    QLabel *lblDate;
    QDateEdit *dateEdit_date;
    QVBoxLayout *colRating;
    QLabel *lblRating;
    QLineEdit *lineEdit_rating;
    QHBoxLayout *formRow5;
    QVBoxLayout *colEndDate;
    QLabel *lblEndDate;
    QDateEdit *dateEdit_endDate;
    QSpacerItem *horizontalSpacer_endDate;
    QSpacerItem *verticalSpacer_form;
    QHBoxLayout *formButtonsLayout;
    QSpacerItem *horizontalSpacer_form;
    QPushButton *btnCancelForm;
    QPushButton *btnSaveSupplier;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1357, 744);
        MainWindow->setStyleSheet(QString::fromUtf8("/* ===== Global ===== */\n"
"QWidget {\n"
"    background-color: #050d0a;\n"
"    color: #66ffcc;\n"
"    font-family: \"Segoe UI\", \"Inter\", \"Arial\";\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"/* ===== Main Content Area ===== */\n"
"QWidget#centralwidget {\n"
"    background-color: #050d0a;\n"
"}\n"
"\n"
"/* ===== Sidebar ===== */\n"
"QGroupBox#sidebarGroup {\n"
"    background-color: #0a1f18;\n"
"    border: none;\n"
"    border-right: 2px solid #00ff9c;\n"
"}\n"
"\n"
"QLabel#sidebarLogo {\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 20px;\n"
"}\n"
"\n"
"QLabel#sidebarTitle {\n"
"    font-size: 22px;\n"
"    font-weight: bold;\n"
"    color: #00ff9c;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"}\n"
"\n"
"QLabel#sidebarBreadcrumb {\n"
"    font-size: 11px;\n"
"    color: #66ffcc;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 0px 20px 15px 20px;\n"
"}\n"
"\n"
"/* Sidebar Menu Buttons */\n"
"QPushButton#sidebarBtn {"
                        "\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px 20px;\n"
"    color: #66ffcc;\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton#sidebarBtn:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    color: #00ff9c;\n"
"}\n"
"\n"
"QPushButton#sidebarBtn:pressed {\n"
"    background-color: rgba(0, 255, 156, 0.2);\n"
"}\n"
"\n"
"/* Active sidebar button */\n"
"QPushButton#sidebarBtnActive {\n"
"    background-color: rgba(0, 255, 156, 0.15);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px 20px;\n"
"    color: #00ff9c;\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    border-left: 3px solid #00ff9c;\n"
"}\n"
"\n"
"/* Logout button */\n"
"QPushButton#logoutBtn {\n"
"    background-color: transparent;\n"
"    border: 1px solid #ff6666;\n"
"    border-radius: 8px;\n"
"    padding: 12px 20px;\n"
"    color: #ff6666;\n"
"    font-weight: 60"
                        "0;\n"
"}\n"
"\n"
"QPushButton#logoutBtn:hover {\n"
"    background-color: rgba(255, 102, 102, 0.1);\n"
"}\n"
"\n"
"/* ===== Page Header ===== */\n"
"QLabel#pageTitle {\n"
"    font-size: 28px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"QLabel#pageSubtitle {\n"
"    font-size: 13px;\n"
"    font-weight: 400;\n"
"    color: #66ffcc;\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"/* ===== Top Action Buttons (View Customers, Add Customer, etc) ===== */\n"
"QPushButton#topActionBtn {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"    color: #00ff9c;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton#topActionBtn:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"}\n"
"\n"
"QPushButton#topActionBtnPrimary {\n"
"    background-color: #00ff9c;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    paddin"
                        "g: 10px 20px;\n"
"    color: #050d0a;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton#topActionBtnPrimary:hover {\n"
"    background-color: #33ffcc;\n"
"    border: 1px solid #33ffcc;\n"
"}\n"
"\n"
"/* ===== Search and Filter Area ===== */\n"
"QLabel#sectionLabel {\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 5px 0px;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background-color: #081713;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    color: #66ffcc;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #33ffcc;\n"
"    background-color: #0a1f18;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: #4d9977;\n"
"}\n"
"\n"
"QComboBox {\n"
"    background-color: #081713;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    color: #66ffcc;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QComboBox:ho"
                        "ver {\n"
"    border: 1px solid #33ffcc;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    padding-right: 10px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: url(:/icons/dropdown.png);\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"\n"
"/* ===== Table ===== */\n"
"QTableView {\n"
"    background-color: #081713;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    gridline-color: rgba(0, 255, 156, 0.2);\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QTableView::item {\n"
"    padding: 10px;\n"
"    color: #66ffcc;\n"
"}\n"
"\n"
"QTableView::item:selected {\n"
"    background-color: rgba(0, 255, 156, 0.2);\n"
"    color: #00ff9c;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #0a1f18;\n"
"    color: #00ff9c;\n"
"    padding: 12px 10px;\n"
"    border: none;\n"
"    border-bottom: 2px solid #00ff9c;\n"
"    font-weight: 600;\n"
"    font-size: 12px;\n"
"    text-transform: uppercase;\n"
"}\n"
"\n"
"/* ===== Actions Panel (Right Side) ===== */\n"
"QFrame#ac"
                        "tionsPanel {\n"
"    background-color: #081713;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QLabel#actionsPanelTitle {\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"/* Action Buttons in Right Panel */\n"
"QPushButton#actionBtn {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #00ff9c;\n"
"    font-weight: 500;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton#actionBtn:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    border: 1px solid #33ffcc;\n"
"}\n"
"\n"
"QPushButton#actionBtnDanger {\n"
"    background-color: transparent;\n"
"    border: 1px solid #ff6666;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #ff6666;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton#actionBtnDanger:hover {\n"
"    background-color:"
                        " rgba(255, 102, 102, 0.1);\n"
"}\n"
"\n"
"QPushButton#actionBtnExport {\n"
"    background-color: #00ff9c;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #050d0a;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton#actionBtnExport:hover {\n"
"    background-color: #33ffcc;\n"
"}\n"
"\n"
"/* ===== Form Panel ===== */\n"
"QFrame#formPanel {\n"
"    background-color: #081713;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QLabel#formTitle {\n"
"    font-size: 18px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"QLabel#formFieldLabel {\n"
"    font-size: 12px;\n"
"    font-weight: 600;\n"
"    color: #00ff9c;\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"QDateEdit {\n"
"    background-color: #081713;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    color: #66ffcc;\n"
"    font-si"
                        "ze: 13px;\n"
"}\n"
"\n"
"QDateEdit:focus {\n"
"    border: 1px solid #33ffcc;\n"
"    background-color: #0a1f18;\n"
"}\n"
"\n"
"QDateEdit::drop-down {\n"
"    border: none;\n"
"    padding-right: 10px;\n"
"}\n"
"\n"
"/* ===== Scrollbars ===== */\n"
"QScrollBar:vertical {\n"
"    background: #050d0a;\n"
"    width: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #00ff9c;\n"
"    border-radius: 5px;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #33ffcc;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"/* ===== Status Bar ===== */\n"
"QStatusBar {\n"
"    background-color: #0a1f18;\n"
"    color: #66ffcc;\n"
"    border-top: 1px solid #00ff9c;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainHorizontalLayout = new QHBoxLayout(centralwidget);
        mainHorizontalLayout->setSpacing(0);
        mainHorizontalLayout->setObjectName("mainHorizontalLayout");
        mainHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        sidebarGroup = new QGroupBox(centralwidget);
        sidebarGroup->setObjectName("sidebarGroup");
        sidebarGroup->setMinimumSize(QSize(250, 0));
        sidebarGroup->setMaximumSize(QSize(250, 16777215));
        sidebarLayout = new QVBoxLayout(sidebarGroup);
        sidebarLayout->setSpacing(0);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarLayout->setContentsMargins(0, 0, 0, 0);
        sidebarLogo = new QLabel(sidebarGroup);
        sidebarLogo->setObjectName("sidebarLogo");
        sidebarLogo->setMinimumSize(QSize(0, 100));
        sidebarLogo->setMaximumSize(QSize(16777215, 100));
        sidebarLogo->setPixmap(QPixmap(QString::fromUtf8(":/image/images/logo.png")));
        sidebarLogo->setScaledContents(false);
        sidebarLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarLayout->addWidget(sidebarLogo);

        btnDashboard = new QPushButton(sidebarGroup);
        btnDashboard->setObjectName("btnDashboard");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnDashboard->sizePolicy().hasHeightForWidth());
        btnDashboard->setSizePolicy(sizePolicy);
        btnDashboard->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px 20px;\n"
"    color: #66ffcc;\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    color: #00ff9c;\n"
"}"));

        sidebarLayout->addWidget(btnDashboard);

        btnReports = new QPushButton(sidebarGroup);
        btnReports->setObjectName("btnReports");
        btnReports->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px 20px;\n"
"    color: #66ffcc;\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    color: #00ff9c;\n"
"}"));

        sidebarLayout->addWidget(btnReports);

        btnCustomers = new QPushButton(sidebarGroup);
        btnCustomers->setObjectName("btnCustomers");
        btnCustomers->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px 20px;\n"
"    color: #66ffcc;\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    color: #00ff9c;\n"
"}"));

        sidebarLayout->addWidget(btnCustomers);

        btnOrders = new QPushButton(sidebarGroup);
        btnOrders->setObjectName("btnOrders");
        btnOrders->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px 20px;\n"
"    color: #66ffcc;\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    color: #00ff9c;\n"
"}"));

        sidebarLayout->addWidget(btnOrders);

        btnInventory = new QPushButton(sidebarGroup);
        btnInventory->setObjectName("btnInventory");
        btnInventory->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px 20px;\n"
"    color: #66ffcc;\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    color: #00ff9c;\n"
"}"));

        sidebarLayout->addWidget(btnInventory);

        btnMachines = new QPushButton(sidebarGroup);
        btnMachines->setObjectName("btnMachines");
        btnMachines->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px 20px;\n"
"    color: #66ffcc;\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    color: #00ff9c;\n"
"}"));

        sidebarLayout->addWidget(btnMachines);

        btnSuppliers = new QPushButton(sidebarGroup);
        btnSuppliers->setObjectName("btnSuppliers");
        btnSuppliers->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0, 255, 156, 0.15);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px 20px;\n"
"    color: #00ff9c;\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    border-left: 3px solid #00ff9c;\n"
"}"));

        sidebarLayout->addWidget(btnSuppliers);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(verticalSpacer_2);

        btnLogout = new QPushButton(sidebarGroup);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid #ff6666;\n"
"    border-radius: 8px;\n"
"    padding: 12px 20px;\n"
"    color: #ff6666;\n"
"    font-weight: 600;\n"
"    margin: 0px 15px 15px 15px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(255, 102, 102, 0.1);\n"
"}"));

        sidebarLayout->addWidget(btnLogout);


        mainHorizontalLayout->addWidget(sidebarGroup);

        mainContentWidget = new QWidget(centralwidget);
        mainContentWidget->setObjectName("mainContentWidget");
        mainContentLayout = new QVBoxLayout(mainContentWidget);
        mainContentLayout->setSpacing(20);
        mainContentLayout->setObjectName("mainContentLayout");
        mainContentLayout->setContentsMargins(30, 30, 30, 30);
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        titleLayout = new QVBoxLayout();
        titleLayout->setSpacing(5);
        titleLayout->setObjectName("titleLayout");
        pageTitle = new QLabel(mainContentWidget);
        pageTitle->setObjectName("pageTitle");

        titleLayout->addWidget(pageTitle);

        pageSubtitle = new QLabel(mainContentWidget);
        pageSubtitle->setObjectName("pageSubtitle");

        titleLayout->addWidget(pageSubtitle);


        headerLayout->addLayout(titleLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer);


        mainContentLayout->addLayout(headerLayout);

        topActionsLayout = new QHBoxLayout();
        topActionsLayout->setSpacing(10);
        topActionsLayout->setObjectName("topActionsLayout");
        btnViewSuppliers = new QPushButton(mainContentWidget);
        btnViewSuppliers->setObjectName("btnViewSuppliers");
        btnViewSuppliers->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0, 255, 156, 0.15);\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"    color: #00ff9c;\n"
"    font-weight: 600;\n"
"}"));

        topActionsLayout->addWidget(btnViewSuppliers);

        btnAddSupplier = new QPushButton(mainContentWidget);
        btnAddSupplier->setObjectName("btnAddSupplier");
        btnAddSupplier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"    color: #00ff9c;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"}"));

        topActionsLayout->addWidget(btnAddSupplier);

        btnSupplierStats = new QPushButton(mainContentWidget);
        btnSupplierStats->setObjectName("btnSupplierStats");
        btnSupplierStats->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"    color: #00ff9c;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"}"));

        topActionsLayout->addWidget(btnSupplierStats);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topActionsLayout->addItem(horizontalSpacer_2);


        mainContentLayout->addLayout(topActionsLayout);

        stackedWidget = new QStackedWidget(mainContentWidget);
        stackedWidget->setObjectName("stackedWidget");
        pageTable = new QWidget();
        pageTable->setObjectName("pageTable");
        pageTableLayout = new QVBoxLayout(pageTable);
        pageTableLayout->setSpacing(10);
        pageTableLayout->setObjectName("pageTableLayout");
        pageTableLayout->setContentsMargins(0, 0, 0, 0);
        searchFilterWidget = new QWidget(pageTable);
        searchFilterWidget->setObjectName("searchFilterWidget");
        searchFilterLayout = new QVBoxLayout(searchFilterWidget);
        searchFilterLayout->setSpacing(10);
        searchFilterLayout->setObjectName("searchFilterLayout");
        searchFilterLayout->setContentsMargins(0, 0, 0, 0);
        lblSuppliersList = new QLabel(searchFilterWidget);
        lblSuppliersList->setObjectName("lblSuppliersList");
        lblSuppliersList->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 5px 0px;\n"
"}"));

        searchFilterLayout->addWidget(lblSuppliersList);

        searchLayout = new QHBoxLayout();
        searchLayout->setSpacing(10);
        searchLayout->setObjectName("searchLayout");
        searchBox = new QLineEdit(searchFilterWidget);
        searchBox->setObjectName("searchBox");
        searchBox->setMinimumSize(QSize(0, 40));

        searchLayout->addWidget(searchBox);

        sortComboBox = new QComboBox(searchFilterWidget);
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->setObjectName("sortComboBox");
        sortComboBox->setMinimumSize(QSize(200, 40));
        sortComboBox->setMaximumSize(QSize(250, 16777215));

        searchLayout->addWidget(sortComboBox);


        searchFilterLayout->addLayout(searchLayout);


        pageTableLayout->addWidget(searchFilterWidget);

        tableActionsLayout = new QHBoxLayout();
        tableActionsLayout->setSpacing(20);
        tableActionsLayout->setObjectName("tableActionsLayout");
        suppliersTable = new QTableView(pageTable);
        suppliersTable->setObjectName("suppliersTable");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(suppliersTable->sizePolicy().hasHeightForWidth());
        suppliersTable->setSizePolicy(sizePolicy1);
        suppliersTable->setMinimumSize(QSize(600, 0));
        suppliersTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        suppliersTable->setAlternatingRowColors(false);
        suppliersTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        suppliersTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        suppliersTable->setShowGrid(true);

        tableActionsLayout->addWidget(suppliersTable);

        actionsPanel = new QFrame(pageTable);
        actionsPanel->setObjectName("actionsPanel");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(actionsPanel->sizePolicy().hasHeightForWidth());
        actionsPanel->setSizePolicy(sizePolicy2);
        actionsPanel->setMinimumSize(QSize(200, 0));
        actionsPanel->setMaximumSize(QSize(220, 16777215));
        actionsPanel->setFrameShape(QFrame::Shape::StyledPanel);
        actionsPanel->setFrameShadow(QFrame::Shadow::Raised);
        actionsPanelLayout = new QVBoxLayout(actionsPanel);
        actionsPanelLayout->setSpacing(15);
        actionsPanelLayout->setObjectName("actionsPanelLayout");
        lblActions = new QLabel(actionsPanel);
        lblActions->setObjectName("lblActions");
        lblActions->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 0px;\n"
"}"));

        actionsPanelLayout->addWidget(lblActions);

        btnEditSupplier = new QPushButton(actionsPanel);
        btnEditSupplier->setObjectName("btnEditSupplier");
        btnEditSupplier->setMinimumSize(QSize(0, 45));
        btnEditSupplier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #00ff9c;\n"
"    font-weight: 500;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    border: 1px solid #33ffcc;\n"
"}"));

        actionsPanelLayout->addWidget(btnEditSupplier);

        btnDeleteSupplier = new QPushButton(actionsPanel);
        btnDeleteSupplier->setObjectName("btnDeleteSupplier");
        btnDeleteSupplier->setMinimumSize(QSize(0, 45));
        btnDeleteSupplier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid #ff6666;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #ff6666;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(255, 102, 102, 0.1);\n"
"}"));

        actionsPanelLayout->addWidget(btnDeleteSupplier);

        btnClearSelection = new QPushButton(actionsPanel);
        btnClearSelection->setObjectName("btnClearSelection");
        btnClearSelection->setMinimumSize(QSize(0, 45));
        btnClearSelection->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #00ff9c;\n"
"    font-weight: 500;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    border: 1px solid #33ffcc;\n"
"}"));

        actionsPanelLayout->addWidget(btnClearSelection);

        btnRateSupplier = new QPushButton(actionsPanel);
        btnRateSupplier->setObjectName("btnRateSupplier");
        btnRateSupplier->setMinimumSize(QSize(0, 45));
        btnRateSupplier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #00ff9c;\n"
"    font-weight: 500;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    border: 1px solid #33ffcc;\n"
"}"));

        actionsPanelLayout->addWidget(btnRateSupplier);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        actionsPanelLayout->addItem(verticalSpacer_3);

        btnExportPDF = new QPushButton(actionsPanel);
        btnExportPDF->setObjectName("btnExportPDF");
        btnExportPDF->setMinimumSize(QSize(0, 45));
        btnExportPDF->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #00ff9c;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #050d0a;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #33ffcc;\n"
"}"));

        actionsPanelLayout->addWidget(btnExportPDF);


        tableActionsLayout->addWidget(actionsPanel);


        pageTableLayout->addLayout(tableActionsLayout);

        stackedWidget->addWidget(pageTable);
        pageForm = new QWidget();
        pageForm->setObjectName("pageForm");
        pageFormLayout = new QVBoxLayout(pageForm);
        pageFormLayout->setSpacing(0);
        pageFormLayout->setObjectName("pageFormLayout");
        pageFormLayout->setContentsMargins(0, 0, 0, 0);
        formPanel = new QFrame(pageForm);
        formPanel->setObjectName("formPanel");
        formPanel->setFrameShape(QFrame::Shape::StyledPanel);
        formPanel->setFrameShadow(QFrame::Shadow::Raised);
        formPanelLayout = new QVBoxLayout(formPanel);
        formPanelLayout->setSpacing(20);
        formPanelLayout->setObjectName("formPanelLayout");
        formPanelLayout->setContentsMargins(30, 25, 30, 25);
        lblFormTitle = new QLabel(formPanel);
        lblFormTitle->setObjectName("lblFormTitle");
        lblFormTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 18px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        formPanelLayout->addWidget(lblFormTitle);

        formRow1 = new QHBoxLayout();
        formRow1->setSpacing(20);
        formRow1->setObjectName("formRow1");
        colId = new QVBoxLayout();
        colId->setSpacing(6);
        colId->setObjectName("colId");
        lblId = new QLabel(formPanel);
        lblId->setObjectName("lblId");
        lblId->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 12px;\n"
"    font-weight: 600;\n"
"    color: #00ff9c;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        colId->addWidget(lblId);

        lineEdit_id = new QLineEdit(formPanel);
        lineEdit_id->setObjectName("lineEdit_id");
        lineEdit_id->setMinimumSize(QSize(0, 42));
        lineEdit_id->setReadOnly(true);

        colId->addWidget(lineEdit_id);


        formRow1->addLayout(colId);

        colName = new QVBoxLayout();
        colName->setSpacing(6);
        colName->setObjectName("colName");
        lblName = new QLabel(formPanel);
        lblName->setObjectName("lblName");
        lblName->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 12px;\n"
"    font-weight: 600;\n"
"    color: #00ff9c;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        colName->addWidget(lblName);

        lineEdit_name = new QLineEdit(formPanel);
        lineEdit_name->setObjectName("lineEdit_name");
        lineEdit_name->setMinimumSize(QSize(0, 42));

        colName->addWidget(lineEdit_name);


        formRow1->addLayout(colName);


        formPanelLayout->addLayout(formRow1);

        formRow2 = new QHBoxLayout();
        formRow2->setSpacing(20);
        formRow2->setObjectName("formRow2");
        colEmail = new QVBoxLayout();
        colEmail->setSpacing(6);
        colEmail->setObjectName("colEmail");
        lblEmail = new QLabel(formPanel);
        lblEmail->setObjectName("lblEmail");
        lblEmail->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 12px;\n"
"    font-weight: 600;\n"
"    color: #00ff9c;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        colEmail->addWidget(lblEmail);

        lineEdit_email = new QLineEdit(formPanel);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setMinimumSize(QSize(0, 42));

        colEmail->addWidget(lineEdit_email);


        formRow2->addLayout(colEmail);

        colPhone = new QVBoxLayout();
        colPhone->setSpacing(6);
        colPhone->setObjectName("colPhone");
        lblPhone = new QLabel(formPanel);
        lblPhone->setObjectName("lblPhone");
        lblPhone->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 12px;\n"
"    font-weight: 600;\n"
"    color: #00ff9c;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        colPhone->addWidget(lblPhone);

        lineEdit_phone = new QLineEdit(formPanel);
        lineEdit_phone->setObjectName("lineEdit_phone");
        lineEdit_phone->setMinimumSize(QSize(0, 42));

        colPhone->addWidget(lineEdit_phone);


        formRow2->addLayout(colPhone);


        formPanelLayout->addLayout(formRow2);

        formRow3 = new QHBoxLayout();
        formRow3->setSpacing(20);
        formRow3->setObjectName("formRow3");
        colProduct = new QVBoxLayout();
        colProduct->setSpacing(6);
        colProduct->setObjectName("colProduct");
        lblProduct = new QLabel(formPanel);
        lblProduct->setObjectName("lblProduct");
        lblProduct->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 12px;\n"
"    font-weight: 600;\n"
"    color: #00ff9c;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        colProduct->addWidget(lblProduct);

        lineEdit_product = new QLineEdit(formPanel);
        lineEdit_product->setObjectName("lineEdit_product");
        lineEdit_product->setMinimumSize(QSize(0, 42));

        colProduct->addWidget(lineEdit_product);


        formRow3->addLayout(colProduct);

        colContract = new QVBoxLayout();
        colContract->setSpacing(6);
        colContract->setObjectName("colContract");
        lblContract = new QLabel(formPanel);
        lblContract->setObjectName("lblContract");
        lblContract->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 12px;\n"
"    font-weight: 600;\n"
"    color: #00ff9c;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        colContract->addWidget(lblContract);

        lineEdit_contract = new QLineEdit(formPanel);
        lineEdit_contract->setObjectName("lineEdit_contract");
        lineEdit_contract->setMinimumSize(QSize(0, 42));

        colContract->addWidget(lineEdit_contract);


        formRow3->addLayout(colContract);


        formPanelLayout->addLayout(formRow3);

        formRow4 = new QHBoxLayout();
        formRow4->setSpacing(20);
        formRow4->setObjectName("formRow4");
        colDate = new QVBoxLayout();
        colDate->setSpacing(6);
        colDate->setObjectName("colDate");
        lblDate = new QLabel(formPanel);
        lblDate->setObjectName("lblDate");
        lblDate->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 12px;\n"
"    font-weight: 600;\n"
"    color: #00ff9c;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        colDate->addWidget(lblDate);

        dateEdit_date = new QDateEdit(formPanel);
        dateEdit_date->setObjectName("dateEdit_date");
        dateEdit_date->setMinimumSize(QSize(0, 42));
        dateEdit_date->setCalendarPopup(true);

        colDate->addWidget(dateEdit_date);


        formRow4->addLayout(colDate);

        colRating = new QVBoxLayout();
        colRating->setSpacing(6);
        colRating->setObjectName("colRating");
        lblRating = new QLabel(formPanel);
        lblRating->setObjectName("lblRating");
        lblRating->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 12px;\n"
"    font-weight: 600;\n"
"    color: #00ff9c;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        colRating->addWidget(lblRating);

        lineEdit_rating = new QLineEdit(formPanel);
        lineEdit_rating->setObjectName("lineEdit_rating");
        lineEdit_rating->setMinimumSize(QSize(0, 42));

        colRating->addWidget(lineEdit_rating);


        formRow4->addLayout(colRating);


        formPanelLayout->addLayout(formRow4);

        formRow5 = new QHBoxLayout();
        formRow5->setSpacing(20);
        formRow5->setObjectName("formRow5");
        colEndDate = new QVBoxLayout();
        colEndDate->setSpacing(6);
        colEndDate->setObjectName("colEndDate");
        lblEndDate = new QLabel(formPanel);
        lblEndDate->setObjectName("lblEndDate");
        lblEndDate->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                  font-size: 12px;\n"
"                  font-weight: 600;\n"
"                  color: #00ff9c;\n"
"                  background: transparent;\n"
"                  border: none;\n"
"              }"));

        colEndDate->addWidget(lblEndDate);

        dateEdit_endDate = new QDateEdit(formPanel);
        dateEdit_endDate->setObjectName("dateEdit_endDate");
        dateEdit_endDate->setMinimumSize(QSize(0, 42));
        dateEdit_endDate->setCalendarPopup(true);

        colEndDate->addWidget(dateEdit_endDate);


        formRow5->addLayout(colEndDate);

        horizontalSpacer_endDate = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formRow5->addItem(horizontalSpacer_endDate);


        formPanelLayout->addLayout(formRow5);

        verticalSpacer_form = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formPanelLayout->addItem(verticalSpacer_form);

        formButtonsLayout = new QHBoxLayout();
        formButtonsLayout->setSpacing(15);
        formButtonsLayout->setObjectName("formButtonsLayout");
        horizontalSpacer_form = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formButtonsLayout->addItem(horizontalSpacer_form);

        btnCancelForm = new QPushButton(formPanel);
        btnCancelForm->setObjectName("btnCancelForm");
        btnCancelForm->setMinimumSize(QSize(140, 45));
        btnCancelForm->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 20px;\n"
"    color: #00ff9c;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"}"));

        formButtonsLayout->addWidget(btnCancelForm);

        btnSaveSupplier = new QPushButton(formPanel);
        btnSaveSupplier->setObjectName("btnSaveSupplier");
        btnSaveSupplier->setMinimumSize(QSize(160, 45));
        btnSaveSupplier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #00ff9c;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 20px;\n"
"    color: #050d0a;\n"
"    font-weight: 700;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #33ffcc;\n"
"    border: 1px solid #33ffcc;\n"
"}"));

        formButtonsLayout->addWidget(btnSaveSupplier);


        formPanelLayout->addLayout(formButtonsLayout);


        pageFormLayout->addWidget(formPanel);

        stackedWidget->addWidget(pageForm);

        mainContentLayout->addWidget(stackedWidget);


        mainHorizontalLayout->addWidget(mainContentWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Supplier Management", nullptr));
        sidebarGroup->setTitle(QString());
        sidebarLogo->setText(QString());
        btnDashboard->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        btnReports->setText(QCoreApplication::translate("MainWindow", "Employee Management", nullptr));
        btnCustomers->setText(QCoreApplication::translate("MainWindow", "Customer Management", nullptr));
        btnOrders->setText(QCoreApplication::translate("MainWindow", "Waste Management", nullptr));
        btnInventory->setText(QCoreApplication::translate("MainWindow", "Vehicle Management", nullptr));
        btnMachines->setText(QCoreApplication::translate("MainWindow", "Machines Management", nullptr));
        btnSuppliers->setText(QCoreApplication::translate("MainWindow", "Supplier Management", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "Log Out \360\237\232\252", nullptr));
        pageTitle->setText(QCoreApplication::translate("MainWindow", "Suppliers", nullptr));
        pageSubtitle->setText(QCoreApplication::translate("MainWindow", "Create, edit, search, sort, export, and analyze suppliers.", nullptr));
        btnViewSuppliers->setText(QCoreApplication::translate("MainWindow", "View Suppliers", nullptr));
        btnAddSupplier->setText(QCoreApplication::translate("MainWindow", "Add Supplier", nullptr));
        btnSupplierStats->setText(QCoreApplication::translate("MainWindow", "Supplier Performance", nullptr));
        lblSuppliersList->setText(QCoreApplication::translate("MainWindow", "Suppliers List", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search by ID / Name / Phone...", nullptr));
        sortComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Sort: Name (A-Z)", nullptr));
        sortComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Sort: Name (Z-A)", nullptr));
        sortComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Sort: Rating (High-Low)", nullptr));
        sortComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Sort: Date (Newest)", nullptr));

        lblActions->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        btnEditSupplier->setText(QCoreApplication::translate("MainWindow", "Edit Supplier", nullptr));
        btnDeleteSupplier->setText(QCoreApplication::translate("MainWindow", "Delete Supplier", nullptr));
        btnClearSelection->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        btnRateSupplier->setText(QCoreApplication::translate("MainWindow", "Rate Supplier", nullptr));
        btnExportPDF->setText(QCoreApplication::translate("MainWindow", "Export PDF", nullptr));
        lblFormTitle->setText(QCoreApplication::translate("MainWindow", "Supplier Form", nullptr));
        lblId->setText(QCoreApplication::translate("MainWindow", "Supplier ID", nullptr));
        lineEdit_id->setPlaceholderText(QCoreApplication::translate("MainWindow", "Auto-generated", nullptr));
        lblName->setText(QCoreApplication::translate("MainWindow", "Full Name", nullptr));
        lineEdit_name->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter supplier name...", nullptr));
        lblEmail->setText(QCoreApplication::translate("MainWindow", "Email Address", nullptr));
        lineEdit_email->setPlaceholderText(QCoreApplication::translate("MainWindow", "supplier@example.com", nullptr));
        lblPhone->setText(QCoreApplication::translate("MainWindow", "Phone Number", nullptr));
        lineEdit_phone->setPlaceholderText(QCoreApplication::translate("MainWindow", "+1 234 567 890", nullptr));
        lblProduct->setText(QCoreApplication::translate("MainWindow", "Product Type", nullptr));
        lineEdit_product->setPlaceholderText(QCoreApplication::translate("MainWindow", "e.g. Electronics, Raw Materials...", nullptr));
        lblContract->setText(QCoreApplication::translate("MainWindow", "Contract", nullptr));
        lineEdit_contract->setPlaceholderText(QCoreApplication::translate("MainWindow", "Contract reference or type...", nullptr));
        lblDate->setText(QCoreApplication::translate("MainWindow", "Contract Date", nullptr));
        dateEdit_date->setDisplayFormat(QCoreApplication::translate("MainWindow", "dd/MM/yyyy", nullptr));
        lblRating->setText(QCoreApplication::translate("MainWindow", "Rating (0\342\200\2235)", nullptr));
        lineEdit_rating->setPlaceholderText(QCoreApplication::translate("MainWindow", "e.g. 4.5", nullptr));
        lblEndDate->setText(QCoreApplication::translate("MainWindow", "Contract End Date", nullptr));
        dateEdit_endDate->setDisplayFormat(QCoreApplication::translate("MainWindow", "dd/MM/yyyy", nullptr));
        btnCancelForm->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        btnSaveSupplier->setText(QCoreApplication::translate("MainWindow", "Save Supplier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
