#include <QApplication>
#include <QMessageBox>

#include "../../../lsMisc/stdQt/stdQt.h"
#include "../../../lsMisc/stdQt/runguard.h"

#include "../settings.h"
#include "ckklsetting.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RunGuard guard("kkl-runguard");
    if (!guard.tryToRun())
    {
        QMessageBox::critical(nullptr,
                              QApplication::applicationName(),
                              QObject::tr("Another instance is already running."));

        return 0;
    }


    if(!ReadSettings())
        return 1;


    CkklSetting w;
    if(!w.initialized())
        return 1;

    w.show();

    return a.exec();
}
