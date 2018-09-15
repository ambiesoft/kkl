#ifndef CKKLWINDOW_H
#define CKKLWINDOW_H

#include <QWidget>
#include <QSystemTrayIcon>

#include "../../../qglobalshortcut/src/qglobalshortcut.h"

class CkklWindow : public QWidget
{
    Q_OBJECT
    using ParentClass = QWidget;

    bool initialized_ = false;

private:
    void createTrayIcon();
public:
    explicit CkklWindow(QWidget *parent = nullptr);
    bool initialized() const {
        return initialized_;
    }
signals:

public slots:
    void showVersion();


protected slots:
    void onHotkeyShow();

protected:
    void closeEvent(QCloseEvent *event) override;
    void focusOutEvent(QFocusEvent* event) override;
    void paintEvent(QPaintEvent*) override;

private:
    QAction *showVersionAction;
    QAction *closeAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QGlobalShortcut gs_;
};

#endif // CKKLWINDOW_H
