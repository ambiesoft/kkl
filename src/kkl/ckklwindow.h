#ifndef CKKLWINDOW_H
#define CKKLWINDOW_H

#include <QWidget>
#include <QSystemTrayIcon>

class CkklWindow : public QWidget
{
    Q_OBJECT
    using ParentClass = QWidget;

private:
    void createTrayIcon();
public:
    explicit CkklWindow(QWidget *parent = nullptr);

signals:

public slots:
    void showVersion();

protected:
    void closeEvent(QCloseEvent *event) override;
private:
    QAction *showVersionAction;
    QAction *closeAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // CKKLWINDOW_H
