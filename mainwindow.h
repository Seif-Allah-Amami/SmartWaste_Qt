#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "machinestats.h"
#include "machinehistory.h"
#include "alertsdialog.h"

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
    void on_btnAddMachine_clicked();
    void on_btnViewMachines_clicked();
    void on_btnDeleteMachine_clicked();
    void on_btnEditMachine_clicked();
    void on_btnExportPDF_clicked();
    void on_searchBox_textChanged(const QString &text);
    void on_sortComboBox_currentIndexChanged(int index);
    void on_btnMachinePerformance_clicked();
    void on_btnHistory_clicked();
    void on_btnAlertSystem_clicked();

private:
    Ui::MainWindow *ui;
    class Connection *conn;
};
#endif // MAINWINDOW_H