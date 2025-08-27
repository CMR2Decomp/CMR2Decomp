#ifndef _MAIN_H
#define _MAIN_H

#include <windows.h>

unsigned char Initialize(HINSTANCE hInstance, unsigned char param2, LPSTR param3);
BOOL __stdcall CreateGameWindow(HINSTANCE hInstance, HWND *pHWND, LPCSTR sWindowName, WNDPROC param_4);
LRESULT __stdcall MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
