QT += core gui

CONFIG += c++14
CONFIG += sdk_no_version_check

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    QtWindow.cpp

HEADERS += \
    QtWindow.hpp

