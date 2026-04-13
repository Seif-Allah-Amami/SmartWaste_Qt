#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

<<<<<<< HEAD
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
=======
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
>>>>>>> origin/vehicle
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
<<<<<<< HEAD
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
=======
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
};

>>>>>>> origin/vehicle
#endif // MAINWINDOW_H
