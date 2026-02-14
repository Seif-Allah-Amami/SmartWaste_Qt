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
#include <QtWidgets/QGridLayout>
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
    QWidget *connection;
    QVBoxLayout *loginLayout;
    QSpacerItem *verticalSpacer_login1;
    QHBoxLayout *loginCenterLayout;
    QSpacerItem *horizontalSpacer_login1;
    QFrame *loginFrame;
    QVBoxLayout *loginFormLayout;
    QHBoxLayout *logoContainerLayout;
    QSpacerItem *horizontalSpacer_logoLeft;
    QLabel *loginLogo;
    QSpacerItem *horizontalSpacer_logoRight;
    QLabel *loginTitle;
    QLabel *loginSubtitle;
    QSpacerItem *verticalSpacer_login2;
    QLineEdit *loginUsername;
    QLineEdit *loginPassword;
    QPushButton *btnLogin;
    QPushButton *btnForgotPassword;
    QSpacerItem *horizontalSpacer_login2;
    QSpacerItem *verticalSpacer_login3;
    QWidget *recoverpwd;
    QVBoxLayout *recoveryLayout;
    QSpacerItem *verticalSpacer_recovery1;
    QHBoxLayout *recoveryCenterLayout;
    QSpacerItem *horizontalSpacer_recovery1;
    QFrame *recoveryFrame;
    QVBoxLayout *recoveryFormLayout;
    QLabel *recoveryLogo;
    QLabel *recoveryTitle;
    QLabel *recoverySubtitle;
    QSpacerItem *verticalSpacer_recovery2;
    QLineEdit *recoveryEmail;
    QPushButton *btnRecoveryContinue;
    QPushButton *btnRecoveryCancel;
    QSpacerItem *horizontalSpacer_recovery2;
    QSpacerItem *verticalSpacer_recovery3;
    QWidget *verification;
    QVBoxLayout *verificationLayout;
    QSpacerItem *verticalSpacer_verify1;
    QHBoxLayout *verifyCenterLayout;
    QSpacerItem *horizontalSpacer_verify1;
    QFrame *verificationFrame;
    QVBoxLayout *verifyFormLayout;
    QLabel *verifyLogo;
    QLabel *verifyTitle;
    QLabel *verifySubtitle;
    QSpacerItem *verticalSpacer_verify2;
    QLineEdit *verifyCode;
    QPushButton *btnVerifyCheck;
    QPushButton *btnVerifyCancel;
    QSpacerItem *horizontalSpacer_verify2;
    QSpacerItem *verticalSpacer_verify3;
    QWidget *main;
    QVBoxLayout *mainMenuLayout;
    QLabel *mainMenuTitle;
    QLabel *mainMenuSubtitle;
    QGridLayout *mainMenuGrid;
    QPushButton *btnMenuEmployee;
    QPushButton *btnMenuCustomer;
    QPushButton *btnMenuWaste;
    QPushButton *btnMenuVehicle;
    QPushButton *btnMenuMachines;
    QPushButton *btnMenuSupplier;
    QSpacerItem *verticalSpacer_mainMenu;
    QWidget *employe;
    QHBoxLayout *employeeMainLayout;
    QGroupBox *sidebarGroup;
    QVBoxLayout *sidebarLayout;
    QHBoxLayout *empLogoContainerLayout;
    QSpacerItem *horizontalSpacer_empLogoLeft;
    QLabel *empSidebarLogo;
    QSpacerItem *horizontalSpacer_empLogoRight;
    QLabel *empSidebarTitle;
    QSpacerItem *verticalSpacer_empSidebar1;
    QPushButton *btnEmpDashboard;
    QPushButton *btnEmpEmployee;
    QPushButton *btnEmpCustomer;
    QPushButton *btnEmpWaste;
    QPushButton *btnEmpVehicle;
    QPushButton *btnEmpMachines;
    QPushButton *btnEmpSupplier;
    QSpacerItem *verticalSpacer_empSidebar2;
    QPushButton *btnEmpLogout;
    QWidget *empMainContent;
    QVBoxLayout *empContentLayout;
    QHBoxLayout *empHeaderLayout;
    QVBoxLayout *empTitleLayout;
    QLabel *empPageTitle;
    QLabel *empPageSubtitle;
    QSpacerItem *horizontalSpacer_empHeader;
    QHBoxLayout *empTopActionsLayout;
    QPushButton *btnEmpView;
    QPushButton *btnEmpAdd;
    QPushButton *btnEmpStats;
    QSpacerItem *horizontalSpacer_empTopActions;
    QWidget *empSearchWidget;
    QVBoxLayout *empSearchLayout;
    QLabel *lblEmpList;
    QHBoxLayout *empSearchInputLayout;
    QLineEdit *empSearchBox;
    QComboBox *empSortComboBox;
    QHBoxLayout *empTableActionsLayout;
    QTableWidget *empTable;
    QFrame *empActionsPanel;
    QVBoxLayout *empActionsPanelLayout;
    QLabel *lblEmpActions;
    QPushButton *btnEmpEdit;
    QPushButton *btnEmpDelete;
    QPushButton *btnEmpQRCode;
    QPushButton *btnEmpClear;
    QSpacerItem *verticalSpacer_empActions;
    QPushButton *btnEmpExport;
    QWidget *wastemanagement;
    QGroupBox *sidebarGroup_2;
    QVBoxLayout *sidebarLayout_2;
    QHBoxLayout *logoContainerLayout_2;
    QSpacerItem *horizontalSpacer_logoLeft_2;
    QLabel *sidebarLogo;
    QSpacerItem *horizontalSpacer_logoRight_2;
    QLabel *sidebarTitle;
    QSpacerItem *verticalSpacer;
    QPushButton *btnDashboard;
    QPushButton *btnEmployee;
    QPushButton *btnCustomer;
    QPushButton *btnWaste;
    QPushButton *btnVehicle;
    QPushButton *btnMachines;
    QPushButton *btnSupplier;
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
    QPushButton *btnViewWaste;
    QPushButton *btnAddWaste;
    QPushButton *btnWasteStats;
    QSpacerItem *horizontalSpacer_2;
    QWidget *searchFilterWidget;
    QVBoxLayout *searchFilterLayout;
    QLabel *lblWasteList;
    QHBoxLayout *searchLayout;
    QLineEdit *searchBox;
    QComboBox *sortComboBox;
    QHBoxLayout *tableActionsLayout;
    QTableWidget *wasteTable;
    QFrame *actionsPanel;
    QVBoxLayout *actionsPanelLayout;
    QLabel *lblActions;
    QPushButton *btnEditWaste;
    QPushButton *btnDeleteWaste;
    QPushButton *btnViewMaps;
    QPushButton *btnRate;
    QPushButton *btnClearSelection;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btnExportPDF;
    QWidget *vehiclePage;
    QGroupBox *sidebarGroup_3;
    QVBoxLayout *sidebarLayout_3;
    QHBoxLayout *logoContainerLayout_3;
    QSpacerItem *horizontalSpacer_logoLeft_3;
    QLabel *sidebarLogo_2;
    QSpacerItem *horizontalSpacer_logoRight_3;
    QLabel *sidebarTitle_2;
    QSpacerItem *verticalSpacer_4;
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
    QWidget *machinePage;
    QWidget *mainContentWidget_3;
    QVBoxLayout *mainContentLayout_3;
    QHBoxLayout *headerLayout_3;
    QVBoxLayout *titleLayout_3;
    QLabel *pageTitle_3;
    QLabel *pageSubtitle_3;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *topActionsLayout_3;
    QPushButton *btnViewMachines;
    QPushButton *btnAddMachine;
    QPushButton *btnMachinePerformance;
    QSpacerItem *horizontalSpacer_6;
    QWidget *searchFilterWidget_3;
    QVBoxLayout *searchFilterLayout_3;
    QLabel *lblMachinesList;
    QHBoxLayout *searchLayout_3;
    QLineEdit *searchBox_3;
    QComboBox *sortComboBox_3;
    QHBoxLayout *tableActionsLayout_3;
    QTableWidget *machinesTable;
    QFrame *actionsPanel_3;
    QVBoxLayout *actionsPanelLayout_3;
    QLabel *lblActions_3;
    QPushButton *btnEditMachine;
    QPushButton *btnDeleteMachine;
    QPushButton *btnAlertSystem;
    QPushButton *btnClearSelection_3;
    QSpacerItem *verticalSpacer_7;
    QPushButton *btnExportPDF_3;
    QGroupBox *sidebarGroup_4;
    QVBoxLayout *sidebarLayout_4;
    QLabel *sidebarLogo_3;
    QLabel *sidebarTitle_3;
    QSpacerItem *verticalSpacer_8;
    QPushButton *btnDashboard_3;
    QPushButton *btnEmployee_3;
    QPushButton *btnCustomers;
    QPushButton *btnWaste_3;
    QPushButton *btnVehicle_3;
    QPushButton *btnMachines_3;
    QPushButton *btnSuppliers;
    QSpacerItem *verticalSpacer_9;
    QPushButton *btnLogout_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1357, 740);
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
        stackedwidget->setGeometry(QRect(0, 0, 1357, 711));
        connection = new QWidget();
        connection->setObjectName("connection");
        loginLayout = new QVBoxLayout(connection);
        loginLayout->setObjectName("loginLayout");
        verticalSpacer_login1 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        loginLayout->addItem(verticalSpacer_login1);

        loginCenterLayout = new QHBoxLayout();
        loginCenterLayout->setObjectName("loginCenterLayout");
        horizontalSpacer_login1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        loginCenterLayout->addItem(horizontalSpacer_login1);

        loginFrame = new QFrame(connection);
        loginFrame->setObjectName("loginFrame");
        loginFrame->setMinimumSize(QSize(450, 550));
        loginFrame->setMaximumSize(QSize(450, 550));
        loginFrame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #081713;\n"
"    border: 2px solid #00ff9c;\n"
"    border-radius: 15px;\n"
"    padding: 30px;\n"
"}"));
        loginFormLayout = new QVBoxLayout(loginFrame);
        loginFormLayout->setSpacing(15);
        loginFormLayout->setObjectName("loginFormLayout");
        logoContainerLayout = new QHBoxLayout();
        logoContainerLayout->setObjectName("logoContainerLayout");
        horizontalSpacer_logoLeft = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoContainerLayout->addItem(horizontalSpacer_logoLeft);

        loginLogo = new QLabel(loginFrame);
        loginLogo->setObjectName("loginLogo");
        loginLogo->setMinimumSize(QSize(180, 90));
        loginLogo->setMaximumSize(QSize(180, 90));
        loginLogo->setPixmap(QPixmap(QString::fromUtf8(":/image/images/logo.png")));
        loginLogo->setScaledContents(false);
        loginLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        logoContainerLayout->addWidget(loginLogo);

        horizontalSpacer_logoRight = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoContainerLayout->addItem(horizontalSpacer_logoRight);


        loginFormLayout->addLayout(logoContainerLayout);

        loginTitle = new QLabel(loginFrame);
        loginTitle->setObjectName("loginTitle");
        loginTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 24px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 10px 0px;\n"
"}"));
        loginTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        loginFormLayout->addWidget(loginTitle);

        loginSubtitle = new QLabel(loginFrame);
        loginSubtitle->setObjectName("loginSubtitle");
        loginSubtitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 13px;\n"
"    color: #66ffcc;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 0px 20px 10px 20px;\n"
"}"));
        loginSubtitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        loginSubtitle->setWordWrap(true);

        loginFormLayout->addWidget(loginSubtitle);

        verticalSpacer_login2 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        loginFormLayout->addItem(verticalSpacer_login2);

        loginUsername = new QLineEdit(loginFrame);
        loginUsername->setObjectName("loginUsername");
        loginUsername->setMinimumSize(QSize(0, 45));

        loginFormLayout->addWidget(loginUsername);

        loginPassword = new QLineEdit(loginFrame);
        loginPassword->setObjectName("loginPassword");
        loginPassword->setMinimumSize(QSize(0, 45));
        loginPassword->setEchoMode(QLineEdit::EchoMode::Password);

        loginFormLayout->addWidget(loginPassword);

        btnLogin = new QPushButton(loginFrame);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setMinimumSize(QSize(0, 50));
        btnLogin->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #00ff9c;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 12px 20px;\n"
"    color: #050d0a;\n"
"    font-weight: 600;\n"
"    font-size: 15px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #33ffcc;\n"
"}"));

        loginFormLayout->addWidget(btnLogin);

        btnForgotPassword = new QPushButton(loginFrame);
        btnForgotPassword->setObjectName("btnForgotPassword");
        btnForgotPassword->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    color: #00ff9c;\n"
"    text-decoration: underline;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    color: #33ffcc;\n"
"}"));

        loginFormLayout->addWidget(btnForgotPassword);


        loginCenterLayout->addWidget(loginFrame);

        horizontalSpacer_login2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        loginCenterLayout->addItem(horizontalSpacer_login2);


        loginLayout->addLayout(loginCenterLayout);

        verticalSpacer_login3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        loginLayout->addItem(verticalSpacer_login3);

        stackedwidget->addWidget(connection);
        recoverpwd = new QWidget();
        recoverpwd->setObjectName("recoverpwd");
        recoveryLayout = new QVBoxLayout(recoverpwd);
        recoveryLayout->setObjectName("recoveryLayout");
        verticalSpacer_recovery1 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        recoveryLayout->addItem(verticalSpacer_recovery1);

        recoveryCenterLayout = new QHBoxLayout();
        recoveryCenterLayout->setObjectName("recoveryCenterLayout");
        horizontalSpacer_recovery1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        recoveryCenterLayout->addItem(horizontalSpacer_recovery1);

        recoveryFrame = new QFrame(recoverpwd);
        recoveryFrame->setObjectName("recoveryFrame");
        recoveryFrame->setMinimumSize(QSize(450, 500));
        recoveryFrame->setMaximumSize(QSize(450, 500));
        recoveryFrame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #081713;\n"
"    border: 2px solid #00ff9c;\n"
"    border-radius: 15px;\n"
"    padding: 30px;\n"
"}"));
        recoveryFormLayout = new QVBoxLayout(recoveryFrame);
        recoveryFormLayout->setSpacing(20);
        recoveryFormLayout->setObjectName("recoveryFormLayout");
        recoveryLogo = new QLabel(recoveryFrame);
        recoveryLogo->setObjectName("recoveryLogo");
        recoveryLogo->setMinimumSize(QSize(200, 100));
        recoveryLogo->setMaximumSize(QSize(200, 100));
        recoveryLogo->setPixmap(QPixmap(QString::fromUtf8(":/image/images/logo.png")));
        recoveryLogo->setScaledContents(false);
        recoveryLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        recoveryFormLayout->addWidget(recoveryLogo);

        recoveryTitle = new QLabel(recoveryFrame);
        recoveryTitle->setObjectName("recoveryTitle");
        recoveryTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 24px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        recoveryTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        recoveryFormLayout->addWidget(recoveryTitle);

        recoverySubtitle = new QLabel(recoveryFrame);
        recoverySubtitle->setObjectName("recoverySubtitle");
        recoverySubtitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 13px;\n"
"    color: #66ffcc;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        recoverySubtitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        recoverySubtitle->setWordWrap(true);

        recoveryFormLayout->addWidget(recoverySubtitle);

        verticalSpacer_recovery2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        recoveryFormLayout->addItem(verticalSpacer_recovery2);

        recoveryEmail = new QLineEdit(recoveryFrame);
        recoveryEmail->setObjectName("recoveryEmail");
        recoveryEmail->setMinimumSize(QSize(0, 45));

        recoveryFormLayout->addWidget(recoveryEmail);

        btnRecoveryContinue = new QPushButton(recoveryFrame);
        btnRecoveryContinue->setObjectName("btnRecoveryContinue");
        btnRecoveryContinue->setMinimumSize(QSize(0, 50));
        btnRecoveryContinue->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #00ff9c;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 12px 20px;\n"
"    color: #050d0a;\n"
"    font-weight: 600;\n"
"    font-size: 15px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #33ffcc;\n"
"}"));

        recoveryFormLayout->addWidget(btnRecoveryContinue);

        btnRecoveryCancel = new QPushButton(recoveryFrame);
        btnRecoveryCancel->setObjectName("btnRecoveryCancel");
        btnRecoveryCancel->setMinimumSize(QSize(0, 45));

        recoveryFormLayout->addWidget(btnRecoveryCancel);


        recoveryCenterLayout->addWidget(recoveryFrame);

        horizontalSpacer_recovery2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        recoveryCenterLayout->addItem(horizontalSpacer_recovery2);


        recoveryLayout->addLayout(recoveryCenterLayout);

        verticalSpacer_recovery3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        recoveryLayout->addItem(verticalSpacer_recovery3);

        stackedwidget->addWidget(recoverpwd);
        verification = new QWidget();
        verification->setObjectName("verification");
        verificationLayout = new QVBoxLayout(verification);
        verificationLayout->setObjectName("verificationLayout");
        verticalSpacer_verify1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verificationLayout->addItem(verticalSpacer_verify1);

        verifyCenterLayout = new QHBoxLayout();
        verifyCenterLayout->setObjectName("verifyCenterLayout");
        horizontalSpacer_verify1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        verifyCenterLayout->addItem(horizontalSpacer_verify1);

        verificationFrame = new QFrame(verification);
        verificationFrame->setObjectName("verificationFrame");
        verificationFrame->setMinimumSize(QSize(450, 500));
        verificationFrame->setMaximumSize(QSize(450, 500));
        verificationFrame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #081713;\n"
"    border: 2px solid #00ff9c;\n"
"    border-radius: 15px;\n"
"    padding: 30px;\n"
"}"));
        verifyFormLayout = new QVBoxLayout(verificationFrame);
        verifyFormLayout->setSpacing(20);
        verifyFormLayout->setObjectName("verifyFormLayout");
        verifyLogo = new QLabel(verificationFrame);
        verifyLogo->setObjectName("verifyLogo");
        verifyLogo->setMinimumSize(QSize(200, 100));
        verifyLogo->setMaximumSize(QSize(200, 100));
        verifyLogo->setPixmap(QPixmap(QString::fromUtf8(":/image/images/logo.png")));
        verifyLogo->setScaledContents(false);
        verifyLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verifyFormLayout->addWidget(verifyLogo);

        verifyTitle = new QLabel(verificationFrame);
        verifyTitle->setObjectName("verifyTitle");
        verifyTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 24px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        verifyTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verifyFormLayout->addWidget(verifyTitle);

        verifySubtitle = new QLabel(verificationFrame);
        verifySubtitle->setObjectName("verifySubtitle");
        verifySubtitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 13px;\n"
"    color: #66ffcc;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        verifySubtitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        verifySubtitle->setWordWrap(true);

        verifyFormLayout->addWidget(verifySubtitle);

        verticalSpacer_verify2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verifyFormLayout->addItem(verticalSpacer_verify2);

        verifyCode = new QLineEdit(verificationFrame);
        verifyCode->setObjectName("verifyCode");
        verifyCode->setMinimumSize(QSize(0, 45));

        verifyFormLayout->addWidget(verifyCode);

        btnVerifyCheck = new QPushButton(verificationFrame);
        btnVerifyCheck->setObjectName("btnVerifyCheck");
        btnVerifyCheck->setMinimumSize(QSize(0, 50));
        btnVerifyCheck->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #00ff9c;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 12px 20px;\n"
"    color: #050d0a;\n"
"    font-weight: 600;\n"
"    font-size: 15px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #33ffcc;\n"
"}"));

        verifyFormLayout->addWidget(btnVerifyCheck);

        btnVerifyCancel = new QPushButton(verificationFrame);
        btnVerifyCancel->setObjectName("btnVerifyCancel");
        btnVerifyCancel->setMinimumSize(QSize(0, 45));

        verifyFormLayout->addWidget(btnVerifyCancel);


        verifyCenterLayout->addWidget(verificationFrame);

        horizontalSpacer_verify2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        verifyCenterLayout->addItem(horizontalSpacer_verify2);


        verificationLayout->addLayout(verifyCenterLayout);

        verticalSpacer_verify3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verificationLayout->addItem(verticalSpacer_verify3);

        stackedwidget->addWidget(verification);
        main = new QWidget();
        main->setObjectName("main");
        mainMenuLayout = new QVBoxLayout(main);
        mainMenuLayout->setSpacing(30);
        mainMenuLayout->setObjectName("mainMenuLayout");
        mainMenuLayout->setContentsMargins(50, 50, 50, 50);
        mainMenuTitle = new QLabel(main);
        mainMenuTitle->setObjectName("mainMenuTitle");
        mainMenuTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 32px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        mainMenuTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        mainMenuLayout->addWidget(mainMenuTitle);

        mainMenuSubtitle = new QLabel(main);
        mainMenuSubtitle->setObjectName("mainMenuSubtitle");
        mainMenuSubtitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 15px;\n"
"    color: #66ffcc;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        mainMenuSubtitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        mainMenuLayout->addWidget(mainMenuSubtitle);

        mainMenuGrid = new QGridLayout();
        mainMenuGrid->setSpacing(20);
        mainMenuGrid->setObjectName("mainMenuGrid");
        btnMenuEmployee = new QPushButton(main);
        btnMenuEmployee->setObjectName("btnMenuEmployee");
        btnMenuEmployee->setMinimumSize(QSize(0, 120));
        btnMenuEmployee->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #0a1f18, stop:1 #081713);\n"
"    border: 2px solid #00ff9c;\n"
"    border-radius: 12px;\n"
"    padding: 30px 20px;\n"
"    color: #ffffff;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #10352a, stop:1 #0a1f18);\n"
"    border: 2px solid #33ffcc;\n"
"}"));

        mainMenuGrid->addWidget(btnMenuEmployee, 0, 0, 1, 1);

        btnMenuCustomer = new QPushButton(main);
        btnMenuCustomer->setObjectName("btnMenuCustomer");
        btnMenuCustomer->setMinimumSize(QSize(0, 120));
        btnMenuCustomer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #0a1f18, stop:1 #081713);\n"
"    border: 2px solid #00ff9c;\n"
"    border-radius: 12px;\n"
"    padding: 30px 20px;\n"
"    color: #ffffff;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #10352a, stop:1 #0a1f18);\n"
"    border: 2px solid #33ffcc;\n"
"}"));

        mainMenuGrid->addWidget(btnMenuCustomer, 0, 1, 1, 1);

        btnMenuWaste = new QPushButton(main);
        btnMenuWaste->setObjectName("btnMenuWaste");
        btnMenuWaste->setMinimumSize(QSize(0, 120));
        btnMenuWaste->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #0a1f18, stop:1 #081713);\n"
"    border: 2px solid #00ff9c;\n"
"    border-radius: 12px;\n"
"    padding: 30px 20px;\n"
"    color: #ffffff;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #10352a, stop:1 #0a1f18);\n"
"    border: 2px solid #33ffcc;\n"
"}"));

        mainMenuGrid->addWidget(btnMenuWaste, 0, 2, 1, 1);

        btnMenuVehicle = new QPushButton(main);
        btnMenuVehicle->setObjectName("btnMenuVehicle");
        btnMenuVehicle->setMinimumSize(QSize(0, 120));
        btnMenuVehicle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #0a1f18, stop:1 #081713);\n"
"    border: 2px solid #00ff9c;\n"
"    border-radius: 12px;\n"
"    padding: 30px 20px;\n"
"    color: #ffffff;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #10352a, stop:1 #0a1f18);\n"
"    border: 2px solid #33ffcc;\n"
"}"));

        mainMenuGrid->addWidget(btnMenuVehicle, 1, 0, 1, 1);

        btnMenuMachines = new QPushButton(main);
        btnMenuMachines->setObjectName("btnMenuMachines");
        btnMenuMachines->setMinimumSize(QSize(0, 120));
        btnMenuMachines->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #0a1f18, stop:1 #081713);\n"
"    border: 2px solid #00ff9c;\n"
"    border-radius: 12px;\n"
"    padding: 30px 20px;\n"
"    color: #ffffff;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #10352a, stop:1 #0a1f18);\n"
"    border: 2px solid #33ffcc;\n"
"}"));

        mainMenuGrid->addWidget(btnMenuMachines, 1, 1, 1, 1);

        btnMenuSupplier = new QPushButton(main);
        btnMenuSupplier->setObjectName("btnMenuSupplier");
        btnMenuSupplier->setMinimumSize(QSize(0, 120));
        btnMenuSupplier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #0a1f18, stop:1 #081713);\n"
"    border: 2px solid #00ff9c;\n"
"    border-radius: 12px;\n"
"    padding: 30px 20px;\n"
"    color: #ffffff;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #10352a, stop:1 #0a1f18);\n"
"    border: 2px solid #33ffcc;\n"
"}"));

        mainMenuGrid->addWidget(btnMenuSupplier, 1, 2, 1, 1);


        mainMenuLayout->addLayout(mainMenuGrid);

        verticalSpacer_mainMenu = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        mainMenuLayout->addItem(verticalSpacer_mainMenu);

        stackedwidget->addWidget(main);
        employe = new QWidget();
        employe->setObjectName("employe");
        employeeMainLayout = new QHBoxLayout(employe);
        employeeMainLayout->setSpacing(0);
        employeeMainLayout->setObjectName("employeeMainLayout");
        employeeMainLayout->setContentsMargins(0, 0, 0, 0);
        sidebarGroup = new QGroupBox(employe);
        sidebarGroup->setObjectName("sidebarGroup");
        sidebarGroup->setMinimumSize(QSize(250, 0));
        sidebarGroup->setMaximumSize(QSize(250, 16777215));
        sidebarLayout = new QVBoxLayout(sidebarGroup);
        sidebarLayout->setSpacing(0);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarLayout->setContentsMargins(0, 0, 0, 0);
        empLogoContainerLayout = new QHBoxLayout();
        empLogoContainerLayout->setObjectName("empLogoContainerLayout");
        horizontalSpacer_empLogoLeft = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        empLogoContainerLayout->addItem(horizontalSpacer_empLogoLeft);

        empSidebarLogo = new QLabel(sidebarGroup);
        empSidebarLogo->setObjectName("empSidebarLogo");
        empSidebarLogo->setMinimumSize(QSize(180, 80));
        empSidebarLogo->setMaximumSize(QSize(180, 80));
        empSidebarLogo->setPixmap(QPixmap(QString::fromUtf8(":/image/images/logo.png")));
        empSidebarLogo->setScaledContents(false);
        empSidebarLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        empLogoContainerLayout->addWidget(empSidebarLogo);

        horizontalSpacer_empLogoRight = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        empLogoContainerLayout->addItem(horizontalSpacer_empLogoRight);


        sidebarLayout->addLayout(empLogoContainerLayout);

        empSidebarTitle = new QLabel(sidebarGroup);
        empSidebarTitle->setObjectName("empSidebarTitle");

        sidebarLayout->addWidget(empSidebarTitle);

        verticalSpacer_empSidebar1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        sidebarLayout->addItem(verticalSpacer_empSidebar1);

        btnEmpDashboard = new QPushButton(sidebarGroup);
        btnEmpDashboard->setObjectName("btnEmpDashboard");
        btnEmpDashboard->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnEmpDashboard);

        btnEmpEmployee = new QPushButton(sidebarGroup);
        btnEmpEmployee->setObjectName("btnEmpEmployee");
        btnEmpEmployee->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnEmpEmployee);

        btnEmpCustomer = new QPushButton(sidebarGroup);
        btnEmpCustomer->setObjectName("btnEmpCustomer");
        btnEmpCustomer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnEmpCustomer);

        btnEmpWaste = new QPushButton(sidebarGroup);
        btnEmpWaste->setObjectName("btnEmpWaste");
        btnEmpWaste->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnEmpWaste);

        btnEmpVehicle = new QPushButton(sidebarGroup);
        btnEmpVehicle->setObjectName("btnEmpVehicle");
        btnEmpVehicle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnEmpVehicle);

        btnEmpMachines = new QPushButton(sidebarGroup);
        btnEmpMachines->setObjectName("btnEmpMachines");
        btnEmpMachines->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnEmpMachines);

        btnEmpSupplier = new QPushButton(sidebarGroup);
        btnEmpSupplier->setObjectName("btnEmpSupplier");
        btnEmpSupplier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnEmpSupplier);

        verticalSpacer_empSidebar2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(verticalSpacer_empSidebar2);

        btnEmpLogout = new QPushButton(sidebarGroup);
        btnEmpLogout->setObjectName("btnEmpLogout");
        btnEmpLogout->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout->addWidget(btnEmpLogout);


        employeeMainLayout->addWidget(sidebarGroup);

        empMainContent = new QWidget(employe);
        empMainContent->setObjectName("empMainContent");
        empContentLayout = new QVBoxLayout(empMainContent);
        empContentLayout->setSpacing(20);
        empContentLayout->setObjectName("empContentLayout");
        empContentLayout->setContentsMargins(30, 30, 30, 30);
        empHeaderLayout = new QHBoxLayout();
        empHeaderLayout->setObjectName("empHeaderLayout");
        empTitleLayout = new QVBoxLayout();
        empTitleLayout->setSpacing(5);
        empTitleLayout->setObjectName("empTitleLayout");
        empPageTitle = new QLabel(empMainContent);
        empPageTitle->setObjectName("empPageTitle");
        empPageTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 28px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        empTitleLayout->addWidget(empPageTitle);

        empPageSubtitle = new QLabel(empMainContent);
        empPageSubtitle->setObjectName("empPageSubtitle");
        empPageSubtitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 13px;\n"
"    font-weight: 400;\n"
"    color: #66ffcc;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        empTitleLayout->addWidget(empPageSubtitle);


        empHeaderLayout->addLayout(empTitleLayout);

        horizontalSpacer_empHeader = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        empHeaderLayout->addItem(horizontalSpacer_empHeader);


        empContentLayout->addLayout(empHeaderLayout);

        empTopActionsLayout = new QHBoxLayout();
        empTopActionsLayout->setSpacing(10);
        empTopActionsLayout->setObjectName("empTopActionsLayout");
        btnEmpView = new QPushButton(empMainContent);
        btnEmpView->setObjectName("btnEmpView");
        btnEmpView->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0, 255, 156, 0.15);\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"    color: #00ff9c;\n"
"    font-weight: 600;\n"
"}"));

        empTopActionsLayout->addWidget(btnEmpView);

        btnEmpAdd = new QPushButton(empMainContent);
        btnEmpAdd->setObjectName("btnEmpAdd");
        btnEmpAdd->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        empTopActionsLayout->addWidget(btnEmpAdd);

        btnEmpStats = new QPushButton(empMainContent);
        btnEmpStats->setObjectName("btnEmpStats");
        btnEmpStats->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        empTopActionsLayout->addWidget(btnEmpStats);

        horizontalSpacer_empTopActions = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        empTopActionsLayout->addItem(horizontalSpacer_empTopActions);


        empContentLayout->addLayout(empTopActionsLayout);

        empSearchWidget = new QWidget(empMainContent);
        empSearchWidget->setObjectName("empSearchWidget");
        empSearchLayout = new QVBoxLayout(empSearchWidget);
        empSearchLayout->setSpacing(10);
        empSearchLayout->setObjectName("empSearchLayout");
        empSearchLayout->setContentsMargins(0, 0, 0, 0);
        lblEmpList = new QLabel(empSearchWidget);
        lblEmpList->setObjectName("lblEmpList");
        lblEmpList->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 5px 0px;\n"
"}"));

        empSearchLayout->addWidget(lblEmpList);

        empSearchInputLayout = new QHBoxLayout();
        empSearchInputLayout->setSpacing(10);
        empSearchInputLayout->setObjectName("empSearchInputLayout");
        empSearchBox = new QLineEdit(empSearchWidget);
        empSearchBox->setObjectName("empSearchBox");
        empSearchBox->setMinimumSize(QSize(0, 40));

        empSearchInputLayout->addWidget(empSearchBox);

        empSortComboBox = new QComboBox(empSearchWidget);
        empSortComboBox->addItem(QString());
        empSortComboBox->addItem(QString());
        empSortComboBox->addItem(QString());
        empSortComboBox->addItem(QString());
        empSortComboBox->setObjectName("empSortComboBox");
        empSortComboBox->setMinimumSize(QSize(200, 40));
        empSortComboBox->setMaximumSize(QSize(250, 16777215));

        empSearchInputLayout->addWidget(empSortComboBox);


        empSearchLayout->addLayout(empSearchInputLayout);


        empContentLayout->addWidget(empSearchWidget);

        empTableActionsLayout = new QHBoxLayout();
        empTableActionsLayout->setSpacing(20);
        empTableActionsLayout->setObjectName("empTableActionsLayout");
        empTable = new QTableWidget(empMainContent);
        if (empTable->columnCount() < 7)
            empTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        empTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        empTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        empTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        empTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        empTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        empTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        empTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        empTable->setObjectName("empTable");
        empTable->setMinimumSize(QSize(600, 0));
        empTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        empTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        empTableActionsLayout->addWidget(empTable);

        empActionsPanel = new QFrame(empMainContent);
        empActionsPanel->setObjectName("empActionsPanel");
        empActionsPanel->setMinimumSize(QSize(200, 0));
        empActionsPanel->setMaximumSize(QSize(220, 16777215));
        empActionsPanelLayout = new QVBoxLayout(empActionsPanel);
        empActionsPanelLayout->setSpacing(15);
        empActionsPanelLayout->setObjectName("empActionsPanelLayout");
        lblEmpActions = new QLabel(empActionsPanel);
        lblEmpActions->setObjectName("lblEmpActions");
        lblEmpActions->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 0px;\n"
"}"));

        empActionsPanelLayout->addWidget(lblEmpActions);

        btnEmpEdit = new QPushButton(empActionsPanel);
        btnEmpEdit->setObjectName("btnEmpEdit");
        btnEmpEdit->setMinimumSize(QSize(0, 45));
        btnEmpEdit->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #00ff9c;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"}"));

        empActionsPanelLayout->addWidget(btnEmpEdit);

        btnEmpDelete = new QPushButton(empActionsPanel);
        btnEmpDelete->setObjectName("btnEmpDelete");
        btnEmpDelete->setMinimumSize(QSize(0, 45));
        btnEmpDelete->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        empActionsPanelLayout->addWidget(btnEmpDelete);

        btnEmpQRCode = new QPushButton(empActionsPanel);
        btnEmpQRCode->setObjectName("btnEmpQRCode");
        btnEmpQRCode->setMinimumSize(QSize(0, 45));
        btnEmpQRCode->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #00ff9c;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"}"));

        empActionsPanelLayout->addWidget(btnEmpQRCode);

        btnEmpClear = new QPushButton(empActionsPanel);
        btnEmpClear->setObjectName("btnEmpClear");
        btnEmpClear->setMinimumSize(QSize(0, 45));
        btnEmpClear->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    color: #00ff9c;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(0, 255, 156, 0.1);\n"
"}"));

        empActionsPanelLayout->addWidget(btnEmpClear);

        verticalSpacer_empActions = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        empActionsPanelLayout->addItem(verticalSpacer_empActions);

        btnEmpExport = new QPushButton(empActionsPanel);
        btnEmpExport->setObjectName("btnEmpExport");
        btnEmpExport->setMinimumSize(QSize(0, 45));
        btnEmpExport->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        empActionsPanelLayout->addWidget(btnEmpExport);


        empTableActionsLayout->addWidget(empActionsPanel);


        empContentLayout->addLayout(empTableActionsLayout);


        employeeMainLayout->addWidget(empMainContent);

        stackedwidget->addWidget(employe);
        wastemanagement = new QWidget();
        wastemanagement->setObjectName("wastemanagement");
        sidebarGroup_2 = new QGroupBox(wastemanagement);
        sidebarGroup_2->setObjectName("sidebarGroup_2");
        sidebarGroup_2->setGeometry(QRect(0, 0, 250, 723));
        sidebarGroup_2->setMinimumSize(QSize(250, 0));
        sidebarGroup_2->setMaximumSize(QSize(250, 16777215));
        sidebarLayout_2 = new QVBoxLayout(sidebarGroup_2);
        sidebarLayout_2->setSpacing(0);
        sidebarLayout_2->setObjectName("sidebarLayout_2");
        sidebarLayout_2->setContentsMargins(0, 0, 0, 0);
        logoContainerLayout_2 = new QHBoxLayout();
        logoContainerLayout_2->setObjectName("logoContainerLayout_2");
        horizontalSpacer_logoLeft_2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoContainerLayout_2->addItem(horizontalSpacer_logoLeft_2);

        sidebarLogo = new QLabel(sidebarGroup_2);
        sidebarLogo->setObjectName("sidebarLogo");
        sidebarLogo->setMinimumSize(QSize(180, 80));
        sidebarLogo->setMaximumSize(QSize(180, 80));
        sidebarLogo->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        sidebarLogo->setPixmap(QPixmap(QString::fromUtf8(":/image/images/logo.png")));
        sidebarLogo->setScaledContents(false);
        sidebarLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        logoContainerLayout_2->addWidget(sidebarLogo);

        horizontalSpacer_logoRight_2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoContainerLayout_2->addItem(horizontalSpacer_logoRight_2);


        sidebarLayout_2->addLayout(logoContainerLayout_2);

        sidebarTitle = new QLabel(sidebarGroup_2);
        sidebarTitle->setObjectName("sidebarTitle");

        sidebarLayout_2->addWidget(sidebarTitle);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        sidebarLayout_2->addItem(verticalSpacer);

        btnDashboard = new QPushButton(sidebarGroup_2);
        btnDashboard->setObjectName("btnDashboard");
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

        sidebarLayout_2->addWidget(btnDashboard);

        btnEmployee = new QPushButton(sidebarGroup_2);
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

        sidebarLayout_2->addWidget(btnEmployee);

        btnCustomer = new QPushButton(sidebarGroup_2);
        btnCustomer->setObjectName("btnCustomer");
        btnCustomer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_2->addWidget(btnCustomer);

        btnWaste = new QPushButton(sidebarGroup_2);
        btnWaste->setObjectName("btnWaste");
        btnWaste->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_2->addWidget(btnWaste);

        btnVehicle = new QPushButton(sidebarGroup_2);
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

        sidebarLayout_2->addWidget(btnVehicle);

        btnMachines = new QPushButton(sidebarGroup_2);
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

        sidebarLayout_2->addWidget(btnMachines);

        btnSupplier = new QPushButton(sidebarGroup_2);
        btnSupplier->setObjectName("btnSupplier");
        btnSupplier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_2->addWidget(btnSupplier);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout_2->addItem(verticalSpacer_2);

        btnLogout = new QPushButton(sidebarGroup_2);
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

        sidebarLayout_2->addWidget(btnLogout);

        mainContentWidget = new QWidget(wastemanagement);
        mainContentWidget->setObjectName("mainContentWidget");
        mainContentWidget->setGeometry(QRect(250, 0, 1107, 723));
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
        pageTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 28px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        titleLayout->addWidget(pageTitle);

        pageSubtitle = new QLabel(mainContentWidget);
        pageSubtitle->setObjectName("pageSubtitle");
        pageSubtitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 13px;\n"
"    font-weight: 400;\n"
"    color: #66ffcc;\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));

        titleLayout->addWidget(pageSubtitle);


        headerLayout->addLayout(titleLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer);


        mainContentLayout->addLayout(headerLayout);

        topActionsLayout = new QHBoxLayout();
        topActionsLayout->setSpacing(10);
        topActionsLayout->setObjectName("topActionsLayout");
        btnViewWaste = new QPushButton(mainContentWidget);
        btnViewWaste->setObjectName("btnViewWaste");
        btnViewWaste->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0, 255, 156, 0.15);\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"    color: #00ff9c;\n"
"    font-weight: 600;\n"
"}"));

        topActionsLayout->addWidget(btnViewWaste);

        btnAddWaste = new QPushButton(mainContentWidget);
        btnAddWaste->setObjectName("btnAddWaste");
        btnAddWaste->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        topActionsLayout->addWidget(btnAddWaste);

        btnWasteStats = new QPushButton(mainContentWidget);
        btnWasteStats->setObjectName("btnWasteStats");
        btnWasteStats->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        topActionsLayout->addWidget(btnWasteStats);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topActionsLayout->addItem(horizontalSpacer_2);


        mainContentLayout->addLayout(topActionsLayout);

        searchFilterWidget = new QWidget(mainContentWidget);
        searchFilterWidget->setObjectName("searchFilterWidget");
        searchFilterLayout = new QVBoxLayout(searchFilterWidget);
        searchFilterLayout->setSpacing(10);
        searchFilterLayout->setObjectName("searchFilterLayout");
        searchFilterLayout->setContentsMargins(0, 0, 0, 0);
        lblWasteList = new QLabel(searchFilterWidget);
        lblWasteList->setObjectName("lblWasteList");
        lblWasteList->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 5px 0px;\n"
"}"));

        searchFilterLayout->addWidget(lblWasteList);

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
        wasteTable = new QTableWidget(mainContentWidget);
        if (wasteTable->columnCount() < 8)
            wasteTable->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(5, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(6, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(7, __qtablewidgetitem14);
        wasteTable->setObjectName("wasteTable");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wasteTable->sizePolicy().hasHeightForWidth());
        wasteTable->setSizePolicy(sizePolicy);
        wasteTable->setMinimumSize(QSize(600, 0));
        wasteTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        wasteTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        tableActionsLayout->addWidget(wasteTable);

        actionsPanel = new QFrame(mainContentWidget);
        actionsPanel->setObjectName("actionsPanel");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(actionsPanel->sizePolicy().hasHeightForWidth());
        actionsPanel->setSizePolicy(sizePolicy1);
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

        btnEditWaste = new QPushButton(actionsPanel);
        btnEditWaste->setObjectName("btnEditWaste");
        btnEditWaste->setMinimumSize(QSize(0, 45));
        btnEditWaste->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout->addWidget(btnEditWaste);

        btnDeleteWaste = new QPushButton(actionsPanel);
        btnDeleteWaste->setObjectName("btnDeleteWaste");
        btnDeleteWaste->setMinimumSize(QSize(0, 45));
        btnDeleteWaste->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout->addWidget(btnDeleteWaste);

        btnViewMaps = new QPushButton(actionsPanel);
        btnViewMaps->setObjectName("btnViewMaps");
        btnViewMaps->setMinimumSize(QSize(0, 45));
        btnViewMaps->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout->addWidget(btnViewMaps);

        btnRate = new QPushButton(actionsPanel);
        btnRate->setObjectName("btnRate");
        btnRate->setMinimumSize(QSize(0, 45));
        btnRate->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout->addWidget(btnRate);

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

        stackedwidget->addWidget(wastemanagement);
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

        sidebarLogo_2 = new QLabel(sidebarGroup_3);
        sidebarLogo_2->setObjectName("sidebarLogo_2");
        sidebarLogo_2->setMinimumSize(QSize(180, 80));
        sidebarLogo_2->setMaximumSize(QSize(180, 80));
        sidebarLogo_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        sidebarLogo_2->setPixmap(QPixmap(QString::fromUtf8(":/image/images/logo.png")));
        sidebarLogo_2->setScaledContents(false);
        sidebarLogo_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        logoContainerLayout_3->addWidget(sidebarLogo_2);

        horizontalSpacer_logoRight_3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoContainerLayout_3->addItem(horizontalSpacer_logoRight_3);


        sidebarLayout_3->addLayout(logoContainerLayout_3);

        sidebarTitle_2 = new QLabel(sidebarGroup_3);
        sidebarTitle_2->setObjectName("sidebarTitle_2");

        sidebarLayout_3->addWidget(sidebarTitle_2);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        sidebarLayout_3->addItem(verticalSpacer_4);

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
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(4, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        vehiclesTable->setHorizontalHeaderItem(5, __qtablewidgetitem20);
        vehiclesTable->setObjectName("vehiclesTable");
        sizePolicy.setHeightForWidth(vehiclesTable->sizePolicy().hasHeightForWidth());
        vehiclesTable->setSizePolicy(sizePolicy);
        vehiclesTable->setMinimumSize(QSize(600, 0));
        vehiclesTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        vehiclesTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        tableActionsLayout_2->addWidget(vehiclesTable);

        actionsPanel_2 = new QFrame(mainContentWidget_2);
        actionsPanel_2->setObjectName("actionsPanel_2");
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
        machinePage = new QWidget();
        machinePage->setObjectName("machinePage");
        mainContentWidget_3 = new QWidget(machinePage);
        mainContentWidget_3->setObjectName("mainContentWidget_3");
        mainContentWidget_3->setGeometry(QRect(250, 7, 1107, 711));
        mainContentLayout_3 = new QVBoxLayout(mainContentWidget_3);
        mainContentLayout_3->setSpacing(20);
        mainContentLayout_3->setObjectName("mainContentLayout_3");
        mainContentLayout_3->setContentsMargins(30, 30, 30, 30);
        headerLayout_3 = new QHBoxLayout();
        headerLayout_3->setObjectName("headerLayout_3");
        titleLayout_3 = new QVBoxLayout();
        titleLayout_3->setSpacing(5);
        titleLayout_3->setObjectName("titleLayout_3");
        pageTitle_3 = new QLabel(mainContentWidget_3);
        pageTitle_3->setObjectName("pageTitle_3");

        titleLayout_3->addWidget(pageTitle_3);

        pageSubtitle_3 = new QLabel(mainContentWidget_3);
        pageSubtitle_3->setObjectName("pageSubtitle_3");

        titleLayout_3->addWidget(pageSubtitle_3);


        headerLayout_3->addLayout(titleLayout_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout_3->addItem(horizontalSpacer_5);


        mainContentLayout_3->addLayout(headerLayout_3);

        topActionsLayout_3 = new QHBoxLayout();
        topActionsLayout_3->setSpacing(10);
        topActionsLayout_3->setObjectName("topActionsLayout_3");
        btnViewMachines = new QPushButton(mainContentWidget_3);
        btnViewMachines->setObjectName("btnViewMachines");
        btnViewMachines->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0, 255, 156, 0.15);\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"    color: #00ff9c;\n"
"    font-weight: 600;\n"
"}"));

        topActionsLayout_3->addWidget(btnViewMachines);

        btnAddMachine = new QPushButton(mainContentWidget_3);
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

        topActionsLayout_3->addWidget(btnAddMachine);

        btnMachinePerformance = new QPushButton(mainContentWidget_3);
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

        topActionsLayout_3->addWidget(btnMachinePerformance);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topActionsLayout_3->addItem(horizontalSpacer_6);


        mainContentLayout_3->addLayout(topActionsLayout_3);

        searchFilterWidget_3 = new QWidget(mainContentWidget_3);
        searchFilterWidget_3->setObjectName("searchFilterWidget_3");
        searchFilterLayout_3 = new QVBoxLayout(searchFilterWidget_3);
        searchFilterLayout_3->setSpacing(10);
        searchFilterLayout_3->setObjectName("searchFilterLayout_3");
        searchFilterLayout_3->setContentsMargins(0, 0, 0, 0);
        lblMachinesList = new QLabel(searchFilterWidget_3);
        lblMachinesList->setObjectName("lblMachinesList");
        lblMachinesList->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 5px 0px;\n"
"}"));

        searchFilterLayout_3->addWidget(lblMachinesList);

        searchLayout_3 = new QHBoxLayout();
        searchLayout_3->setSpacing(10);
        searchLayout_3->setObjectName("searchLayout_3");
        searchBox_3 = new QLineEdit(searchFilterWidget_3);
        searchBox_3->setObjectName("searchBox_3");
        searchBox_3->setMinimumSize(QSize(0, 40));

        searchLayout_3->addWidget(searchBox_3);

        sortComboBox_3 = new QComboBox(searchFilterWidget_3);
        sortComboBox_3->addItem(QString());
        sortComboBox_3->addItem(QString());
        sortComboBox_3->addItem(QString());
        sortComboBox_3->addItem(QString());
        sortComboBox_3->setObjectName("sortComboBox_3");
        sortComboBox_3->setMinimumSize(QSize(200, 40));
        sortComboBox_3->setMaximumSize(QSize(250, 16777215));

        searchLayout_3->addWidget(sortComboBox_3);


        searchFilterLayout_3->addLayout(searchLayout_3);


        mainContentLayout_3->addWidget(searchFilterWidget_3);

        tableActionsLayout_3 = new QHBoxLayout();
        tableActionsLayout_3->setSpacing(20);
        tableActionsLayout_3->setObjectName("tableActionsLayout_3");
        machinesTable = new QTableWidget(mainContentWidget_3);
        if (machinesTable->columnCount() < 6)
            machinesTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(1, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(2, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(3, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(4, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        machinesTable->setHorizontalHeaderItem(5, __qtablewidgetitem26);
        machinesTable->setObjectName("machinesTable");
        sizePolicy.setHeightForWidth(machinesTable->sizePolicy().hasHeightForWidth());
        machinesTable->setSizePolicy(sizePolicy);
        machinesTable->setMinimumSize(QSize(600, 0));
        machinesTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        machinesTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        tableActionsLayout_3->addWidget(machinesTable);

        actionsPanel_3 = new QFrame(mainContentWidget_3);
        actionsPanel_3->setObjectName("actionsPanel_3");
        sizePolicy1.setHeightForWidth(actionsPanel_3->sizePolicy().hasHeightForWidth());
        actionsPanel_3->setSizePolicy(sizePolicy1);
        actionsPanel_3->setMinimumSize(QSize(200, 0));
        actionsPanel_3->setMaximumSize(QSize(220, 16777215));
        actionsPanel_3->setFrameShape(QFrame::Shape::StyledPanel);
        actionsPanel_3->setFrameShadow(QFrame::Shadow::Raised);
        actionsPanelLayout_3 = new QVBoxLayout(actionsPanel_3);
        actionsPanelLayout_3->setSpacing(15);
        actionsPanelLayout_3->setObjectName("actionsPanelLayout_3");
        lblActions_3 = new QLabel(actionsPanel_3);
        lblActions_3->setObjectName("lblActions_3");
        lblActions_3->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding: 0px;\n"
"}"));

        actionsPanelLayout_3->addWidget(lblActions_3);

        btnEditMachine = new QPushButton(actionsPanel_3);
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

        actionsPanelLayout_3->addWidget(btnEditMachine);

        btnDeleteMachine = new QPushButton(actionsPanel_3);
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

        actionsPanelLayout_3->addWidget(btnDeleteMachine);

        btnAlertSystem = new QPushButton(actionsPanel_3);
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

        actionsPanelLayout_3->addWidget(btnAlertSystem);

        btnClearSelection_3 = new QPushButton(actionsPanel_3);
        btnClearSelection_3->setObjectName("btnClearSelection_3");
        btnClearSelection_3->setMinimumSize(QSize(0, 45));
        btnClearSelection_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout_3->addWidget(btnClearSelection_3);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        actionsPanelLayout_3->addItem(verticalSpacer_7);

        btnExportPDF_3 = new QPushButton(actionsPanel_3);
        btnExportPDF_3->setObjectName("btnExportPDF_3");
        btnExportPDF_3->setMinimumSize(QSize(0, 45));
        btnExportPDF_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        actionsPanelLayout_3->addWidget(btnExportPDF_3);


        tableActionsLayout_3->addWidget(actionsPanel_3);


        mainContentLayout_3->addLayout(tableActionsLayout_3);

        sidebarGroup_4 = new QGroupBox(machinePage);
        sidebarGroup_4->setObjectName("sidebarGroup_4");
        sidebarGroup_4->setGeometry(QRect(0, -3, 250, 721));
        sidebarGroup_4->setMinimumSize(QSize(250, 0));
        sidebarGroup_4->setMaximumSize(QSize(250, 16777215));
        sidebarLayout_4 = new QVBoxLayout(sidebarGroup_4);
        sidebarLayout_4->setSpacing(0);
        sidebarLayout_4->setObjectName("sidebarLayout_4");
        sidebarLayout_4->setContentsMargins(0, 0, 0, 0);
        sidebarLogo_3 = new QLabel(sidebarGroup_4);
        sidebarLogo_3->setObjectName("sidebarLogo_3");
        sidebarLogo_3->setMinimumSize(QSize(200, 80));
        sidebarLogo_3->setMaximumSize(QSize(200, 80));
        sidebarLogo_3->setPixmap(QPixmap(QString::fromUtf8(":/image/images/logo.png")));
        sidebarLogo_3->setScaledContents(false);
        sidebarLogo_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarLayout_4->addWidget(sidebarLogo_3);

        sidebarTitle_3 = new QLabel(sidebarGroup_4);
        sidebarTitle_3->setObjectName("sidebarTitle_3");

        sidebarLayout_4->addWidget(sidebarTitle_3);

        verticalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        sidebarLayout_4->addItem(verticalSpacer_8);

        btnDashboard_3 = new QPushButton(sidebarGroup_4);
        btnDashboard_3->setObjectName("btnDashboard_3");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnDashboard_3->sizePolicy().hasHeightForWidth());
        btnDashboard_3->setSizePolicy(sizePolicy2);
        btnDashboard_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_4->addWidget(btnDashboard_3);

        btnEmployee_3 = new QPushButton(sidebarGroup_4);
        btnEmployee_3->setObjectName("btnEmployee_3");
        btnEmployee_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_4->addWidget(btnEmployee_3);

        btnCustomers = new QPushButton(sidebarGroup_4);
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

        sidebarLayout_4->addWidget(btnCustomers);

        btnWaste_3 = new QPushButton(sidebarGroup_4);
        btnWaste_3->setObjectName("btnWaste_3");
        btnWaste_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_4->addWidget(btnWaste_3);

        btnVehicle_3 = new QPushButton(sidebarGroup_4);
        btnVehicle_3->setObjectName("btnVehicle_3");
        btnVehicle_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_4->addWidget(btnVehicle_3);

        btnMachines_3 = new QPushButton(sidebarGroup_4);
        btnMachines_3->setObjectName("btnMachines_3");
        btnMachines_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_4->addWidget(btnMachines_3);

        btnSuppliers = new QPushButton(sidebarGroup_4);
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

        sidebarLayout_4->addWidget(btnSuppliers);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout_4->addItem(verticalSpacer_9);

        btnLogout_3 = new QPushButton(sidebarGroup_4);
        btnLogout_3->setObjectName("btnLogout_3");
        btnLogout_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        sidebarLayout_4->addWidget(btnLogout_3);

        stackedwidget->addWidget(machinePage);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedwidget->setCurrentIndex(7);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ReGen Management System", nullptr));
        loginLogo->setText(QString());
        loginTitle->setText(QCoreApplication::translate("MainWindow", "Welcome to ReGen", nullptr));
        loginSubtitle->setText(QCoreApplication::translate("MainWindow", "Sign in with your email, username, or phone number", nullptr));
        loginUsername->setPlaceholderText(QCoreApplication::translate("MainWindow", "Email, Username, or Phone Number", nullptr));
        loginPassword->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        btnLogin->setText(QCoreApplication::translate("MainWindow", "Log In", nullptr));
        btnForgotPassword->setText(QCoreApplication::translate("MainWindow", "Forgot Password?", nullptr));
        recoveryLogo->setText(QString());
        recoveryTitle->setText(QCoreApplication::translate("MainWindow", "Account Recovery", nullptr));
        recoverySubtitle->setText(QCoreApplication::translate("MainWindow", "Please enter your email address or phone number associated with your account", nullptr));
        recoveryEmail->setPlaceholderText(QCoreApplication::translate("MainWindow", "Email or Phone Number", nullptr));
        btnRecoveryContinue->setText(QCoreApplication::translate("MainWindow", "Continue", nullptr));
        btnRecoveryCancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        verifyLogo->setText(QString());
        verifyTitle->setText(QCoreApplication::translate("MainWindow", "Verification Code", nullptr));
        verifySubtitle->setText(QCoreApplication::translate("MainWindow", "A verification code has been sent to your email or phone number", nullptr));
        verifyCode->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter Verification Code", nullptr));
        btnVerifyCheck->setText(QCoreApplication::translate("MainWindow", "Verify", nullptr));
        btnVerifyCancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        mainMenuTitle->setText(QCoreApplication::translate("MainWindow", "Main Menu", nullptr));
        mainMenuSubtitle->setText(QCoreApplication::translate("MainWindow", "Select a module to manage", nullptr));
        btnMenuEmployee->setText(QCoreApplication::translate("MainWindow", "Employee Management", nullptr));
        btnMenuCustomer->setText(QCoreApplication::translate("MainWindow", "Customer Management", nullptr));
        btnMenuWaste->setText(QCoreApplication::translate("MainWindow", "Waste Management", nullptr));
        btnMenuVehicle->setText(QCoreApplication::translate("MainWindow", "Vehicle Management", nullptr));
        btnMenuMachines->setText(QCoreApplication::translate("MainWindow", "Machines Management", nullptr));
        btnMenuSupplier->setText(QCoreApplication::translate("MainWindow", "Supplier Management", nullptr));
        sidebarGroup->setTitle(QString());
        empSidebarLogo->setText(QString());
        empSidebarTitle->setText(QCoreApplication::translate("MainWindow", "ReGen", nullptr));
        btnEmpDashboard->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        btnEmpEmployee->setText(QCoreApplication::translate("MainWindow", "Employee Management", nullptr));
        btnEmpCustomer->setText(QCoreApplication::translate("MainWindow", "Customer Management", nullptr));
        btnEmpWaste->setText(QCoreApplication::translate("MainWindow", "Waste Management", nullptr));
        btnEmpVehicle->setText(QCoreApplication::translate("MainWindow", "Vehicle Management", nullptr));
        btnEmpMachines->setText(QCoreApplication::translate("MainWindow", "Machines Management", nullptr));
        btnEmpSupplier->setText(QCoreApplication::translate("MainWindow", "Supplier Management", nullptr));
        btnEmpLogout->setText(QCoreApplication::translate("MainWindow", "Log Out \360\237\232\252", nullptr));
        empPageTitle->setText(QCoreApplication::translate("MainWindow", "Employees", nullptr));
        empPageSubtitle->setText(QCoreApplication::translate("MainWindow", "Create, edit, search, sort, export, and analyze employees.", nullptr));
        btnEmpView->setText(QCoreApplication::translate("MainWindow", "View Employees", nullptr));
        btnEmpAdd->setText(QCoreApplication::translate("MainWindow", "Add Employee", nullptr));
        btnEmpStats->setText(QCoreApplication::translate("MainWindow", "Employee Statistics", nullptr));
        lblEmpList->setText(QCoreApplication::translate("MainWindow", "Employees List", nullptr));
        empSearchBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search by ID / Name / Email...", nullptr));
        empSortComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Sort: Name (A-Z)", nullptr));
        empSortComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Sort: Department", nullptr));
        empSortComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Sort: Salary", nullptr));
        empSortComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Sort: Date (Newest)", nullptr));

        QTableWidgetItem *___qtablewidgetitem = empTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = empTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Full Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = empTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = empTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = empTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Department", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = empTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Hire Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = empTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Salary", nullptr));
        lblEmpActions->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        btnEmpEdit->setText(QCoreApplication::translate("MainWindow", "Edit Employee", nullptr));
        btnEmpDelete->setText(QCoreApplication::translate("MainWindow", "Delete Employee", nullptr));
        btnEmpQRCode->setText(QCoreApplication::translate("MainWindow", "Generate QR Code", nullptr));
        btnEmpClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        btnEmpExport->setText(QCoreApplication::translate("MainWindow", "Export PDF", nullptr));
        sidebarGroup_2->setTitle(QString());
        sidebarLogo->setText(QString());
        sidebarTitle->setText(QCoreApplication::translate("MainWindow", "ReGen", nullptr));
        btnDashboard->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        btnEmployee->setText(QCoreApplication::translate("MainWindow", "Employee Management", nullptr));
        btnCustomer->setText(QCoreApplication::translate("MainWindow", "Customer Management", nullptr));
        btnWaste->setText(QCoreApplication::translate("MainWindow", "Waste Management", nullptr));
        btnVehicle->setText(QCoreApplication::translate("MainWindow", "Vehicle Management", nullptr));
        btnMachines->setText(QCoreApplication::translate("MainWindow", "Machines Management", nullptr));
        btnSupplier->setText(QCoreApplication::translate("MainWindow", "Supplier Management", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "Log Out \360\237\232\252", nullptr));
        pageTitle->setText(QCoreApplication::translate("MainWindow", "Waste Management", nullptr));
        pageSubtitle->setText(QCoreApplication::translate("MainWindow", "Track, manage, and analyze waste collection and disposal.", nullptr));
        btnViewWaste->setText(QCoreApplication::translate("MainWindow", "View Waste Records", nullptr));
        btnAddWaste->setText(QCoreApplication::translate("MainWindow", "Add Waste Record", nullptr));
        btnWasteStats->setText(QCoreApplication::translate("MainWindow", "Waste Statistics", nullptr));
        lblWasteList->setText(QCoreApplication::translate("MainWindow", "Waste Records", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search by ID / Type / Location...", nullptr));
        sortComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Sort: Date (Newest)", nullptr));
        sortComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Sort: Type", nullptr));
        sortComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Sort: Location", nullptr));
        sortComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Sort: Status", nullptr));

        QTableWidgetItem *___qtablewidgetitem7 = wasteTable->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = wasteTable->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = wasteTable->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Category", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = wasteTable->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Quantity", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = wasteTable->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Weight (kg)", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = wasteTable->horizontalHeaderItem(5);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Collection Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = wasteTable->horizontalHeaderItem(6);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = wasteTable->horizontalHeaderItem(7);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        lblActions->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        btnEditWaste->setText(QCoreApplication::translate("MainWindow", "Edit Record", nullptr));
        btnDeleteWaste->setText(QCoreApplication::translate("MainWindow", "Delete Record", nullptr));
        btnViewMaps->setText(QCoreApplication::translate("MainWindow", "View on Map", nullptr));
        btnRate->setText(QCoreApplication::translate("MainWindow", "Rate Service", nullptr));
        btnClearSelection->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        btnExportPDF->setText(QCoreApplication::translate("MainWindow", "Export PDF", nullptr));
        sidebarGroup_3->setTitle(QString());
        sidebarLogo_2->setText(QString());
        sidebarTitle_2->setText(QCoreApplication::translate("MainWindow", "ReGen", nullptr));
        btnDashboard_2->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        btnEmployee_2->setText(QCoreApplication::translate("MainWindow", "Employee Management", nullptr));
        btnCustomer_2->setText(QCoreApplication::translate("MainWindow", "Customer Management", nullptr));
        btnWaste_2->setText(QCoreApplication::translate("MainWindow", "Waste Management", nullptr));
        btnVehicle_2->setText(QCoreApplication::translate("MainWindow", "Vehicle Management", nullptr));
        btnMachines_2->setText(QCoreApplication::translate("MainWindow", "Machines Management", nullptr));
        btnSupplier_2->setText(QCoreApplication::translate("MainWindow", "Supplier Management", nullptr));
        btnLogout_2->setText(QCoreApplication::translate("MainWindow", "Log Out \360\237\232\252", nullptr));
        pageTitle_2->setText(QCoreApplication::translate("MainWindow", "Vehicles", nullptr));
        pageSubtitle_2->setText(QCoreApplication::translate("MainWindow", "Manage fleet, track maintenance, and monitor vehicle status.", nullptr));
        btnViewVehicles->setText(QCoreApplication::translate("MainWindow", "View Vehicles", nullptr));
        btnAddVehicle->setText(QCoreApplication::translate("MainWindow", "Add Vehicle", nullptr));
        btnCalendar->setText(QCoreApplication::translate("MainWindow", "Maintenance Calendar", nullptr));
        lblVehiclesList->setText(QCoreApplication::translate("MainWindow", "Vehicles List", nullptr));
        searchBox_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search by ID / Plate / Model...", nullptr));
        sortComboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Sort: ID", nullptr));
        sortComboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Sort: Model", nullptr));
        sortComboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Sort: Type", nullptr));
        sortComboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "Sort: Next Maintenance", nullptr));

        QTableWidgetItem *___qtablewidgetitem15 = vehiclesTable->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = vehiclesTable->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Num Plate", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = vehiclesTable->horizontalHeaderItem(2);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = vehiclesTable->horizontalHeaderItem(3);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Model", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = vehiclesTable->horizontalHeaderItem(4);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = vehiclesTable->horizontalHeaderItem(5);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "Next Maintenance", nullptr));
        lblActions_2->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        btnEditVehicle->setText(QCoreApplication::translate("MainWindow", "Edit Vehicle", nullptr));
        btnDeleteVehicle->setText(QCoreApplication::translate("MainWindow", "Delete Vehicle", nullptr));
        btnChatbot->setText(QCoreApplication::translate("MainWindow", "AI Chatbot \360\237\244\226", nullptr));
        btnClearSelection_2->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        btnExportPDF_2->setText(QCoreApplication::translate("MainWindow", "Export PDF", nullptr));
        pageTitle_3->setText(QCoreApplication::translate("MainWindow", "Machines", nullptr));
        pageSubtitle_3->setText(QCoreApplication::translate("MainWindow", "Create, edit, search, sort, export, and analyze machines.", nullptr));
        btnViewMachines->setText(QCoreApplication::translate("MainWindow", "View Machines", nullptr));
        btnAddMachine->setText(QCoreApplication::translate("MainWindow", "Add Machine", nullptr));
        btnMachinePerformance->setText(QCoreApplication::translate("MainWindow", "Machine Performance", nullptr));
        lblMachinesList->setText(QCoreApplication::translate("MainWindow", "Machines List", nullptr));
        searchBox_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search by ID / Name / Type...", nullptr));
        sortComboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "Sort: Name (A-Z)", nullptr));
        sortComboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Sort: Type", nullptr));
        sortComboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "Sort: Status", nullptr));
        sortComboBox_3->setItemText(3, QCoreApplication::translate("MainWindow", "Sort: Date (Newest)", nullptr));

        QTableWidgetItem *___qtablewidgetitem21 = machinesTable->horizontalHeaderItem(0);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = machinesTable->horizontalHeaderItem(1);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = machinesTable->horizontalHeaderItem(2);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = machinesTable->horizontalHeaderItem(3);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = machinesTable->horizontalHeaderItem(4);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = machinesTable->horizontalHeaderItem(5);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "Purchase Date", nullptr));
        lblActions_3->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        btnEditMachine->setText(QCoreApplication::translate("MainWindow", "Edit Machine", nullptr));
        btnDeleteMachine->setText(QCoreApplication::translate("MainWindow", "Delete Machine", nullptr));
        btnAlertSystem->setText(QCoreApplication::translate("MainWindow", "Alert System", nullptr));
        btnClearSelection_3->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        btnExportPDF_3->setText(QCoreApplication::translate("MainWindow", "Export PDF", nullptr));
        sidebarGroup_4->setTitle(QString());
        sidebarLogo_3->setText(QString());
        sidebarTitle_3->setText(QCoreApplication::translate("MainWindow", "ReGen", nullptr));
        btnDashboard_3->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        btnEmployee_3->setText(QCoreApplication::translate("MainWindow", "Employee Management", nullptr));
        btnCustomers->setText(QCoreApplication::translate("MainWindow", "Customer Management", nullptr));
        btnWaste_3->setText(QCoreApplication::translate("MainWindow", "Waste Management", nullptr));
        btnVehicle_3->setText(QCoreApplication::translate("MainWindow", "Vehicle Management", nullptr));
        btnMachines_3->setText(QCoreApplication::translate("MainWindow", "Machines Management", nullptr));
        btnSuppliers->setText(QCoreApplication::translate("MainWindow", "Supplier Management", nullptr));
        btnLogout_3->setText(QCoreApplication::translate("MainWindow", "Log Out \360\237\232\252", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
