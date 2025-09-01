#ifndef _MAIN_H
#define _MAIN_H

#include <windows.h>

class CMain
{
public:
    static unsigned char Initialize(HINSTANCE hInstance, unsigned char param2, LPSTR param3);
    static BOOL __stdcall CreateGameWindow(HINSTANCE hInstance, HWND *pHWND, LPCSTR sWindowName, WNDPROC param_4);
    static LRESULT __stdcall MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static void FUN_0049c130(void);

    // GLOBAL: CMR2 0x00663c84
    static HWND m_hWndList[1];
    // GLOBAL: CMR2 0x00663dac
    static int m_hWndIx;
    // GLOBAL: CMR2 0x00663c70
    static int m_unk0x00663c70;

private:
    // GLOBAL: CMR2 0x00663db0
    static HINSTANCE m_hInstance;
    // GLOBAL: CMR2 0x00511430
    static char m_gameName[20];
    // GLOBAL: CMR2 0x00520c74
    static char m_logFileLocation[14];
    // GLOBAL: CMR2 0x00520c54
    static char m_logFileHeader1[29];
    // GLOBAL: CMR2 0x00520c34
    static char m_logFileAsterisks[29];
    // GLOBAL: CMR2 0x0052ea5c
    static char m_logFileBlankLine[1];
    // GLOBAL: CMR2 0x00520bf4
    static char m_logFileFinishedNormally[30];
    // GLOBAL: CMR2 0x00520bf0
    static BOOL m_isShowingCursor;
};

#endif
