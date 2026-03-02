#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "customer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadCustomers();
    void onAddCustomer();
    void onEditCustomer();
    void onDeleteCustomer();
    void onExportPDFClicked();
    void onReportStatusClicked();

private:
    Ui::MainWindow *ui;
    QList<Customer> allCustomers_; // Store all customers for dynamic search
    void updateCustomersTable(const QList<Customer> &customers);

private slots:
    void onSearchBox5TextChanged(const QString &text);
    void onSortComboBox5Changed(int index);
    void onClearSelection5Clicked();
};
#endif // MAINWINDOW_H
