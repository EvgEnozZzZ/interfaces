#include "MainWindow.h"

#include "AddEditDriverDialog.h"
#include "AddEditTripDialog.h"
#include "AddEditVehicleDialog.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , tabWidget_(nullptr)
    , vehicleTable_(nullptr)
    , driverTable_(nullptr)
    , tripTable_(nullptr)
    , vehicleModel_(nullptr)
    , driverModel_(nullptr)
    , tripModel_(nullptr)
{
    if (!database_.initialize()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть базу данных SQLite.");
    }

    setupUi();
    refreshAll();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *rootLayout = new QVBoxLayout(centralWidget);

    tabWidget_ = new QTabWidget(this);
    rootLayout->addWidget(tabWidget_);
    setCentralWidget(centralWidget);

    setupDashboardTab();
    setupVehicleTab();
    setupDriverTab();
    setupTripTab();
}

void MainWindow::setupDashboardTab()
{
    QWidget *dashboardWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(dashboardWidget);

    QLabel *title = new QLabel("Панель управления автопарком", this);
    QFont titleFont = title->font();
    titleFont.setBold(true);
    titleFont.setPointSize(16);
    title->setFont(titleFont);
    layout->addWidget(title);

    QGroupBox *summaryBox = new QGroupBox("Общая сводка", this);
    QGridLayout *summaryLayout = new QGridLayout(summaryBox);

    vehiclesTotalLabel_ = new QLabel(this);
    driversTotalLabel_ = new QLabel(this);
    tripsTotalLabel_ = new QLabel(this);
    availableVehiclesLabel_ = new QLabel(this);
    availableDriversLabel_ = new QLabel(this);

    summaryLayout->addWidget(vehiclesTotalLabel_, 0, 0);
    summaryLayout->addWidget(driversTotalLabel_, 0, 1);
    summaryLayout->addWidget(tripsTotalLabel_, 1, 0);
    summaryLayout->addWidget(availableVehiclesLabel_, 1, 1);
    summaryLayout->addWidget(availableDriversLabel_, 2, 0);

    layout->addWidget(summaryBox);

    QLabel *infoLabel = new QLabel(
        "Система позволяет следить за транспортом, назначать рейсы и контролировать доступность водителей.",
        this);
    infoLabel->setWordWrap(true);
    layout->addWidget(infoLabel);

    tabWidget_->addTab(dashboardWidget, "Главная");
}

void MainWindow::setupVehicleTab()
{
    QWidget *vehicleWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(vehicleWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addVehicleButton = new QPushButton("Добавить", this);
    QPushButton *editVehicleButton = new QPushButton("Редактировать", this);
    QPushButton *deleteVehicleButton = new QPushButton("Удалить", this);

    buttonLayout->addWidget(addVehicleButton);
    buttonLayout->addWidget(editVehicleButton);
    buttonLayout->addWidget(deleteVehicleButton);
    buttonLayout->addStretch();

    vehicleTable_ = new QTableView(this);
    vehicleTable_->setSelectionBehavior(QAbstractItemView::SelectRows);
    vehicleTable_->setSelectionMode(QAbstractItemView::SingleSelection);
    vehicleTable_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vehicleTable_->setAlternatingRowColors(true);
    vehicleTable_->horizontalHeader()->setStretchLastSection(true);

    vehicleModel_ = new QStandardItemModel(0, 10, this);
    vehicleModel_->setHorizontalHeaderLabels(QStringList()
        << "ID"
        << "Номер"
        << "Марка"
        << "Модель"
        << "Тип"
        << "Грузоподъемность"
        << "Пробег"
        << "Статус"
        << "Следующее ТО"
        << "Примечание");

    vehicleTable_->setModel(vehicleModel_);

    layout->addLayout(buttonLayout);
    layout->addWidget(vehicleTable_);

    connect(addVehicleButton, &QPushButton::clicked, this, &MainWindow::addVehicle);
    connect(editVehicleButton, &QPushButton::clicked, this, &MainWindow::editVehicle);
    connect(deleteVehicleButton, &QPushButton::clicked, this, &MainWindow::deleteVehicle);

    tabWidget_->addTab(vehicleWidget, "Автомобили");
}

void MainWindow::setupDriverTab()
{
    QWidget *driverWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(driverWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addDriverButton = new QPushButton("Добавить", this);
    QPushButton *editDriverButton = new QPushButton("Редактировать", this);
    QPushButton *deleteDriverButton = new QPushButton("Удалить", this);

    buttonLayout->addWidget(addDriverButton);
    buttonLayout->addWidget(editDriverButton);
    buttonLayout->addWidget(deleteDriverButton);
    buttonLayout->addStretch();

    driverTable_ = new QTableView(this);
    driverTable_->setSelectionBehavior(QAbstractItemView::SelectRows);
    driverTable_->setSelectionMode(QAbstractItemView::SingleSelection);
    driverTable_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    driverTable_->setAlternatingRowColors(true);
    driverTable_->horizontalHeader()->setStretchLastSection(true);

    driverModel_ = new QStandardItemModel(0, 8, this);
    driverModel_->setHorizontalHeaderLabels(QStringList()
        << "ID"
        << "ФИО"
        << "Права"
        << "Категория"
        << "Телефон"
        << "Статус"
        << "Медосмотр"
        << "Примечание");

    driverTable_->setModel(driverModel_);

    layout->addLayout(buttonLayout);
    layout->addWidget(driverTable_);

    connect(addDriverButton, &QPushButton::clicked, this, &MainWindow::addDriver);
    connect(editDriverButton, &QPushButton::clicked, this, &MainWindow::editDriver);
    connect(deleteDriverButton, &QPushButton::clicked, this, &MainWindow::deleteDriver);

    tabWidget_->addTab(driverWidget, "Водители");
}

void MainWindow::setupTripTab()
{
    QWidget *tripWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(tripWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addTripButton = new QPushButton("Добавить", this);
    QPushButton *editTripButton = new QPushButton("Редактировать", this);
    QPushButton *deleteTripButton = new QPushButton("Удалить", this);

    buttonLayout->addWidget(addTripButton);
    buttonLayout->addWidget(editTripButton);
    buttonLayout->addWidget(deleteTripButton);
    buttonLayout->addStretch();

    tripTable_ = new QTableView(this);
    tripTable_->setSelectionBehavior(QAbstractItemView::SelectRows);
    tripTable_->setSelectionMode(QAbstractItemView::SingleSelection);
    tripTable_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tripTable_->setAlternatingRowColors(true);
    tripTable_->horizontalHeader()->setStretchLastSection(true);

    tripModel_ = new QStandardItemModel(0, 8, this);
    tripModel_->setHorizontalHeaderLabels(QStringList()
        << "ID"
        << "Маршрут"
        << "Груз"
        << "Дата"
        << "Приоритет"
        << "Статус"
        << "Автомобиль"
        << "Водитель");

    tripTable_->setModel(tripModel_);

    layout->addLayout(buttonLayout);
    layout->addWidget(tripTable_);

    connect(addTripButton, &QPushButton::clicked, this, &MainWindow::addTrip);
    connect(editTripButton, &QPushButton::clicked, this, &MainWindow::editTrip);
    connect(deleteTripButton, &QPushButton::clicked, this, &MainWindow::deleteTrip);

    tabWidget_->addTab(tripWidget, "Рейсы");
}

void MainWindow::refreshAll()
{
    loadVehicleTable();
    loadDriverTable();
    loadTripTable();
    updateSummary();
}

void MainWindow::loadVehicleTable()
{
    if (!vehicleModel_) {
        return;
    }

    vehicleModel_->clear();
    vehicleModel_->setHorizontalHeaderLabels(QStringList()
        << "ID"
        << "Номер"
        << "Марка"
        << "Модель"
        << "Тип"
        << "Грузоподъемность"
        << "Пробег"
        << "Статус"
        << "Следующее ТО"
        << "Примечание");

    const QList<QVariantMap> vehicles = database_.getVehicles();
    for (const QVariantMap &vehicle : vehicles) {
        QList<QStandardItem *> row;
        row << new QStandardItem(vehicle["id"].toString())
            << new QStandardItem(vehicle["registration_number"].toString())
            << new QStandardItem(vehicle["brand"].toString())
            << new QStandardItem(vehicle["model"].toString())
            << new QStandardItem(vehicle["vehicle_type"].toString())
            << new QStandardItem(vehicle["capacity_tons"].toString())
            << new QStandardItem(vehicle["mileage_km"].toString())
            << new QStandardItem(vehicle["status"].toString())
            << new QStandardItem(vehicle["next_service_date"].toString())
            << new QStandardItem(vehicle["notes"].toString());
        vehicleModel_->appendRow(row);
    }

    if (vehicleTable_) {
        vehicleTable_->resizeColumnsToContents();
    }
}

void MainWindow::loadDriverTable()
{
    if (!driverModel_) {
        return;
    }

    driverModel_->clear();
    driverModel_->setHorizontalHeaderLabels(QStringList()
        << "ID"
        << "ФИО"
        << "Права"
        << "Категория"
        << "Телефон"
        << "Статус"
        << "Медосмотр"
        << "Примечание");

    const QList<QVariantMap> drivers = database_.getDrivers();
    for (const QVariantMap &driver : drivers) {
        QList<QStandardItem *> row;
        row << new QStandardItem(driver["id"].toString())
            << new QStandardItem(driver["full_name"].toString())
            << new QStandardItem(driver["license_number"].toString())
            << new QStandardItem(driver["license_category"].toString())
            << new QStandardItem(driver["phone"].toString())
            << new QStandardItem(driver["status"].toString())
            << new QStandardItem(driver["medical_check_date"].toString())
            << new QStandardItem(driver["notes"].toString());
        driverModel_->appendRow(row);
    }

    if (driverTable_) {
        driverTable_->resizeColumnsToContents();
    }
}

void MainWindow::loadTripTable()
{
    if (!tripModel_) {
        return;
    }

    tripModel_->clear();
    tripModel_->setHorizontalHeaderLabels(QStringList()
        << "ID"
        << "Маршрут"
        << "Груз"
        << "Дата"
        << "Приоритет"
        << "Статус"
        << "Автомобиль"
        << "Водитель");

    const QList<QVariantMap> trips = database_.getTrips();
    for (const QVariantMap &trip : trips) {
        QList<QStandardItem *> row;
        row << new QStandardItem(trip["id"].toString())
            << new QStandardItem(trip["route_name"].toString())
            << new QStandardItem(trip["cargo"].toString())
            << new QStandardItem(trip["departure_date"].toString())
            << new QStandardItem(trip["priority"].toString())
            << new QStandardItem(trip["status"].toString())
            << new QStandardItem(trip["vehicle_name"].toString())
            << new QStandardItem(trip["driver_name"].toString());
        tripModel_->appendRow(row);
    }

    if (tripTable_) {
        tripTable_->resizeColumnsToContents();
    }
}

void MainWindow::updateSummary()
{
    const QVariantMap summary = database_.getSummary();
    vehiclesTotalLabel_->setText(QString("Всего авто: %1").arg(summary.value("vehicles_total", 0).toInt()));
    driversTotalLabel_->setText(QString("Всего водителей: %1").arg(summary.value("drivers_total", 0).toInt()));
    tripsTotalLabel_->setText(QString("Всего рейсов: %1").arg(summary.value("trips_total", 0).toInt()));
    availableVehiclesLabel_->setText(QString("Свободных авто: %1").arg(summary.value("vehicles_available", 0).toInt()));
    availableDriversLabel_->setText(QString("Свободных водителей: %1").arg(summary.value("drivers_available", 0).toInt()));
}

void MainWindow::addVehicle()
{
    AddEditVehicleDialog dialog(this, AddEditVehicleDialog::AddMode);
    if (dialog.exec() == QDialog::Accepted) {
        if (database_.addVehicle(dialog.values())) {
            refreshAll();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось добавить автомобиль.");
        }
    }
}

void MainWindow::editVehicle()
{
    if (!vehicleTable_ || !vehicleTable_->selectionModel() || !vehicleTable_->selectionModel()->hasSelection()) {
        QMessageBox::information(this, "Информация", "Выберите автомобиль из списка.");
        return;
    }

    const int row = vehicleTable_->selectionModel()->currentIndex().row();
    const int id = vehicleModel_->item(row, 0)->text().toInt();

    QVariantMap selected;
    const QList<QVariantMap> vehicles = database_.getVehicles();
    for (const QVariantMap &vehicle : vehicles) {
        if (vehicle["id"].toInt() == id) {
            selected = vehicle;
            break;
        }
    }

    AddEditVehicleDialog dialog(this, AddEditVehicleDialog::EditMode, selected);
    if (dialog.exec() == QDialog::Accepted) {
        if (database_.updateVehicle(id, dialog.values())) {
            refreshAll();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось обновить автомобиль.");
        }
    }
}

void MainWindow::deleteVehicle()
{
    if (!vehicleTable_ || !vehicleTable_->selectionModel() || !vehicleTable_->selectionModel()->hasSelection()) {
        QMessageBox::information(this, "Информация", "Выберите автомобиль для удаления.");
        return;
    }

    const int row = vehicleTable_->selectionModel()->currentIndex().row();
    const int id = vehicleModel_->item(row, 0)->text().toInt();

    if (QMessageBox::question(this, "Подтверждение", "Удалить выбранный автомобиль?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return;
    }

    if (database_.deleteVehicle(id)) {
        refreshAll();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить автомобиль.");
    }
}

void MainWindow::addDriver()
{
    AddEditDriverDialog dialog(this, AddEditDriverDialog::AddMode);
    if (dialog.exec() == QDialog::Accepted) {
        if (database_.addDriver(dialog.values())) {
            refreshAll();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось добавить водителя.");
        }
    }
}

void MainWindow::editDriver()
{
    if (!driverTable_ || !driverTable_->selectionModel() || !driverTable_->selectionModel()->hasSelection()) {
        QMessageBox::information(this, "Информация", "Выберите водителя из списка.");
        return;
    }

    const int row = driverTable_->selectionModel()->currentIndex().row();
    const int id = driverModel_->item(row, 0)->text().toInt();

    QVariantMap selected;
    const QList<QVariantMap> drivers = database_.getDrivers();
    for (const QVariantMap &driver : drivers) {
        if (driver["id"].toInt() == id) {
            selected = driver;
            break;
        }
    }

    AddEditDriverDialog dialog(this, AddEditDriverDialog::EditMode, selected);
    if (dialog.exec() == QDialog::Accepted) {
        if (database_.updateDriver(id, dialog.values())) {
            refreshAll();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось обновить водителя.");
        }
    }
}

void MainWindow::deleteDriver()
{
    if (!driverTable_ || !driverTable_->selectionModel() || !driverTable_->selectionModel()->hasSelection()) {
        QMessageBox::information(this, "Информация", "Выберите водителя для удаления.");
        return;
    }

    const int row = driverTable_->selectionModel()->currentIndex().row();
    const int id = driverModel_->item(row, 0)->text().toInt();

    if (QMessageBox::question(this, "Подтверждение", "Удалить выбранного водителя?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return;
    }

    if (database_.deleteDriver(id)) {
        refreshAll();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить водителя.");
    }
}

void MainWindow::addTrip()
{
    AddEditTripDialog dialog(this, AddEditTripDialog::AddMode, QVariantMap(), database_.getVehicleNames(), database_.getDriverNames());
    if (dialog.exec() == QDialog::Accepted) {
        if (database_.addTrip(dialog.values())) {
            refreshAll();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось добавить рейс.");
        }
    }
}

void MainWindow::editTrip()
{
    if (!tripTable_ || !tripTable_->selectionModel() || !tripTable_->selectionModel()->hasSelection()) {
        QMessageBox::information(this, "Информация", "Выберите рейс из списка.");
        return;
    }

    const int row = tripTable_->selectionModel()->currentIndex().row();
    const int id = tripModel_->item(row, 0)->text().toInt();

    QVariantMap selected;
    const QList<QVariantMap> trips = database_.getTrips();
    for (const QVariantMap &trip : trips) {
        if (trip["id"].toInt() == id) {
            selected = trip;
            break;
        }
    }

    QString driverName = selected.value("driver_name").toString();
    QString vehicleName = selected.value("vehicle_name").toString();
    QMap<int, QString> vehicles = database_.getVehicleNames();
    QMap<int, QString> drivers = database_.getDriverNames();

    int vehicleId = -1;
    int driverId = -1;

    for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
        if (it.value() == vehicleName) {
            vehicleId = it.key();
            break;
        }
    }

    for (auto it = drivers.begin(); it != drivers.end(); ++it) {
        if (it.value() == driverName) {
            driverId = it.key();
            break;
        }
    }

    selected["vehicle_id"] = vehicleId;
    selected["driver_id"] = driverId;

    AddEditTripDialog dialog(this, AddEditTripDialog::EditMode, selected, vehicles, drivers);
    if (dialog.exec() == QDialog::Accepted) {
        if (database_.updateTrip(id, dialog.values())) {
            refreshAll();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось обновить рейс.");
        }
    }
}

void MainWindow::deleteTrip()
{
    if (!tripTable_ || !tripTable_->selectionModel() || !tripTable_->selectionModel()->hasSelection()) {
        QMessageBox::information(this, "Информация", "Выберите рейс для удаления.");
        return;
    }

    const int row = tripTable_->selectionModel()->currentIndex().row();
    const int id = tripModel_->item(row, 0)->text().toInt();

    if (QMessageBox::question(this, "Подтверждение", "Удалить выбранный рейс?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return;
    }

    if (database_.deleteTrip(id)) {
        refreshAll();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить рейс.");
    }
}
