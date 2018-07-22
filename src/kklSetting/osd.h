#ifndef OSD_H
#define OSD_H


#if defined(Q_OS_WIN) || defined(Q_OS_WINCE)
    std::wstring toOsdString(const QString& s);
#else
    std::string toOsdString(const QString& s);
#endif



#endif // OSD_H
