#include "AddEditDriverDialog.h"

#include <QDate>
#include <QFormLayout>
#include <QVBoxLayout>

AddEditDriverDialog::AddEditDriverDialog(QWidget *parent, Mode mode, const QVariantMap &values)
    : QDialog(parent)
{
    setWindowTitle(mode == AddMode ? "Добавить водителя" : "Редактировать водителя");
    setModal(true);

    fullNameEdit_ = new QLineEdit(values.value("full_name").toString(), this);
    licenseNumberEdit_ = new QLineEdit(values.value("license_number").toString(), this);
    licenseCategoryCombo_ = new QComboBox(this);
    licenseCategoryCombo_->addItems({"B", "C", "D", "E", "C,E", "D,E"});
    licenseCategoryCombo_->setCurrentText(values.value("license_category").toString());

    phoneEdit_ = new QLineEdit(values.value("phone").toString(), this);
    statusCombo_ = new QComboBox(this);
    statusCombo_->addItems({"Свободен", "В рейсе", "Отпуск", "Недоступен"});
    statusCombo_->setCurrentText(values.value("status").toString());

    medicalDateEdit_ = new QDateEdit(this);
    medicalDateEdit_->setCalendarPopup(true);
    if (!values.value("medical_check_date").toString().isEmpty()) {
        medicalDateEdit_->setDate(QDate::fromString(values.value("medical_check_date").toString(), "yyyy-MM-dd"));
    } else {
        medicalDateEdit_->setDate(QDate::currentDate().addDays(30));
    }

    notesEdit_ = new QLineEdit(values.value("notes").toString(), this);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("ФИО:", fullNameEdit_);
    formLayout->addRow("Права:", licenseNumberEdit_);
    formLayout->addRow("Категория:", licenseCategoryCombo_);
    formLayout->addRow("Телефон:", phoneEdit_);
    formLayout->addRow("Статус:", statusCombo_);
    formLayout->addRow("Медосмотр:", medicalDateEdit_);
    formLayout->addRow("Примечание:", notesEdit_);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    resize(500, 360);
}

QVariantMap AddEditDriverDialog::values() const
{
    QVariantMap result;
    result["full_name"] = fullNameEdit_->text().trimmed();
    result["license_number"] = licenseNumberEdit_->text().trimmed();
    result["license_category"] = licenseCategoryCombo_->currentText();
    result["phone"] = phoneEdit_->text().trimmed();
    result["status"] = statusCombo_->currentText();
    result["medical_check_date"] = medicalDateEdit_->date().toString("yyyy-MM-dd");
    result["notes"] = notesEdit_->text().trimmed();
    return result;
}
