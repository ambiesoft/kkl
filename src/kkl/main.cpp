
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>

#include "../../../profile/cpp/Profile/include/ambiesoft.profile.h"
#include "../../../lsMisc/stdQt/stdQt.h"
#include "../../../lsMisc/stdQt/runguard.h"

#include "settings.h"

#include "ckklwindow.h"

using namespace Ambiesoft;


bool ReadSettings()
{
    {
        QString inipath = QDir().homePath();
        QDir(inipath).mkdir(".kkl");
        inipath = pathCombine(inipath, ".kkl");
        if(!QFileInfo(inipath).isDir())
        {
            QMessageBox::critical(nullptr,
                                  QApplication::applicationName(),
                                  QObject::tr("Failed to create directory '%1'.").arg(inipath));

        }
        inipath = pathCombine(inipath, "kkl.conf");

        int testvalue = static_cast<int>(time(nullptr));
        Profile::WriteInt("TEST", "TESTVALUE",testvalue,inipath.toStdString().c_str());

        int t;
        Profile::GetInt("TEST","TESTVALUE",-1,t,inipath.toStdString().c_str());

        if(testvalue != t)
        {
            QMessageBox::critical(nullptr,
                                  QApplication::applicationName(),
                                  QObject::tr("Failed to write to '%1'.").arg(inipath));
            return false;
        }

        std::string s;
        HashIniHandle hih = Profile::ReadAll(inipath.toStdString());

        Profile::GetString("settings", "hot key", "", s, hih);
        gSettings.hotKey = s.c_str();
    }

    {
        // read ini
    }
    return true;
}
int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("KKL");
    QCoreApplication::setApplicationVersion("3.01");
    Q_INIT_RESOURCE(kkl);
    QApplication app(argc, argv);


    RunGuard guard("kkl-runguard");
    if (!guard.tryToRun())
    {
        QMessageBox::critical(nullptr,
                              QApplication::applicationName(),
                              QObject::tr("Another instance is already running."));

        return 0;
    }

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr,
                              QApplication::applicationName(),
                              QObject::tr("System tray is not available on this system."));
        return 1;
    }

    if(!ReadSettings())
        return 1;

    CkklWindow win;
    if(!win.initialized())
        return -1;

    return app.exec();
}
