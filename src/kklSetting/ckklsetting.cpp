#include <vector>
#include <string>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QTableWidgetItem>

#include "../../../profile/cpp/Profile/include/ambiesoft.profile.h"
#include "../../../lsMisc/stdQt/stdQt.h"

#include "../settings.h"

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

//    QString iniPath = pathCombine(QApplication::applicationDirPath(),
//                                  QApplication::applicationName() + ".ini");
//    qDebug() << "ini path is " << iniPath;

//    bool bIniExists = QFile::exists(iniPath);

//    try
//    {
//        Profile::ReadAll(toOsdString(iniPath), true);
//    }
//    catch(file_not_found_error&)
//    {
//        if(bIniExists)
//        {
//            QMessageBox::warning(this,
//                                 QApplication::applicationName(),
//                                 tr("'%1' not found").arg(iniPath));
//            return;
//        }
//    }
//    catch(file_not_opened_error&)
//    {
//        if(bIniExists)
//        {
//            QMessageBox::warning(this,
//                                 QApplication::applicationName(),
//                                 tr("'%1' not found").arg(iniPath));
//            return;
//        }
//    }

    ui->keySequenceEdit->setKeySequence(QKeySequence(gSettings.hotKey));


    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(gItems.count());

    KKLIterator it;
    int i=0;
    for (it = gItems.begin(); it != gItems.end(); ++it, ++i)
    {
        QTableWidgetItem* pItem = new QTableWidgetItem();
        pItem->setText(it.key());
        ui->tableWidget->setItem(i, 0, pItem);

        KKLItem& item = gItems[it.key()];

        // type
        pItem = new QTableWidgetItem();
        pItem->setText(item.typeAsString());
        ui->tableWidget->setItem(i, 1, pItem);


        // exe
        pItem = new QTableWidgetItem();
        pItem->setText(item.Exe());
        ui->tableWidget->setItem(i, 2, pItem);

        // file
        pItem = new QTableWidgetItem();
        pItem->setText(item.File());
        ui->tableWidget->setItem(i, 3, pItem);
    }

    initialized_ = true;
}

CkklSetting::~CkklSetting()
{
    delete ui;
}

void CkklSetting::closeEvent(QCloseEvent *event)
{
    qDebug() << "Close" << event;
}

void CkklSetting::on_buttonBox_accepted()
{
    KKLMap newItems;
    for(int i=0 ; i < ui->tableWidget->rowCount(); ++i)
    {
        QString key = ui->tableWidget->item(i, 0)->text();

        // TODO save
    }
}
