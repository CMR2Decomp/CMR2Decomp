#include "Logger.h"

// GLOBAL: CMR2 0x00667344
unsigned int unk0x00667344;

unsigned int CLogger::unk0x00667200;
char CLogger::unk0x00667204[320];
unsigned int CLogger::unk0x00667348;
HANDLE CLogger::hLogFileHandle;

// FUNCTION: CMR2 0x004ab620
void __stdcall CLogger::OpenLogFile(LPCSTR file)
{
    lstrcpyA(unk0x00667204, file);
    unk0x00667344 = 0;
    hLogFileHandle = CreateFileA(file, GENERIC_WRITE, 0, NULL, 2, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hLogFileHandle != INVALID_HANDLE_VALUE)
        unk0x00667200 = 1;
}

// FUNCTION: CMR2 0x004ab670
void __stdcall CLogger::LogToFile(LPCSTR str)
{
    LPCSTR lpBuffer;
    DWORD nSizeToWrite;
    DWORD nWritten;
    const char n = 0xd;
    const char r = 0xa;

    if (unk0x00667348 == 0 && unk0x00667200 != 0)
    {
        lpBuffer = str;
        nSizeToWrite = lstrlenA(str);
        WriteFile(hLogFileHandle, lpBuffer, nSizeToWrite, &nWritten, NULL);
        WriteFile(hLogFileHandle, &n, 1, &nWritten, NULL);
        WriteFile(hLogFileHandle, &r, 1, &nWritten, NULL);
        FlushFileBuffers(hLogFileHandle);
    }
}
