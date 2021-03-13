#include <QMessageBox>
#include <QApplication>
#include <QDir>

#include "../../profile/cpp/Profile/include/ambiesoft.profile.h"
#include "../../../lsMisc/stdQt/stdQt.h"

#include "settings.h"

Settings gSettings;
QMap<QString, KKLItem> gItems;

using namespace Ambiesoft;
using namespace AmbiesoftQt;

static bool testIniFile(const QString& inifile)
{
    int testvalue = static_cast<int>(time(nullptr));
    Profile::WriteInt("TEST", "TESTVALUE",testvalue,inifile.toStdString().c_str());

    int t;
    Profile::GetInt("TEST","TESTVALUE",-1,t,inifile.toStdString().c_str());

    if(testvalue != t)
    {
        QMessageBox::critical(nullptr,
                              QApplication::applicationName(),
                              QObject::tr("Failed to write to '%1'.").arg(inifile));
        return false;
    }
    return true;
}
bool ReadSettings()
{

    QString inidir = QDir().homePath();
    QDir(inidir).mkdir(".kkl");
    inidir = pathCombine(inidir, ".kkl");
    if(!QFileInfo(inidir).isDir())
    {
        QMessageBox::critical(nullptr,
                              QApplication::applicationName(),
                              QObject::tr("Failed to create directory '%1'.").arg(inidir));

    }
    {
        QString confpath = pathCombine(inidir, "kkl.conf");

        if(!testIniFile(confpath))
            return false;

        std::string s;
        Profile::CHashIni hih(Profile::ReadAll(confpath.toStdString()));

        Profile::GetString("settings", "hot key", "ALT+2", s, hih);
        gSettings.hotKey = s.c_str();
    }

    {
        // read ini
        QString inipath = pathCombine(inidir, "kkl.ini");

        if(!testIniFile(inipath))
            return false;

        Profile::CHashIni hih(Profile::ReadAll(inipath.toStdString()));

        std::string basename("command name");
        std::string basekey("command key");
        std::string basetype("command type");
        std::string baseexe("command exe");
        std::string basefile("command file");
        std::string basepriority("command priority");
        int count = 0;
        Profile::GetInt("settings", "command count", 0, count, hih);
        for(int i=0 ; i < count ; ++i)
        {
            std::string strI = std::to_string(i);

            std::string secname = basename + strI;
            std::string seckey = basekey + strI;
            std::string sectype = basetype + strI;
            std::string secexe = baseexe + strI;
            std::string secfile = basefile + strI;
            std::string secpriority = basepriority + strI;

            std::string valname;
            std::string valkey;
            int valtype;
            std::string valexe;
            std::string valfile;
            int valpriority;


            Profile::GetString("commands", secname, "", valname, hih);
            Profile::GetString("commands", seckey, "", valkey, hih);
            Profile::GetInt("commands", sectype, 0, valtype, hih);
            Profile::GetString("commands", secexe, "", valexe, hih);
            Profile::GetString("commands", secfile, "", valfile, hih);
            Profile::GetInt("commands", secpriority, 0, valpriority, hih);

            gItems.insert(QString(valkey.c_str()),
                          KKLItem(
                              QString(valname.c_str()),
                              QString(valkey.c_str()),
                              valtype,
                              QString(valexe.c_str()),
                              QString(valfile.c_str())
                                 )
                          );
        }
    }
    return true;
}
