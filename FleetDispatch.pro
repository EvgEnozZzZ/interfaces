QT += core gui sql widgets

CONFIG += c++17

TARGET = FleetDispatch
TEMPLATE = app

SOURCES += \
    main.cpp \
    Database.cpp \
    MainWindow.cpp \
    AddEditVehicleDialog.cpp \
    AddEditDriverDialog.cpp \
    AddEditTripDialog.cpp

HEADERS += \
    Database.h \
    MainWindow.h \
    AddEditVehicleDialog.h \
    AddEditDriverDialog.h \
    AddEditTripDialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /tmp/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
