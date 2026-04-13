#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "employee.h"
#include <QMainWindow>

class QCloseEvent;

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

    // Login logic
    void onLoginClicked();
    void onVerifyClicked();

    // 🔥 REQUIRED (missing from header before)
    void on_btnClearSelection_clicked();
    void on_btnEmpClear_clicked();

    QList<Employee> m_cachedEmployees;
    bool m_databaseReady;
};

#endif // MAINWINDOW_H
