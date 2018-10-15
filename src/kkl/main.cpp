
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QMap>

#include "../../../profile/cpp/Profile/include/ambiesoft.profile.h"
#include "../../../lsMisc/stdQt/stdQt.h"
#include "../../../lsMisc/stdQt/runguard.h"

#include "../settings.h"

#include "ckklwindow.h"

using namespace Ambiesoft;




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
