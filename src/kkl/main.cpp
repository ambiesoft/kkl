
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QDir>

#include "../../../profile/cpp/Profile/include/ambiesoft.profile.h"
#include "../../../lsMisc/stdQt/stdQt.h"

#include "settings.h"

#include "ckklwindow.h"

using namespace Ambiesoft;


bool ReadSettings()
{
    QString a = pathCombine(QDir().homePath(),".kkl","kkl.conf");

    int testvalue = static_cast<int>(time(nullptr));
    Profile::WriteInt("TEST", "TESTVALUE",testvalue,a.toStdString().c_str());

    int t;
    Profile::GetInt("TEST","TESTVALUE",-1,t,a.toStdString().c_str());

    if(testvalue != t)
        return false;

    std::string s;
    HashIniHandle hih = Profile::ReadAll(a.toStdString());

    Profile::GetString("settings", "hot key", "", s, hih);
    gSettings.hotKey = s.c_str();

    return true;
}
int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("KKL");
    QCoreApplication::setApplicationVersion("3.01");

    Q_INIT_RESOURCE(kkl);
    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr,
                              QApplication::applicationName(),
                              QObject::tr("System tray is not available on this system."));
        return 1;
    }

    if(!ReadSettings())
        return 1;

    CkklWindow window;
    // window.show();

    return app.exec();
}
