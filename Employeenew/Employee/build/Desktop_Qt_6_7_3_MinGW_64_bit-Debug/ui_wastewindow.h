/********************************************************************************
** Form generated from reading UI file 'wastewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WASTEWINDOW_H
#define UI_WASTEWINDOW_H

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

class Ui_WasteWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainHorizontalLayout;
    QGroupBox *sidebarGroup;
    QVBoxLayout *sidebarLayout;
    QHBoxLayout *logoContainerLayout;
    QSpacerItem *horizontalSpacer_logoLeft;
    QLabel *sidebarLogo;
    QSpacerItem *horizontalSpacer_logoRight;
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
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WasteWindow)
    {
        if (WasteWindow->objectName().isEmpty())
            WasteWindow->setObjectName("WasteWindow");
        WasteWindow->resize(1357, 700);
        WasteWindow->setStyleSheet(QString::fromUtf8("/* ===== Global ===== */\n"
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
"/* ===== Page Header ===== */\n"
"QLabel#pageTitle {\n"
"    font-size: 28px;\n"
"    font-weight: 700;\n"
"    color: #ffffff;\n"
"    background: transparent;\n"
" "
                        "   border: none;\n"
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
"/* ===== Search and Filter Area ===== */\n"
"QLabel#sectionLabel {\n"
"    font-size: 14px;\n"
"    font-weight: "
                        "600;\n"
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
"    background-color: #081713;\n"
"    border: 1px solid #00ff9c;\n"
"    border-radius: 10px;\n"
"    gridline-color: rgba(0"
                        ", 255, 156, 0.2);\n"
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
"/* Action Buttons in Right Panel */\n"
"QPushButton#actionBtn {\n"
"    background-color: transparent;\n"
"    bo"
                        "rder: 1px solid #00ff9c;\n"
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
"}\n"
"\n"
"/* ===== Scrollbars ===== */\n"
"QScrollBar:vertical {\n"
"    background: #050d0a;\n"
""
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
        centralwidget = new QWidget(WasteWindow);
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
        logoContainerLayout = new QHBoxLayout();
        logoContainerLayout->setObjectName("logoContainerLayout");
        horizontalSpacer_logoLeft = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoContainerLayout->addItem(horizontalSpacer_logoLeft);

        sidebarLogo = new QLabel(sidebarGroup);
        sidebarLogo->setObjectName("sidebarLogo");
        sidebarLogo->setMinimumSize(QSize(180, 80));
        sidebarLogo->setMaximumSize(QSize(180, 80));
        sidebarLogo->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        sidebarLogo->setPixmap(QPixmap(QString::fromUtf8(":/image/images/logo.png")));
        sidebarLogo->setScaledContents(false);
        sidebarLogo->setAlignment(Qt::AlignCenter);

        logoContainerLayout->addWidget(sidebarLogo);

        horizontalSpacer_logoRight = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoContainerLayout->addItem(horizontalSpacer_logoRight);


        sidebarLayout->addLayout(logoContainerLayout);

        sidebarTitle = new QLabel(sidebarGroup);
        sidebarTitle->setObjectName("sidebarTitle");

        sidebarLayout->addWidget(sidebarTitle);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        sidebarLayout->addItem(verticalSpacer);

        btnDashboard = new QPushButton(sidebarGroup);
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

        btnCustomer = new QPushButton(sidebarGroup);
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

        sidebarLayout->addWidget(btnCustomer);

        btnWaste = new QPushButton(sidebarGroup);
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

        btnSupplier = new QPushButton(sidebarGroup);
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

        sidebarLayout->addWidget(btnSupplier);

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
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        wasteTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        wasteTable->setObjectName("wasteTable");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wasteTable->sizePolicy().hasHeightForWidth());
        wasteTable->setSizePolicy(sizePolicy);
        wasteTable->setMinimumSize(QSize(600, 0));
        wasteTable->setSelectionMode(QAbstractItemView::SingleSelection);
        wasteTable->setSelectionBehavior(QAbstractItemView::SelectRows);

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
        actionsPanel->setFrameShape(QFrame::StyledPanel);
        actionsPanel->setFrameShadow(QFrame::Raised);
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


        mainHorizontalLayout->addWidget(mainContentWidget);

        WasteWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(WasteWindow);
        statusbar->setObjectName("statusbar");
        WasteWindow->setStatusBar(statusbar);

        retranslateUi(WasteWindow);

        QMetaObject::connectSlotsByName(WasteWindow);
    } // setupUi

    void retranslateUi(QMainWindow *WasteWindow)
    {
        WasteWindow->setWindowTitle(QCoreApplication::translate("WasteWindow", "Waste Management", nullptr));
        sidebarGroup->setTitle(QString());
        sidebarLogo->setText(QString());
        sidebarTitle->setText(QCoreApplication::translate("WasteWindow", "ReGen", nullptr));
        btnDashboard->setText(QCoreApplication::translate("WasteWindow", "Dashboard", nullptr));
        btnEmployee->setText(QCoreApplication::translate("WasteWindow", "Employee Management", nullptr));
        btnCustomer->setText(QCoreApplication::translate("WasteWindow", "Customer Management", nullptr));
        btnWaste->setText(QCoreApplication::translate("WasteWindow", "Waste Management", nullptr));
        btnVehicle->setText(QCoreApplication::translate("WasteWindow", "Vehicle Management", nullptr));
        btnMachines->setText(QCoreApplication::translate("WasteWindow", "Machines Management", nullptr));
        btnSupplier->setText(QCoreApplication::translate("WasteWindow", "Supplier Management", nullptr));
        btnLogout->setText(QCoreApplication::translate("WasteWindow", "Log Out \360\237\232\252", nullptr));
        pageTitle->setText(QCoreApplication::translate("WasteWindow", "Waste Management", nullptr));
        pageSubtitle->setText(QCoreApplication::translate("WasteWindow", "Track, manage, and analyze waste collection and disposal.", nullptr));
        btnViewWaste->setText(QCoreApplication::translate("WasteWindow", "View Waste Records", nullptr));
        btnAddWaste->setText(QCoreApplication::translate("WasteWindow", "Add Waste Record", nullptr));
        btnWasteStats->setText(QCoreApplication::translate("WasteWindow", "Waste Statistics", nullptr));
        lblWasteList->setText(QCoreApplication::translate("WasteWindow", "Waste Records", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("WasteWindow", "Search by ID / Type / Location...", nullptr));
        sortComboBox->setItemText(0, QCoreApplication::translate("WasteWindow", "Sort: Date (Newest)", nullptr));
        sortComboBox->setItemText(1, QCoreApplication::translate("WasteWindow", "Sort: Type", nullptr));
        sortComboBox->setItemText(2, QCoreApplication::translate("WasteWindow", "Sort: Location", nullptr));
        sortComboBox->setItemText(3, QCoreApplication::translate("WasteWindow", "Sort: Status", nullptr));

        QTableWidgetItem *___qtablewidgetitem = wasteTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("WasteWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = wasteTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("WasteWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = wasteTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("WasteWindow", "Category", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = wasteTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("WasteWindow", "Quantity", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = wasteTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("WasteWindow", "Weight (kg)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = wasteTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("WasteWindow", "Collection Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = wasteTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("WasteWindow", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = wasteTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("WasteWindow", "Status", nullptr));
        lblActions->setText(QCoreApplication::translate("WasteWindow", "Actions", nullptr));
        btnEditWaste->setText(QCoreApplication::translate("WasteWindow", "Edit Record", nullptr));
        btnDeleteWaste->setText(QCoreApplication::translate("WasteWindow", "Delete Record", nullptr));
        btnViewMaps->setText(QCoreApplication::translate("WasteWindow", "View on Map", nullptr));
        btnRate->setText(QCoreApplication::translate("WasteWindow", "Rate Service", nullptr));
        btnClearSelection->setText(QCoreApplication::translate("WasteWindow", "Clear", nullptr));
        btnExportPDF->setText(QCoreApplication::translate("WasteWindow", "Export PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WasteWindow: public Ui_WasteWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WASTEWINDOW_H
