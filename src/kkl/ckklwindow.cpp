#include <QMessageBox>
#include <QMenu>
#include <QCloseEvent>
#include "ckklwindow.h"

CkklWindow::CkklWindow(QWidget *parent) : QWidget(parent)
{
    resize(240, 60);
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
    QMessageBox::about(this, "KKL", "ffffffffff");
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
