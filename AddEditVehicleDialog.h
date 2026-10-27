#ifndef ADDEDITVEHICLEDIALOG_H
#define ADDEDITVEHICLEDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QVariantMap>

class AddEditVehicleDialog : public QDialog
{
    Q_OBJECT
public:
    enum Mode {
        AddMode,
        EditMode
    };

    explicit AddEditVehicleDialog(QWidget *parent = nullptr,
                                 Mode mode = AddMode,
                                 const QVariantMap &values = QVariantMap());

    QVariantMap values() const;

private:
    QLineEdit *registrationEdit_;
    QLineEdit *brandEdit_;
    QLineEdit *modelEdit_;
    QComboBox *typeCombo_;
    QSpinBox *capacitySpin_;
    QSpinBox *mileageSpin_;
    QComboBox *statusCombo_;
    QDateEdit *serviceDateEdit_;
    QLineEdit *notesEdit_;
};

#endif // ADDEDITVEHICLEDIALOG_H
