/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MainWindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "0$us6+r5SLQ63w64Cv6fR+9YxxnmY",
        "addVehicle",
        "",
        "editVehicle",
        "deleteVehicle",
        "addDriver",
        "editDriver",
        "deleteDriver",
        "addTrip",
        "editTrip",
        "deleteTrip",
        "refreshAll"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'addVehicle'
        QtMocHelpers::SlotData<void()>(2, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'editVehicle'
        QtMocHelpers::SlotData<void()>(4, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'deleteVehicle'
        QtMocHelpers::SlotData<void()>(5, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'addDriver'
        QtMocHelpers::SlotData<void()>(6, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'editDriver'
        QtMocHelpers::SlotData<void()>(7, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'deleteDriver'
        QtMocHelpers::SlotData<void()>(8, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'addTrip'
        QtMocHelpers::SlotData<void()>(9, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'editTrip'
        QtMocHelpers::SlotData<void()>(10, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'deleteTrip'
        QtMocHelpers::SlotData<void()>(11, 3, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'refreshAll'
        QtMocHelpers::SlotData<void()>(12, 3, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    int qt_metaObjectHashIndex = 1;
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_metaObjectHashIndex);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->addVehicle(); break;
        case 1: _t->editVehicle(); break;
        case 2: _t->deleteVehicle(); break;
        case 3: _t->addDriver(); break;
        case 4: _t->editDriver(); break;
        case 5: _t->deleteDriver(); break;
        case 6: _t->addTrip(); break;
        case 7: _t->editTrip(); break;
        case 8: _t->deleteTrip(); break;
        case 9: _t->refreshAll(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
