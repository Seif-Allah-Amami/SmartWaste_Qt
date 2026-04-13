#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QComboBox;
class QDateEdit;
class QLabel;
class QLineEdit;
class QPushButton;
class QTabWidget;
class QWidget;

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

private:
    void setupVehicleTabs();
    void setupAddVehicleForm(QWidget *parent);
    void showVehicleStatsDialog();
    void bindVehicleUi();
    void clearAddVehicleForm();
    void refreshVehiclesTable();
    void setEditMode(bool enabled);
    void populateFormFromRow(int row);
    int selectedVehicleId() const;
    void applySortFromCombo();
    void applySearchFilter();
    void exportVehiclesToPdf();

    Ui::MainWindow *ui;

    QTabWidget *vehicleTabWidget;
    QWidget *vehicleListTab;
    QWidget *vehicleAddTab;
    QLabel *addVehicleTitleLabel;

    QLineEdit *addVehicleIdEdit;
    QLineEdit *addVehiclePlateEdit;
    QComboBox *addVehicleTypeCombo;
    QLineEdit *addVehicleModelEdit;
    QComboBox *addVehicleFuelCombo;
    QComboBox *addVehicleStatusCombo;
    QDateEdit *addVehicleNextMaintEdit;
    QLineEdit *addVehicleEmployeeIdEdit;
    QPushButton *addVehicleSaveBtn;
    QPushButton *addVehicleClearBtn;
    bool isEditMode;
    int editingVehicleId;
};
#endif // MAINWINDOW_H
