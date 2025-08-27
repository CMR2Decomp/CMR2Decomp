#ifndef _MAIN_H
#define _MAIN_H

#include <windows.h>

unsigned char Initialize(HINSTANCE hInstance, unsigned char param2, char *param3);
BOOL __stdcall CreateGameWindow(HINSTANCE hInstance, HWND *pHWND, LPCSTR sWindowName, WNDPROC *param_4);

#endif
