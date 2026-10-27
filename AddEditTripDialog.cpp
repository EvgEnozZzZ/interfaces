#include "AddEditTripDialog.h"

#include <QDate>
#include <QFormLayout>
#include <QVBoxLayout>

AddEditTripDialog::AddEditTripDialog(QWidget *parent,
                                     Mode mode,
                                     const QVariantMap &values,
                                     const QMap<int, QString> &vehicleNames,
                                     const QMap<int, QString> &driverNames)
    : QDialog(parent)
{
    setWindowTitle(mode == AddMode ? "Добавить рейс" : "Редактировать рейс");
    setModal(true);

    vehicleCombo_ = new QComboBox(this);
    for (auto it = vehicleNames.constBegin(); it != vehicleNames.constEnd(); ++it) {
        vehicleCombo_->addItem(it.value(), it.key());
    }

    driverCombo_ = new QComboBox(this);
    for (auto it = driverNames.constBegin(); it != driverNames.constEnd(); ++it) {
        driverCombo_->addItem(it.value(), it.key());
    }

    routeEdit_ = new QLineEdit(values.value("route_name").toString(), this);
    cargoEdit_ = new QLineEdit(values.value("cargo").toString(), this);

    dateEdit_ = new QDateEdit(this);
    dateEdit_->setCalendarPopup(true);
    if (!values.value("departure_date").toString().isEmpty()) {
        dateEdit_->setDate(QDate::fromString(values.value("departure_date").toString(), "yyyy-MM-dd"));
    } else {
        dateEdit_->setDate(QDate::currentDate());
    }

    priorityCombo_ = new QComboBox(this);
    priorityCombo_->addItems({"Низкий", "Средний", "Высокий", "Критический"});
    priorityCombo_->setCurrentText(values.value("priority").toString());

    statusCombo_ = new QComboBox(this);
    statusCombo_->addItems({"Запланирован", "В пути", "Завершен", "Отменен"});
    statusCombo_->setCurrentText(values.value("status").toString());

    int selectedVehicleId = values.value("vehicle_id").toInt();
    int selectedDriverId = values.value("driver_id").toInt();

    if (selectedVehicleId > 0) {
        for (int i = 0; i < vehicleCombo_->count(); ++i) {
            if (vehicleCombo_->itemData(i).toInt() == selectedVehicleId) {
                vehicleCombo_->setCurrentIndex(i);
                break;
            }
        }
    }

    if (selectedDriverId > 0) {
        for (int i = 0; i < driverCombo_->count(); ++i) {
            if (driverCombo_->itemData(i).toInt() == selectedDriverId) {
                driverCombo_->setCurrentIndex(i);
                break;
            }
        }
    }

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Автомобиль:", vehicleCombo_);
    formLayout->addRow("Водитель:", driverCombo_);
    formLayout->addRow("Маршрут:", routeEdit_);
    formLayout->addRow("Груз:", cargoEdit_);
    formLayout->addRow("Дата:", dateEdit_);
    formLayout->addRow("Приоритет:", priorityCombo_);
    formLayout->addRow("Статус:", statusCombo_);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    resize(500, 360);
}

QVariantMap AddEditTripDialog::values() const
{
    QVariantMap result;
    result["vehicle_id"] = vehicleCombo_->currentData().toInt();
    result["driver_id"] = driverCombo_->currentData().toInt();
    result["route_name"] = routeEdit_->text().trimmed();
    result["cargo"] = cargoEdit_->text().trimmed();
    result["departure_date"] = dateEdit_->date().toString("yyyy-MM-dd");
    result["priority"] = priorityCombo_->currentText();
    result["status"] = statusCombo_->currentText();
    return result;
}
