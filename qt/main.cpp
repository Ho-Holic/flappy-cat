#include "QtWindow.hpp"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication application(argc, argv);

    QtWindow window;
    window.show();

    return application.exec();
}
