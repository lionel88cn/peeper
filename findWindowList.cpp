#include "findWindowList.h"

HWND windowHandle;

BOOL IsAltTabWindow(HWND hwnd)
{
    if (hwnd == GetShellWindow())   //Desktop
        return false;
    // Start at the root owner
    HWND hwndWalk = GetAncestor(hwnd, GA_ROOTOWNER);

    // See if we are the last active visible popup
    HWND hwndTry;
    while ((hwndTry = GetLastActivePopup(hwndWalk)) != hwndTry)
    {
        if (IsWindowVisible(hwndTry))
            break;
        hwndWalk = hwndTry;
    }
    return hwndWalk == hwnd;
}

BOOL CALLBACK MyEnumProc(HWND hWnd, LPARAM lParam)
{
    TCHAR title[500];
    ZeroMemory(title, sizeof(title));
    GetWindowText(hWnd, title, sizeof(title)/sizeof(title[0]));
    wstring nowwindow=title;
    string nowwindowstr( nowwindow.begin(), nowwindow.end() );

    if (IsAltTabWindow(hWnd) && IsWindowVisible(hWnd) && GetWindowTextLength(hWnd)>0)
    {
        _tprintf(_T("Window Found: %s\n"), title);
        QString qtString = QString::fromStdWString ( nowwindow );
        qDebug()<<"Window Found: "<<qtString<<endl;
        openedwindows.addwindow(nowwindowstr);
    }
    //if(_tcsstr(title, _T("Excel")))
    std::size_t found = nowwindowstr.find("Excel");
    if(found!=std::string::npos)
    {
        windowHandle = hWnd;
        return FALSE;
    }
    return TRUE;
}

void findWindowList(void)
{
    EnumWindows(MyEnumProc, 0);
}
