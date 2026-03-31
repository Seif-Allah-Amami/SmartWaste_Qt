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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
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
    QLabel *sidebarTitle;
    QSpacerItem *verticalSpacer;
    QPushButton *btnDashboard;
    QPushButton *btnEmployee;
    QPushButton *btnCustomers;
    QPushButton *btnWaste;
    QPushButton *btnVehicle;
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
    QPushButton *btnViewMachines;
    QPushButton *btnAddMachine;
    QPushButton *btnMachinePerformance;
    QSpacerItem *horizontalSpacer_2;
    QWidget *searchFilterWidget;
    QVBoxLayout *searchFilterLayout;
    QLabel *lblMachinesList;
    QHBoxLayout *searchLayout;
    QLineEdit *searchBox;
    QComboBox *sortComboBox;
    QHBoxLayout *tableActionsLayout;
    QTableWidget *machinesTable;
    QFrame *actionsPanel;
    QVBoxLayout *actionsPanelLayout;
    QLabel *lblActions;
    QPushButton *btnEditMachine;
    QPushButton *btnDeleteMachine;
    QPushButton *btnAlertSystem;
    QPushButton *btnClearSelection;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btnExportPDF;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1357, 700);
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
"/* Sidebar Menu Buttons */\n"
"QPushButton#sidebarBtn {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 14px 20px;\n"
"    color: #66ffcc;\n"
"    text-align: left;\n"
"    font-si"
                        "ze: 14px;\n"
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
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton#logoutBtn:hover {\n"
"    background-color: rgba(255, 102, 102, 0.1);\n"
"}\n"
"\n"
"/* ===== Page Header ===== */\n"
"QLabel#pageTitle {\n"
"    font-si"
                        "ze: 28px;\n"
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
"/* ===== Top Action Buttons ===== */\n"
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
"    padding: 10px 20px;\n"
"    color: #050d0a;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton#topActionBtnPrimary:hover {\n"
"    background-color: #33ffcc;\n"
"    border: 1px solid #33ffcc;\n"
"}\n"
"\n"
"/* ===== Search"
                        " and Filter Area ===== */\n"
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
"QComboBox:hover {\n"
"    border: 1px solid #33ffcc;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    padding-right: 10px;\n"
"}\n"
"\n"
"/* ===== Table ===== */\n"
"QTableWidget {\n"
"    background-color: #0817"
                        "13;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    gridline-color: rgba(0, 255, 156, 0.2);\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 10px;\n"
"    color: #66ffcc;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
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
"QFrame#actionsPanel {\n"
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
"/* Action Butto"
                        "ns in Right Panel */\n"
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
"    background-color: rgba(255, 102, 102, 0.1);\n"
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
""
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
        sidebarLogo->setMinimumSize(QSize(200, 80));
        sidebarLogo->setMaximumSize(QSize(200, 80));
        sidebarLogo->setPixmap(QPixmap(QString::fromUtf8(":/image/images/logo.png")));
        sidebarLogo->setScaledContents(false);
        sidebarLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarLayout->addWidget(sidebarLogo);

        sidebarTitle = new QLabel(sidebarGroup);
        sidebarTitle->setObjectName("sidebarTitle");

        sidebarLayout->addWidget(sidebarTitle);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        sidebarLayout->addItem(verticalSpacer);

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

        btnEmployee = new QPushButton(sidebarGroup);
        btnEmployee->setObjectName("btnEmployee");
        btnEmployee->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnEmployee);

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

        btnWaste = new QPushButton(sidebarGroup);
        btnWaste->setObjectName("btnWaste");
        btnWaste->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnWaste);

        btnVehicle = new QPushButton(sidebarGroup);
        btnVehicle->setObjectName("btnVehicle");
        btnVehicle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnVehicle);

        btnMachines = new QPushButton(sidebarGroup);
        btnMachines->setObjectName("btnMachines");
        btnMachines->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnMachines);

        btnSuppliers = new QPushButton(sidebarGroup);
        btnSuppliers->setObjectName("btnSuppliers");
        btnSuppliers->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        btnViewMachines = new QPushButton(mainContentWidget);
        btnViewMachines->setObjectName("btnViewMachines");
        btnViewMachines->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0, 255, 156, 0.15);\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"    color: #00ff9c;\n"
"    font-weight: 600;\n"
"}"));

        topActionsLayout->addWidget(btnViewMachines);

        btnAddMachine = new QPushButton(mainContentWidget);
        btnAddMachine->setObjectName("btnAddMachine");
        btnAddMachine->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        topActionsLayout->addWidget(btnAddMachine);

        btnMachinePerformance = new QPushButton(mainContentWidget);
        btnMachinePerformance->setObjectName("btnMachinePerformance");
        btnMachinePerformance->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        topActionsLayout->addWidget(btnMachinePerformance);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topActionsLayout->addItem(horizontalSpacer_2);


        mainContentLayout->addLayout(topActionsLayout);

        searchFilterWidget = new QWidget(mainContentWidget);
        searchFilterWidget->setObjectName("searchFilterWidget");
        searchFilterLayout = new QVBoxLayout(searchFilterWidget);
        searchFilterLayout->setSpacing(10);
        searchFilterLayout->setObjectName("searchFilterLayout");
        searchFilterLayout->setContentsMargins(0, 0, 0, 0);
        lblMachinesList = new QLabel(searchFilterWidget);
        lblMachinesList->setObjectName("lblMachinesList");
        lblMachinesList->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 5px 0px;\n"
"}"));

        searchFilterLayout->addWidget(lblMachinesList);

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


        mainContentLayout->addWidget(searchFilterWidget);

        tableActionsLayout = new QHBoxLayout();
        tableActionsLayout->setSpacing(20);
        tableActionsLayout->setObjectName("tableActionsLayout");
        machinesTable = new QTableWidget(mainContentWidget);
        if (machinesTable->columnCount() < 6)
            machinesTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        machinesTable->setObjectName("machinesTable");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(machinesTable->sizePolicy().hasHeightForWidth());
        machinesTable->setSizePolicy(sizePolicy1);
        machinesTable->setMinimumSize(QSize(600, 0));
        machinesTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        machinesTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        tableActionsLayout->addWidget(machinesTable);

        actionsPanel = new QFrame(mainContentWidget);
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

        btnEditMachine = new QPushButton(actionsPanel);
        btnEditMachine->setObjectName("btnEditMachine");
        btnEditMachine->setMinimumSize(QSize(0, 45));
        btnEditMachine->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout->addWidget(btnEditMachine);

        btnDeleteMachine = new QPushButton(actionsPanel);
        btnDeleteMachine->setObjectName("btnDeleteMachine");
        btnDeleteMachine->setMinimumSize(QSize(0, 45));
        btnDeleteMachine->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout->addWidget(btnDeleteMachine);

        btnAlertSystem = new QPushButton(actionsPanel);
        btnAlertSystem->setObjectName("btnAlertSystem");
        btnAlertSystem->setMinimumSize(QSize(0, 45));
        btnAlertSystem->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout->addWidget(btnAlertSystem);

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


        mainContentLayout->addLayout(tableActionsLayout);


        mainHorizontalLayout->addWidget(mainContentWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Machines Management", nullptr));
        sidebarGroup->setTitle(QString());
        sidebarLogo->setText(QString());
        sidebarTitle->setText(QCoreApplication::translate("MainWindow", "ReGen", nullptr));
        btnDashboard->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        btnEmployee->setText(QCoreApplication::translate("MainWindow", "Employee Management", nullptr));
        btnCustomers->setText(QCoreApplication::translate("MainWindow", "Customer Management", nullptr));
        btnWaste->setText(QCoreApplication::translate("MainWindow", "Waste Management", nullptr));
        btnVehicle->setText(QCoreApplication::translate("MainWindow", "Vehicle Management", nullptr));
        btnMachines->setText(QCoreApplication::translate("MainWindow", "Machines Management", nullptr));
        btnSuppliers->setText(QCoreApplication::translate("MainWindow", "Supplier Management", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "Log Out \360\237\232\252", nullptr));
        pageTitle->setText(QCoreApplication::translate("MainWindow", "Machines", nullptr));
        pageSubtitle->setText(QCoreApplication::translate("MainWindow", "Create, edit, search, sort, export, and analyze machines.", nullptr));
        btnViewMachines->setText(QCoreApplication::translate("MainWindow", "View Machines", nullptr));
        btnAddMachine->setText(QCoreApplication::translate("MainWindow", "Add Machine", nullptr));
        btnMachinePerformance->setText(QCoreApplication::translate("MainWindow", "Machine Performance", nullptr));
        lblMachinesList->setText(QCoreApplication::translate("MainWindow", "Machines List", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search by ID / Name / Type...", nullptr));
        sortComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Sort: Name (A-Z)", nullptr));
        sortComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Sort: Type", nullptr));
        sortComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Sort: Status", nullptr));
        sortComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Sort: Date (Newest)", nullptr));

        QTableWidgetItem *___qtablewidgetitem = machinesTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = machinesTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = machinesTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = machinesTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = machinesTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = machinesTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Purchase Date", nullptr));
        lblActions->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        btnEditMachine->setText(QCoreApplication::translate("MainWindow", "Edit Machine", nullptr));
        btnDeleteMachine->setText(QCoreApplication::translate("MainWindow", "Delete Machine", nullptr));
        btnAlertSystem->setText(QCoreApplication::translate("MainWindow", "Alert System", nullptr));
        btnClearSelection->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        btnExportPDF->setText(QCoreApplication::translate("MainWindow", "Export PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
