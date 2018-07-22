#include <QApplication>

#include "ckklsetting.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CkklSetting w;
    if(!initialized())
        return 1;

    w.show();

    return a.exec();
}
