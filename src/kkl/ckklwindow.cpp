#include <QMessageBox>
#include <QMenu>
#include <QCloseEvent>
#include <QApplication>
#include <QPainter>

#include "../../qglobalshortcut/src/qglobalshortcut.h"

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

    createTrayIcon();
    QIcon icon(":images/icon.ico");
    Q_ASSERT(!icon.isNull());
    trayIcon->setIcon(icon);
    trayIcon->show();


    // Prepare global hotkeys
    gs_.setKey(QKeySequence("Alt+2"));

    connect(&gs_, SIGNAL(activated()),
            this, SLOT(onHotkeyShow()));
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
