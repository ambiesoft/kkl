#include <vector>
#include <string>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

#include "../../../profile/cpp/Profile/include/ambiesoft.profile.h"
#include "../../../lsMisc/stdQt/stdQt.h"

#include "osd.h"
#include "ckklsetting.h"
#include "ui_ckklsetting.h"

using namespace Ambiesoft;
using namespace std;

CkklSetting::CkklSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CkklSetting)
{
    ui->setupUi(this);

    QString iniPath = pathCombine(QApplication::applicationDirPath(),
                                  QApplication::applicationName() + ".ini");
    qDebug() << "ini path is " << iniPath;

    bool bIniExists = QFile::exists(iniPath);

    try
    {
        Profile::ReadAll(toOsdString(iniPath), true);
    }
    catch(file_not_found_error&)
    {
        if(bIniExists)
        {
            QMessageBox::warning(this,
                                 QApplication::applicationName(),
                                 tr("'%1' not found").arg(iniPath));
            return;
        }
    }
    catch(file_not_opened_error&)
    {
        if(bIniExists)
        {
            QMessageBox::warning(this,
                                 QApplication::applicationName(),
                                 tr("'%1' not found").arg(iniPath));
            return;
        }
    }

    initialized_ = true;
}

CkklSetting::~CkklSetting()
{
    delete ui;
}
