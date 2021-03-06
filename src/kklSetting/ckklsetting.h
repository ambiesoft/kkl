#ifndef CKKLSETTING_H
#define CKKLSETTING_H

#include <QDialog>

namespace Ui {
class CkklSetting;
}

class CkklSetting : public QDialog
{
    Q_OBJECT

public:
    explicit CkklSetting(QWidget *parent = 0);
    ~CkklSetting();

    bool initialized() const {
        return initialized_;
    }
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CkklSetting *ui;

    bool initialized_ = false;
};

#endif // CKKLSETTING_H
