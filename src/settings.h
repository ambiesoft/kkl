#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QElapsedTimer>
#include <QMap>

struct Settings
{
    QString hotKey;
};
extern Settings gSettings;


class KKLItem
{
    QString name_;
    QString key_;
    int type_;
    QString exe_;
    QString file_;

public:
    KKLItem() = default;
    KKLItem(const QString& name,
            const QString& key,
            int type,
            const QString& exe,
            const QString& file) :
        name_(name),
        key_(key),
        type_(type),
        exe_(exe),
        file_(file) {}
    void overMe(const KKLItem& that) {
        this->name_ = that.name_;
        this->key_=that.key_;
        this->type_=that.type_;
        this->exe_=that.exe_;
        this->file_=that.file_;
    }
    KKLItem(const KKLItem& that) {
        overMe(that);
    }

    const KKLItem& operator=(const KKLItem& item) {
        if(this != &item) {
            overMe(item);
        }
        return *this;
    }
    QString Exe() const {
        return exe_;
    }
    QString File() const {
        return file_;
    }
    QString typeAsString() const {
        return QString::number(type_);
    }
};

typedef QMap<QString, KKLItem>::iterator KKLIterator;
typedef QMap<QString, KKLItem> KKLMap;

extern KKLMap gItems;


bool ReadSettings();

#endif // SETTINGS_H
