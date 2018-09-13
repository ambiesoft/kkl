#include <QMessageBox>
#include <QMenu>
#include <QCloseEvent>
#include <QApplication>
#include <QPainter>
#include <QDebug>

#include "../../qglobalshortcut/src/qglobalshortcut.h"

#include "settings.h"

#include "ckklwindow.h"

CkklWindow::CkklWindow(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);

    resize(240, 20);
    move(0,0);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool);

    // Qt::Tool cause closing window not close the app.
    // This flag makes it close the app.
    setAttribute(Qt::WA_QuitOnClose);


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
            QMessageBox::critical(this,
                                  QApplication::applicationName(),
                                  tr("Hot-key is empty."));
            break;
        }
        QKeySequence qks(gSettings.hotKey);

        qDebug() << QString("setting='%1', toString()=='%2'").arg(gSettings.hotKey).arg(qks.toString());
        if(qks.toString() != gSettings.hotKey)
        {
            QMessageBox::critical(this,
                                  QApplication::applicationName(),
                                  QString(tr("%1 is invalid hot-key")).arg(gSettings.hotKey));
            break;
        }
        gs_.setKey(qks); // "Alt+2"));

        connect(&gs_, SIGNAL(activated()),
                this, SLOT(onHotkeyShow()));
    } while(false);

    // show tray icon
    createTrayIcon();
    QIcon icon(":images/icon.ico");
    Q_ASSERT(!icon.isNull());
    trayIcon->setIcon(icon);
    trayIcon->show();
}

void CkklWindow::onHotkeyShow()
{
    this->show();
    this->activateWindow();
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
    QMessageBox::about(this,
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
