#ifndef MAINWINDOW_H
#define MAINWINDOW_H

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> origin/employee
#include "employee.h"
#include <QMainWindow>

class QCloseEvent;

<<<<<<< HEAD
=======
=======
#include <QMainWindow>

>>>>>>> origin/employee
>>>>>>> origin/employee
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void setupConnections();

    // Navigation methods
    void showLoginPage();
    void showRecoveryPage();
    void showVerificationPage();
    void showMainMenu();
    void showEmployeePage();
    void showCustomerPage();
    void showWastePage();
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> origin/employee

    // Employee DB helpers
    bool initializeDatabase();
    bool ensureEmployeeTable();
    void setupEmployeeTable();
    void loadEmployeesToTable(const QList<Employee> &employees);
    void applyEmployeeSearchAndSort();
    bool collectEmployeeData(Employee &employee, bool forEdit);
    bool selectedEmployeeId(int &id) const;

    // Employee CRUD handlers
    void onAddEmployeeClicked();
    void onViewEmployeesClicked();
    void onEditEmployeeClicked();
    void onDeleteEmployeeClicked();
    void onClearEmployeeClicked();
    void onEmpSearchChanged(const QString &text);
    void onEmpSortChanged(int index);
<<<<<<< HEAD
    void onGenerateQRCodeClicked();
    void onUploadCVClicked();
=======
>>>>>>> origin/employee

    // Login logic
    void onLoginClicked();
    void onVerifyClicked();

    // 🔥 REQUIRED (missing from header before)
    void on_btnClearSelection_clicked();
    void on_btnEmpClear_clicked();

    QList<Employee> m_cachedEmployees;
    bool m_databaseReady;
<<<<<<< HEAD
=======
=======
<<<<<<< HEAD
    void showVehiclePage();
    void showMachinePage();
    void showSupplierPage();
=======
<<<<<<< HEAD
    void showVehiclePage();
    void showMachinePage();
=======
<<<<<<< HEAD
    void showVehiclePage();
=======
>>>>>>> cc7e03e7c193b16524633b58b2f60e0e503c4f03
>>>>>>> a74b88ee5bbf8c446a6a6d38d8b79c649dad41fb
>>>>>>> d241421e166fc2265f00b501a6340b3af2200544

    // Logic methods
    void onLoginClicked();
    void onVerifyClicked();
>>>>>>> origin/employee
>>>>>>> origin/employee
};

#endif // MAINWINDOW_H
