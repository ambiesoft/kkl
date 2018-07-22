#include <QString>

#include "osd.h"

#if defined(Q_OS_WIN) || defined(Q_OS_WINCE)
    std::wstring toOsdString(const QString& s)
    {
        return s.toStdWString();
    }
#else
    std::string toOsdString(const QString& s)
    {
        return s.toStdString();
    }
#endif

