#include "Logger.h"

// GLOBAL: CMR2 0x00667344
unsigned int unk0x00667344;

BOOL CLogger::bIsLogFileOpen;
char CLogger::unk0x00667204[320];
unsigned int CLogger::unk0x00667348;
HANDLE CLogger::hLogFileHandle;

// FUNCTION: CMR2 0x004ab620
void CLogger::OpenLogFile(LPCSTR file)
{
    lstrcpyA(unk0x00667204, file);
    unk0x00667344 = 0;
    hLogFileHandle = CreateFileA(file, GENERIC_WRITE, 0, NULL, 2, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hLogFileHandle != INVALID_HANDLE_VALUE)
        bIsLogFileOpen = TRUE;
}

// FUNCTION: CMR2 0x004ab670
void CLogger::LogToFile(LPCSTR str)
{
    LPCSTR lpBuffer;
    DWORD nSizeToWrite;
    DWORD nWritten;
    const char n = 0xd;
    const char r = 0xa;

    if (unk0x00667348 == 0 && bIsLogFileOpen != FALSE)
    {
        lpBuffer = str;
        nSizeToWrite = lstrlenA(str);
        WriteFile(hLogFileHandle, lpBuffer, nSizeToWrite, &nWritten, NULL);
        WriteFile(hLogFileHandle, &n, 1, &nWritten, NULL);
        WriteFile(hLogFileHandle, &r, 1, &nWritten, NULL);
        FlushFileBuffers(hLogFileHandle);
    }
}

// FUNCTION: CMR2 0x004ab6f0
void CLogger::CloseLogFile(void)
{
    CloseHandle(hLogFileHandle);
    bIsLogFileOpen = FALSE;
}
