#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("FleetDispatch");
    app.setOrganizationName("Interfaces");

    MainWindow window;
    window.resize(1280, 800);
    window.show();

    return app.exec();
}
