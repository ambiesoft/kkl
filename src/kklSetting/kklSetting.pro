#-------------------------------------------------
#
# Project created by QtCreator 2018-07-22T06:52:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kklSetting
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


SOURCES += \
        main.cpp \
        ckklsetting.cpp \
    ../../../lsMisc/stdQt/stdQt.cpp \
    osd.cpp \
    ../settings.cpp \
    ../../../lsMisc/stdQt/runguard.cpp \
    ../../../lsMisc/stdQt/stdQt.cpp

HEADERS += \
        ckklsetting.h \
    ../../../profile/cpp/Profile/include/ambiesoft.profile.h \
    ../../../lsMisc/stdQt/stdQt.h \
    osd.h \
    ../settings.h \
    ../../../lsMisc/stdQt/runguard.h \
    ../../../lsMisc/stdQt/stdQt.h \
    stdafx.h


win32 {
    message("win32")

    SOURCES += \
            ../../../lsMisc/GetLastErrorString.cpp \
            ../../../lsMisc/stdQt/stdQt_win32.cpp

    HEADERS += \
            ../../../lsMisc/GetLastErrorString.h \

    win32-g++ {
        message("win32-g++")
        LIBS += -lshlwapi
    }
    win32-msvc* {
        message("win32-msvc*")
        LIBS += User32.lib shlwapi.lib
        # Ole32.lib
    }
    RC_ICONS +=
}
linux {
    message("linux-g++")


    SOURCES += \
        ../../../lsMisc/stdQt/stdQt_linux.cpp

    RC_ICONS +=
}

FORMS += \
        ckklsetting.ui
