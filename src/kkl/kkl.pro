#-------------------------------------------------
#
# Project created by QtCreator 2018-07-22T04:47:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kkl
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Added from https://github.com/ambiesoft/qglobalshortcut
unix:QT = x11extras
unix:LIBS += -lX11 -lxcb
unix:QMAKE_CXXFLAGS += "-std=c++11"

win32:LIBS += User32.lib
win32:SOURCES += ../../qglobalshortcut/src/qglobalshortcut_win.cc
unix:SOURCES  += ../../qglobalshortcut/src/qglobalshortcut_x11.cc
#macx:SOURCES  += src/qglobalshortcut_macx.cc


SOURCES += \
        main.cpp \
    ckklwindow.cpp \
    ../../qglobalshortcut/src/qglobalshortcut.cc

HEADERS += \
    ckklwindow.h \
    stable.h \
    ../../qglobalshortcut/src/qglobalshortcut.h

FORMS +=


PRECOMPILED_HEADER = stable.h

RESOURCES += \
    kkl.qrc
