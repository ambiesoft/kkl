#include <QMessageBox>
#include <QMenu>
#include <QCloseEvent>
#include <QApplication>
#include <QPainter>
#include <QDebug>

#include <ctime>

#include "../../../qglobalshortcut/src/qglobalshortcut.h"

#include "settings.h"

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
    createTrayIcon();
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
void CkklWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(showVersionAction);
    trayIconMenu->addAction(closeAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
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

    this->hide();
}
void CkklWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect geo = this->geometry();

//    int x, y, width, height;

//    x = geo.x()-10;
//    y = geo.y()-10;
//    width = geo.width()-3;
//    height = geo.height()-5;

    // painter.fillRect(x, y, width, height, QColor(220,220,220));

    painter.drawText(geo, "aaaaaa", QTextOption(Qt::AlignVCenter));
}
