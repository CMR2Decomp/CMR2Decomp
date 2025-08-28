#ifndef _LOGGER_H_
#define _LOGGER_H

#include <windows.h>

class CLogger
{
private:
    // GLOBAL: CMR2 0x00667200
    static BOOL bIsLogFileOpen;
    // GLOBAL: CMR2 0x00667204
    static char unk0x00667204[320];
    // GLOBAL: CMR2 0x00667348
    static unsigned int unk0x00667348;
    // GLOBAL: CMR2 0x0066734c
    static HANDLE hLogFileHandle;

public:
    static void __stdcall OpenLogFile(LPCSTR file);
    static void __stdcall LogToFile(LPCSTR str);
    static void __stdcall CloseLogFile(void);
};

#endif
