#include <Windows.h>

#include <QWidget>
#include "osd.h"

void launchApp(QWidget* widget, const KKLItem& item)
{
    SHELLEXECUTEINFO sei;
    memset(&sei, 0, sizeof(sei));

    wchar_t szT[MAX_PATH] = {0};
    if( !item.File().isEmpty() )
    {
        lstrcpy(szT, item.File().toStdWString().c_str());
    }

    sei.cbSize = sizeof(sei);
    sei.fMask  = SEE_MASK_DOENVSUBST|SEE_MASK_NOCLOSEPROCESS ;
    Q_ASSERT(IsWindow( (HWND)widget->winId()));
    sei.hwnd   = (HWND)widget->winId();
    sei.lpVerb = nullptr;

    std::wstring wsExe = item.Exe().toStdWString();
    if( !wsExe.empty())
    {
        sei.lpFile = wsExe.c_str();
        sei.lpParameters = szT;
    }
    else
    {
        Q_ASSERT(szT[0]);
        sei.lpFile = szT;
        sei.lpParameters = nullptr;
    }

    sei.lpDirectory = nullptr; // TODO
    sei.nShow = SW_SHOW;
    sei.hInstApp = nullptr;
    sei.lpIDList = nullptr;
    sei.lpClass = nullptr;
    sei.hkeyClass = nullptr;
    sei.dwHotKey = 0;
    sei.hIcon = nullptr;
    sei.hProcess = nullptr;

    if(ShellExecuteEx(&sei))
    {
        // TODO
        //                        if(item.->nPriority==7)
        //                        {
        //                            SetPriorityClass(sei.hProcess, REALTIME_PRIORITY_CLASS);
        //                        }
        CloseHandle(sei.hProcess);
    }
}
