#include <QMessageBox>
#include <QMenu>
#include <QCloseEvent>
#include <QApplication>
#include <QPainter>
#include <QDebug>
#include <QPen>
#include <QTextDocument>
#include <QProcess>

#include <ctime>

#include "../../../qglobalshortcut/src/qglobalshortcut.h"

#include "../settings.h"
#include "osd.h"

#include "ckklwindow.h"

CkklWindow::CkklWindow(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool);

    // Qt::Tool cause closing window not close the app.
    // This flag makes it close the app.
    qDebug() << "QuiteOnClose=" << testAttribute(Qt::WA_QuitOnClose);
    setAttribute(Qt::WA_QuitOnClose);
    qDebug() << "QuiteOnClose=" << testAttribute(Qt::WA_QuitOnClose);
    QApplication::setQuitLockEnabled(false);

    showVersionAction = new QAction(tr("Show &Version"), this);
    connect(showVersionAction, &QAction::triggered,
            this, &CkklWindow::showVersion);

    closeAction = new QAction(tr("&Close"), this);
    connect(closeAction, &QAction::triggered,
            this, &CkklWindow::close);



    // Prepare global hotkeys
    do
    {
        if(gSettings.hotKey.isEmpty())
        {
            QMessageBox::critical(nullptr,
                                  QApplication::applicationName(),
                                  tr("Hot-key is empty."));
            break;
        }
        QKeySequence qks(gSettings.hotKey);

        // if hot-key is valid, toString() returns its value otherwise returns "".
        qDebug() << QString("setting='%1', toString()=='%2'").arg(gSettings.hotKey).arg(qks.toString());
        if(qks.toString().compare(gSettings.hotKey, Qt::CaseInsensitive) != 0)
        {
            QMessageBox::critical(nullptr,
                                  QApplication::applicationName(),
                                  QString(tr("'%1' is not a valid hot-key")).arg(gSettings.hotKey));
            break;
        }
        // Register hot-key to system
        if(!gs_.setKey(qks))
        {
            QMessageBox::critical(nullptr,
                                  QApplication::applicationName(),
                                  QString(tr("Registering hot-key with '%1' is failed")).arg(gSettings.hotKey));
            break;
        }

        connect(&gs_, SIGNAL(activated()),
                this, SLOT(onHotkeyShow()));
    } while(false);

    create();

    // show tray icon
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(showVersionAction);
    trayIconMenu->addAction(closeAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    QIcon icon(":images/icon.ico");
    Q_ASSERT(!icon.isNull());
    if(icon.isNull())
    {
        QMessageBox::critical(nullptr,
                              QApplication::applicationName(),
                              tr("icon not found"));
        return;
    }
    trayIcon->setIcon(icon);
    trayIcon->show();



    initialized_ = true;
}

void CkklWindow::onHotkeyShow()
{
    qDebug() << "Timer" << QString::number(std::clock());
    resize(240, 20);
    move(300,300);
    this->show();
    this->activateWindow();
    qDebug() << "Timer" << QString::number(std::clock());
}
void CkklWindow::showVersion()
{
    QMessageBox::about(nullptr,
                       QCoreApplication::applicationName(),
                       QString("%1 version %2").
                       arg(QCoreApplication::applicationName()).
                       arg(QCoreApplication::applicationVersion()));
}
void CkklWindow::closeEvent(QCloseEvent *event)
{
    // Q_UNUSED(event);
    event->accept();

    trayIcon->hide();
    delete trayIcon;
    trayIcon=nullptr;

    ParentClass::closeEvent(event);

    // we need this, becase QApplication::quitOnLastWindowClosed() is false.
    QApplication::quit();
}

void CkklWindow::focusOutEvent(QFocusEvent* event)
{
    ParentClass::focusOutEvent(event);

    currentKeys_.clear();
    this->hide();
}
void CkklWindow::paintEvent(QPaintEvent*)
{
    qDebug() << "Paint" << currentKeys_;
    QPainter painter(this);

//    int width = size().width() - 3;
//    int height = size().height() - 5;

//    painter.fillRect(0, 0, width, height, QColor(220,220,220));


//    QPen myPen(Qt::black, 2, Qt::SolidLine);
//    painter.setPen(myPen);
//    painter.drawText(0,0, currentKeys_);//, QTextOption(Qt::AlignVCenter));

    QTextDocument td;
    td.setHtml(currentKeys_);
    td.drawContents(&painter);
}

QString dq(const QString& s)
{
    if(s.isEmpty())
        return "\"\"";

    if(s[0]=='"')
        return s;

    for(auto&& c : s)
    {
        if(c==' ' || c=='\t')
        {
            return "\"" + s + "\"";
        }
    }
    return s;
}
//void CkklWindow::launchApp(const KKLItem& item)
//{
//    QString startcmd = dq(item.Exe());
//    if(!item.File().isEmpty())
//        startcmd += " " + item.File();

//    QProcess process;

//    qDebug() << "Launch" << startcmd;
//    process.start(startcmd);
//}

void CkklWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event;

    bool isReturnKey = false;
    if(event->key() == Qt::Key::Key_Backspace)
    {
        if(!currentKeys_.isEmpty())
            currentKeys_.remove(currentKeys_.length()-1,1);
        update();
        return;
    }
    else if(event->key() == Qt::Key::Key_Return)
    {
        isReturnKey = true;
    }
    else if( event->text().size() != 1)
    {
        return;
    }

    QString newKeys = currentKeys_ + event->text();

    KKLIterator it;

    if(!isReturnKey)
    {
        // first, test match
        for (it = gItems.begin(); it != gItems.end(); ++it)
        {
            // match
            if(it.key()==newKeys)
            {
                launchApp(this,it.value());
                currentKeys_ = "";
                update();
                hide();
                return;
            }
        }
    }


    // not match, find kouho
    QList<KKLItem> newkouho;
    QList<KKLItem> currentkouho;
    for (it = gItems.begin(); it != gItems.end(); ++it)
    {
        // is kouho?
        if(it.key().startsWith(newKeys))
        {
            newkouho.append(it.value());
        }
        if(it.key().startsWith(currentKeys_))
        {
            currentkouho.append(it.value());
        }
    }

    if(isReturnKey && currentkouho.size()==1)
    {
        launchApp(this, currentkouho[0]);
        currentKeys_.clear();
        update();
        hide();
        return;
    }

    if(newkouho.isEmpty())
    {
        // new keys have no kouho, cancel it
        return;
    }

    currentKeys_.append( event->text());
    this->update();
}
