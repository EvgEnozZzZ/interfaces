#include "AddEditVehicleDialog.h"

#include <QDate>
#include <QFormLayout>
#include <QVBoxLayout>

AddEditVehicleDialog::AddEditVehicleDialog(QWidget *parent, Mode mode, const QVariantMap &values)
    : QDialog(parent)
{
    setWindowTitle(mode == AddMode ? "Добавить автомобиль" : "Редактировать автомобиль");
    setModal(true);

    registrationEdit_ = new QLineEdit(values.value("registration_number").toString(), this);
    brandEdit_ = new QLineEdit(values.value("brand").toString(), this);
    modelEdit_ = new QLineEdit(values.value("model").toString(), this);
    typeCombo_ = new QComboBox(this);
    typeCombo_->addItems({"Грузовой", "Легковой", "Автобус", "Спецтехника"});
    typeCombo_->setCurrentText(values.value("vehicle_type").toString());

    capacitySpin_ = new QSpinBox(this);
    capacitySpin_->setRange(0, 1000);
    capacitySpin_->setValue(values.value("capacity_tons").toInt());

    mileageSpin_ = new QSpinBox(this);
    mileageSpin_->setRange(0, 5000000);
    mileageSpin_->setValue(values.value("mileage_km").toInt());

    statusCombo_ = new QComboBox(this);
    statusCombo_->addItems({"Свободен", "В рейсе", "На ремонте", "Недоступен"});
    statusCombo_->setCurrentText(values.value("status").toString());

    serviceDateEdit_ = new QDateEdit(this);
    serviceDateEdit_->setCalendarPopup(true);
    if (!values.value("next_service_date").toString().isEmpty()) {
        serviceDateEdit_->setDate(QDate::fromString(values.value("next_service_date").toString(), "yyyy-MM-dd"));
    } else {
        serviceDateEdit_->setDate(QDate::currentDate().addDays(30));
    }

    notesEdit_ = new QLineEdit(values.value("notes").toString(), this);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Госномер:", registrationEdit_);
    formLayout->addRow("Марка:", brandEdit_);
    formLayout->addRow("Модель:", modelEdit_);
    formLayout->addRow("Тип:", typeCombo_);
    formLayout->addRow("Грузоподъемность:", capacitySpin_);
    formLayout->addRow("Пробег:", mileageSpin_);
    formLayout->addRow("Статус:", statusCombo_);
    formLayout->addRow("Следующее ТО:", serviceDateEdit_);
    formLayout->addRow("Примечание:", notesEdit_);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    resize(500, 420);
}

QVariantMap AddEditVehicleDialog::values() const
{
    QVariantMap result;
    result["registration_number"] = registrationEdit_->text().trimmed();
    result["brand"] = brandEdit_->text().trimmed();
    result["model"] = modelEdit_->text().trimmed();
    result["vehicle_type"] = typeCombo_->currentText();
    result["capacity_tons"] = capacitySpin_->value();
    result["mileage_km"] = mileageSpin_->value();
    result["status"] = statusCombo_->currentText();
    result["next_service_date"] = serviceDateEdit_->date().toString("yyyy-MM-dd");
    result["notes"] = notesEdit_->text().trimmed();
    return result;
}
