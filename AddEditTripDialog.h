#ifndef ADDEDITTRIPDIALOG_H
#define ADDEDITTRIPDIALOG_H

#include <QComboBox>
#include <QDateEdit>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QVariantMap>

class AddEditTripDialog : public QDialog
{
    Q_OBJECT
public:
    enum Mode {
        AddMode,
        EditMode
    };

    explicit AddEditTripDialog(QWidget *parent = nullptr,
                              Mode mode = AddMode,
                              const QVariantMap &values = QVariantMap(),
                              const QMap<int, QString> &vehicleNames = QMap<int, QString>(),
                              const QMap<int, QString> &driverNames = QMap<int, QString>());

    QVariantMap values() const;

private:
    QComboBox *vehicleCombo_;
    QComboBox *driverCombo_;
    QLineEdit *routeEdit_;
    QLineEdit *cargoEdit_;
    QDateEdit *dateEdit_;
    QComboBox *priorityCombo_;
    QComboBox *statusCombo_;
};

#endif // ADDEDITTRIPDIALOG_H
