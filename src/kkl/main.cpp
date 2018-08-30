
#include <QApplication>
#include <QWidget>
#include <QMessageBox>

#include "ckklwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("KKL");
    QCoreApplication::setApplicationVersion("3.01");

    Q_INIT_RESOURCE(kkl);
    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("KKL"),
                              QObject::tr("System tray is not available on this system."));
        return 1;
    }

    CkklWindow window;
    window.show();

    return app.exec();
}
