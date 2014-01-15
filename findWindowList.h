#ifndef FINDWINDOWLIST_H
#define FINDWINDOWLIST_H

#include <QDebug>
#include <QString>
#include <string>
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include "Bot.h"
using namespace std;

extern HWND windowHandle;

BOOL IsAltTabWindow(HWND hwnd);
BOOL CALLBACK MyEnumProc(HWND hWnd, LPARAM lParam);
void findWindowList(void);

#endif // FINDWINDOWLIST_H
