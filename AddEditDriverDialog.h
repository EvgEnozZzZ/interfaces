#ifndef ADDEDITDRIVERDIALOG_H
#define ADDEDITDRIVERDIALOG_H

#include <QComboBox>
#include <QDateEdit>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QVariantMap>

class AddEditDriverDialog : public QDialog
{
    Q_OBJECT
public:
    enum Mode {
        AddMode,
        EditMode
    };

    explicit AddEditDriverDialog(QWidget *parent = nullptr,
                                 Mode mode = AddMode,
                                 const QVariantMap &values = QVariantMap());

    QVariantMap values() const;

private:
    QLineEdit *fullNameEdit_;
    QLineEdit *licenseNumberEdit_;
    QComboBox *licenseCategoryCombo_;
    QLineEdit *phoneEdit_;
    QComboBox *statusCombo_;
    QDateEdit *medicalDateEdit_;
    QLineEdit *notesEdit_;
};

#endif // ADDEDITDRIVERDIALOG_H
