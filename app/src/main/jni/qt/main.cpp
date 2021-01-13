#include "QtWindow.hpp"
#include <QGuiApplication>

int main(int argc, char* argv[])
{
    QGuiApplication application(argc, argv);

    QtWindow window;
    window.resize(540, 960);
    //window.resize(1080, 1920);
    window.show();

    return application.exec();
}
