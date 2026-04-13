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
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedwidget;
    QWidget *vehiclePage;
    QGroupBox *sidebarGroup_3;
    QVBoxLayout *sidebarLayout_3;
    QHBoxLayout *logoContainerLayout_3;
    QSpacerItem *horizontalSpacer_logoLeft_3;
    QSpacerItem *horizontalSpacer_logoRight_3;
    QLabel *sidebarLogo_6;
    QPushButton *btnDashboard_2;
    QPushButton *btnEmployee_2;
    QPushButton *btnCustomer_2;
    QPushButton *btnWaste_2;
    QPushButton *btnVehicle_2;
    QPushButton *btnMachines_2;
    QPushButton *btnSupplier_2;
    QSpacerItem *verticalSpacer_5;
    QPushButton *btnLogout_2;
    QWidget *mainContentWidget_2;
    QVBoxLayout *mainContentLayout_2;
    QHBoxLayout *headerLayout_2;
    QVBoxLayout *titleLayout_2;
    QLabel *pageTitle_2;
    QLabel *pageSubtitle_2;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *topActionsLayout_2;
    QPushButton *btnViewVehicles;
    QPushButton *btnAddVehicle;
    QPushButton *btnCalendar;
    QPushButton *statistic_btn;
    QSpacerItem *horizontalSpacer_4;
    QWidget *searchFilterWidget_2;
    QVBoxLayout *searchFilterLayout_2;
    QLabel *lblVehiclesList;
    QHBoxLayout *searchLayout_2;
    QLineEdit *searchBox_2;
    QComboBox *sortComboBox_2;
    QHBoxLayout *tableActionsLayout_2;
    QTableWidget *vehiclesTable;
    QFrame *actionsPanel_2;
    QVBoxLayout *actionsPanelLayout_2;
    QLabel *lblActions_2;
    QPushButton *btnEditVehicle;
    QPushButton *btnDeleteVehicle;
    QPushButton *btnChatbot;
    QPushButton *btnClearSelection_2;
    QSpacerItem *verticalSpacer_6;
    QPushButton *btnExportPDF_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1362, 756);
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
"/* ===== Login/Auth Pages ===== */\n"
"QLabel#authTitle {\n"
"    font-size: 28px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
""
                        "    border: none;\n"
"}\n"
"\n"
"QLabel#authSubtitle {\n"
"    font-size: 14px;\n"
"    font-weight: 400;\n"
"    color: #66ffcc;\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"QLabel#authLogo {\n"
"    background: transparent;\n"
"    border: none;\n"
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
"/* ===== Buttons ===== */\n"
"QPushButton {\n"
"    background-color: #0a1f18;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"    color: #66ffcc;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"    border: 1px solid #33ffcc;\n"
"}\n"
"\n"
"QPushButton:pres"
                        "sed {\n"
"    background-color: #05140f;\n"
"}\n"
"\n"
"QPushButton#primaryBtn {\n"
"    background-color: #00ff9c;\n"
"    border: 1px solid #00ff9c;\n"
"    color: #050d0a;\n"
"}\n"
"\n"
"QPushButton#primaryBtn:hover {\n"
"    background-color: #33ffcc;\n"
"}\n"
"\n"
"QPushButton#linkBtn {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    color: #00ff9c;\n"
"    text-decoration: underline;\n"
"}\n"
"\n"
"QPushButton#linkBtn:hover {\n"
"    color: #33ffcc;\n"
"}\n"
"\n"
"/* ===== Inputs ===== */\n"
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
"    padding: 10px"
                        " 15px;\n"
"    color: #66ffcc;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    border: 1px solid #33ffcc;\n"
"}\n"
"\n"
"/* ===== Table ===== */\n"
"QTableWidget {\n"
"    background-color: #081713;\n"
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
"/* ===== Actions Panel ===== */\n"
"QFrame#actionsPanel {\n"
"    background-color: #081713;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QLabel#act"
                        "ionsPanelTitle {\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"QPushButton#actionBtn {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #00ff9c;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton#actionBtn:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
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
"    font-weigh"
                        "t: 600;\n"
"}\n"
"\n"
"QPushButton#actionBtnExport:hover {\n"
"    background-color: #33ffcc;\n"
"}\n"
"\n"
"/* ===== Main Menu Cards ===== */\n"
"QPushButton#menuCard {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #0a1f18, stop:1 #081713);\n"
"    border: 2px solid #00ff9c;\n"
"    border-radius: 12px;\n"
"    padding: 30px 20px;\n"
"    color: #ffffff;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QPushButton#menuCard:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #10352a, stop:1 #0a1f18);\n"
"    border: 2px solid #33ffcc;\n"
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
""
                        "/* ===== Status Bar ===== */\n"
"QStatusBar {\n"
"    background-color: #0a1f18;\n"
"    color: #66ffcc;\n"
"    border-top: 1px solid #00ff9c;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedwidget = new QStackedWidget(centralwidget);
        stackedwidget->setObjectName("stackedwidget");
        stackedwidget->setGeometry(QRect(10, 10, 1357, 711));
        vehiclePage = new QWidget();
        vehiclePage->setObjectName("vehiclePage");
        sidebarGroup_3 = new QGroupBox(vehiclePage);
        sidebarGroup_3->setObjectName("sidebarGroup_3");
        sidebarGroup_3->setGeometry(QRect(0, 0, 250, 721));
        sidebarGroup_3->setMinimumSize(QSize(250, 0));
        sidebarGroup_3->setMaximumSize(QSize(250, 16777215));
        sidebarLayout_3 = new QVBoxLayout(sidebarGroup_3);
        sidebarLayout_3->setSpacing(0);
        sidebarLayout_3->setObjectName("sidebarLayout_3");
        sidebarLayout_3->setContentsMargins(0, 0, 0, 0);
        logoContainerLayout_3 = new QHBoxLayout();
        logoContainerLayout_3->setObjectName("logoContainerLayout_3");
        horizontalSpacer_logoLeft_3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoContainerLayout_3->addItem(horizontalSpacer_logoLeft_3);

        horizontalSpacer_logoRight_3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoContainerLayout_3->addItem(horizontalSpacer_logoRight_3);


        sidebarLayout_3->addLayout(logoContainerLayout_3);

        sidebarLogo_6 = new QLabel(sidebarGroup_3);
        sidebarLogo_6->setObjectName("sidebarLogo_6");
        sidebarLogo_6->setMinimumSize(QSize(0, 100));
        sidebarLogo_6->setMaximumSize(QSize(16777215, 100));
        sidebarLogo_6->setPixmap(QPixmap(QString::fromUtf8(":/image/image/images/logo.png")));
        sidebarLogo_6->setScaledContents(false);
        sidebarLogo_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarLayout_3->addWidget(sidebarLogo_6);

        btnDashboard_2 = new QPushButton(sidebarGroup_3);
        btnDashboard_2->setObjectName("btnDashboard_2");
        btnDashboard_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_3->addWidget(btnDashboard_2);

        btnEmployee_2 = new QPushButton(sidebarGroup_3);
        btnEmployee_2->setObjectName("btnEmployee_2");
        btnEmployee_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_3->addWidget(btnEmployee_2);

        btnCustomer_2 = new QPushButton(sidebarGroup_3);
        btnCustomer_2->setObjectName("btnCustomer_2");
        btnCustomer_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_3->addWidget(btnCustomer_2);

        btnWaste_2 = new QPushButton(sidebarGroup_3);
        btnWaste_2->setObjectName("btnWaste_2");
        btnWaste_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_3->addWidget(btnWaste_2);

        btnVehicle_2 = new QPushButton(sidebarGroup_3);
        btnVehicle_2->setObjectName("btnVehicle_2");
        btnVehicle_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_3->addWidget(btnVehicle_2);

        btnMachines_2 = new QPushButton(sidebarGroup_3);
        btnMachines_2->setObjectName("btnMachines_2");
        btnMachines_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_3->addWidget(btnMachines_2);

        btnSupplier_2 = new QPushButton(sidebarGroup_3);
        btnSupplier_2->setObjectName("btnSupplier_2");
        btnSupplier_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_3->addWidget(btnSupplier_2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout_3->addItem(verticalSpacer_5);

        btnLogout_2 = new QPushButton(sidebarGroup_3);
        btnLogout_2->setObjectName("btnLogout_2");
        btnLogout_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_3->addWidget(btnLogout_2);

        mainContentWidget_2 = new QWidget(vehiclePage);
        mainContentWidget_2->setObjectName("mainContentWidget_2");
        mainContentWidget_2->setGeometry(QRect(250, 7, 1107, 711));
        mainContentLayout_2 = new QVBoxLayout(mainContentWidget_2);
        mainContentLayout_2->setSpacing(20);
        mainContentLayout_2->setObjectName("mainContentLayout_2");
        mainContentLayout_2->setContentsMargins(30, 30, 30, 30);
        headerLayout_2 = new QHBoxLayout();
        headerLayout_2->setObjectName("headerLayout_2");
        titleLayout_2 = new QVBoxLayout();
        titleLayout_2->setSpacing(5);
        titleLayout_2->setObjectName("titleLayout_2");
        pageTitle_2 = new QLabel(mainContentWidget_2);
        pageTitle_2->setObjectName("pageTitle_2");
        pageTitle_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 28px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        titleLayout_2->addWidget(pageTitle_2);

        pageSubtitle_2 = new QLabel(mainContentWidget_2);
        pageSubtitle_2->setObjectName("pageSubtitle_2");
        pageSubtitle_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 13px;\n"
"    font-weight: 400;\n"
"    color: #66ffcc;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        titleLayout_2->addWidget(pageSubtitle_2);


        headerLayout_2->addLayout(titleLayout_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout_2->addItem(horizontalSpacer_3);


        mainContentLayout_2->addLayout(headerLayout_2);

        topActionsLayout_2 = new QHBoxLayout();
        topActionsLayout_2->setSpacing(10);
        topActionsLayout_2->setObjectName("topActionsLayout_2");
        btnViewVehicles = new QPushButton(mainContentWidget_2);
        btnViewVehicles->setObjectName("btnViewVehicles");
        btnViewVehicles->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0, 255, 156, 0.15);\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"    color: #00ff9c;\n"
"    font-weight: 600;\n"
"}"));

        topActionsLayout_2->addWidget(btnViewVehicles);

        btnAddVehicle = new QPushButton(mainContentWidget_2);
        btnAddVehicle->setObjectName("btnAddVehicle");
        btnAddVehicle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        topActionsLayout_2->addWidget(btnAddVehicle);

        btnCalendar = new QPushButton(mainContentWidget_2);
        btnCalendar->setObjectName("btnCalendar");
        btnCalendar->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        topActionsLayout_2->addWidget(btnCalendar);

        statistic_btn = new QPushButton(mainContentWidget_2);
        statistic_btn->setObjectName("statistic_btn");
        statistic_btn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        topActionsLayout_2->addWidget(statistic_btn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topActionsLayout_2->addItem(horizontalSpacer_4);


        mainContentLayout_2->addLayout(topActionsLayout_2);

        searchFilterWidget_2 = new QWidget(mainContentWidget_2);
        searchFilterWidget_2->setObjectName("searchFilterWidget_2");
        searchFilterLayout_2 = new QVBoxLayout(searchFilterWidget_2);
        searchFilterLayout_2->setSpacing(10);
        searchFilterLayout_2->setObjectName("searchFilterLayout_2");
        searchFilterLayout_2->setContentsMargins(0, 0, 0, 0);
        lblVehiclesList = new QLabel(searchFilterWidget_2);
        lblVehiclesList->setObjectName("lblVehiclesList");
        lblVehiclesList->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 5px 0px;\n"
"}"));

        searchFilterLayout_2->addWidget(lblVehiclesList);

        searchLayout_2 = new QHBoxLayout();
        searchLayout_2->setSpacing(10);
        searchLayout_2->setObjectName("searchLayout_2");
        searchBox_2 = new QLineEdit(searchFilterWidget_2);
        searchBox_2->setObjectName("searchBox_2");
        searchBox_2->setMinimumSize(QSize(0, 40));

        searchLayout_2->addWidget(searchBox_2);

        sortComboBox_2 = new QComboBox(searchFilterWidget_2);
        sortComboBox_2->addItem(QString());
        sortComboBox_2->addItem(QString());
        sortComboBox_2->addItem(QString());
        sortComboBox_2->addItem(QString());
        sortComboBox_2->setObjectName("sortComboBox_2");
        sortComboBox_2->setMinimumSize(QSize(200, 40));
        sortComboBox_2->setMaximumSize(QSize(250, 16777215));

        searchLayout_2->addWidget(sortComboBox_2);


        searchFilterLayout_2->addLayout(searchLayout_2);


        mainContentLayout_2->addWidget(searchFilterWidget_2);

        tableActionsLayout_2 = new QHBoxLayout();
        tableActionsLayout_2->setSpacing(20);
        tableActionsLayout_2->setObjectName("tableActionsLayout_2");
        vehiclesTable = new QTableWidget(mainContentWidget_2);
        if (vehiclesTable->columnCount() < 6)
            vehiclesTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        vehiclesTable->setObjectName("vehiclesTable");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(vehiclesTable->sizePolicy().hasHeightForWidth());
        vehiclesTable->setSizePolicy(sizePolicy);
        vehiclesTable->setMinimumSize(QSize(600, 0));
        vehiclesTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        vehiclesTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        tableActionsLayout_2->addWidget(vehiclesTable);

        actionsPanel_2 = new QFrame(mainContentWidget_2);
        actionsPanel_2->setObjectName("actionsPanel_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(actionsPanel_2->sizePolicy().hasHeightForWidth());
        actionsPanel_2->setSizePolicy(sizePolicy1);
        actionsPanel_2->setMinimumSize(QSize(200, 0));
        actionsPanel_2->setMaximumSize(QSize(220, 16777215));
        actionsPanel_2->setFrameShape(QFrame::Shape::StyledPanel);
        actionsPanel_2->setFrameShadow(QFrame::Shadow::Raised);
        actionsPanelLayout_2 = new QVBoxLayout(actionsPanel_2);
        actionsPanelLayout_2->setSpacing(15);
        actionsPanelLayout_2->setObjectName("actionsPanelLayout_2");
        lblActions_2 = new QLabel(actionsPanel_2);
        lblActions_2->setObjectName("lblActions_2");
        lblActions_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 0px;\n"
"}"));

        actionsPanelLayout_2->addWidget(lblActions_2);

        btnEditVehicle = new QPushButton(actionsPanel_2);
        btnEditVehicle->setObjectName("btnEditVehicle");
        btnEditVehicle->setMinimumSize(QSize(0, 45));
        btnEditVehicle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout_2->addWidget(btnEditVehicle);

        btnDeleteVehicle = new QPushButton(actionsPanel_2);
        btnDeleteVehicle->setObjectName("btnDeleteVehicle");
        btnDeleteVehicle->setMinimumSize(QSize(0, 45));
        btnDeleteVehicle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout_2->addWidget(btnDeleteVehicle);

        btnChatbot = new QPushButton(actionsPanel_2);
        btnChatbot->setObjectName("btnChatbot");
        btnChatbot->setMinimumSize(QSize(0, 45));
        btnChatbot->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout_2->addWidget(btnChatbot);

        btnClearSelection_2 = new QPushButton(actionsPanel_2);
        btnClearSelection_2->setObjectName("btnClearSelection_2");
        btnClearSelection_2->setMinimumSize(QSize(0, 45));
        btnClearSelection_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout_2->addWidget(btnClearSelection_2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        actionsPanelLayout_2->addItem(verticalSpacer_6);

        btnExportPDF_2 = new QPushButton(actionsPanel_2);
        btnExportPDF_2->setObjectName("btnExportPDF_2");
        btnExportPDF_2->setMinimumSize(QSize(0, 45));
        btnExportPDF_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout_2->addWidget(btnExportPDF_2);


        tableActionsLayout_2->addWidget(actionsPanel_2);


        mainContentLayout_2->addLayout(tableActionsLayout_2);

        stackedwidget->addWidget(vehiclePage);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedwidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        sidebarGroup_3->setTitle(QString());
        sidebarLogo_6->setText(QString());
        btnDashboard_2->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        btnEmployee_2->setText(QCoreApplication::translate("MainWindow", "Employee Management", nullptr));
        btnCustomer_2->setText(QCoreApplication::translate("MainWindow", "Customer Management", nullptr));
        btnWaste_2->setText(QCoreApplication::translate("MainWindow", "Waste Management", nullptr));
        btnVehicle_2->setText(QCoreApplication::translate("MainWindow", "Vehicle Management", nullptr));
        btnMachines_2->setText(QCoreApplication::translate("MainWindow", "Vehicles Management", nullptr));
        btnSupplier_2->setText(QCoreApplication::translate("MainWindow", "Supplier Management", nullptr));
        btnLogout_2->setText(QCoreApplication::translate("MainWindow", "Log Out \360\237\232\252", nullptr));
        pageTitle_2->setText(QCoreApplication::translate("MainWindow", "Vehicles", nullptr));
        pageSubtitle_2->setText(QCoreApplication::translate("MainWindow", "Manage fleet, track maintenance, and monitor vehicle status.", nullptr));
        btnViewVehicles->setText(QCoreApplication::translate("MainWindow", "View Vehicles", nullptr));
        btnAddVehicle->setText(QCoreApplication::translate("MainWindow", "Add Vehicle", nullptr));
        btnCalendar->setText(QCoreApplication::translate("MainWindow", "Maintenance Calendar", nullptr));
        statistic_btn->setText(QCoreApplication::translate("MainWindow", "vehicless statistic", nullptr));
        lblVehiclesList->setText(QCoreApplication::translate("MainWindow", "Vehicles List", nullptr));
        searchBox_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search by ID / Plate / Model...", nullptr));
        sortComboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Sort: ID", nullptr));
        sortComboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Sort: Model", nullptr));
        sortComboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Sort: Type", nullptr));
        sortComboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "Sort: Next Maintenance", nullptr));

        QTableWidgetItem *___qtablewidgetitem = vehiclesTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = vehiclesTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Num Plate", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = vehiclesTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = vehiclesTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Model", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = vehiclesTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = vehiclesTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Next Maintenance", nullptr));
        lblActions_2->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        btnEditVehicle->setText(QCoreApplication::translate("MainWindow", "Edit Vehicle", nullptr));
        btnDeleteVehicle->setText(QCoreApplication::translate("MainWindow", "Delete Vehicle", nullptr));
        btnChatbot->setText(QCoreApplication::translate("MainWindow", "AI Chatbot \360\237\244\226", nullptr));
        btnClearSelection_2->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        btnExportPDF_2->setText(QCoreApplication::translate("MainWindow", "Export PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
