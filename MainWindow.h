#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Database.h"

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QTabWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addVehicle();
    void editVehicle();
    void deleteVehicle();

    void addDriver();
    void editDriver();
    void deleteDriver();

    void addTrip();
    void editTrip();
    void deleteTrip();

    void refreshAll();

private:
    void setupUi();
    void setupDashboardTab();
    void setupVehicleTab();
    void setupDriverTab();
    void setupTripTab();

    void loadVehicleTable();
    void loadDriverTable();
    void loadTripTable();
    void updateSummary();

    Database database_;

    QTabWidget *tabWidget_;

    QTableView *vehicleTable_;
    QTableView *driverTable_;
    QTableView *tripTable_;

    QStandardItemModel *vehicleModel_;
    QStandardItemModel *driverModel_;
    QStandardItemModel *tripModel_;

    QLabel *vehiclesTotalLabel_;
    QLabel *driversTotalLabel_;
    QLabel *tripsTotalLabel_;
    QLabel *availableVehiclesLabel_;
    QLabel *availableDriversLabel_;
};

#endif // MAINWINDOW_H
