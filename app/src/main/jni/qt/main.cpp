#include "QtWindow.hpp"
#include <QGuiApplication>
#include <qt/QtLog.hpp>

int main(int argc, char* argv[])
{
    QGuiApplication application(argc, argv);

    Log::setHandler(new QtLog()); // must come before services and any REQUIRE macro

    QtWindow window;
    window.resize(540, 960);
    //window.resize(1080, 1920);
    window.show();

    return application.exec();
}
