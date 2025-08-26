#include "FileBuffer.h"
#include <windows.h>

// FUNCTION: CMR2 0x004aad70
void *__stdcall AllocateLockedBuffer(size_t iSize)
{
    HANDLE handle;
    void *buffer;

    handle = GlobalAlloc(0x42, iSize);
    buffer = GlobalLock(handle);
    return buffer;
}

// FUNCTION: CMR2 0x004aad90
void *__stdcall ReallocateLockedBuffer(void *buffer, size_t iSize)
{
    HGLOBAL handle;
    UINT flags;

    if (buffer != NULL)
    {
        handle = GlobalHandle(buffer);
        GlobalUnlock(handle);
        flags = 0;
        handle = GlobalReAlloc(GlobalHandle(buffer), iSize, flags);
        return GlobalLock(handle);
    }

    handle = AllocateLockedBuffer(iSize);
    return handle;
}

// FUNCTION: CMR2 0x004aade0
void __stdcall FreeGenericFileBuffer(void *param1)
{
    HANDLE handle;

    handle = GlobalHandle(param1);
    GlobalUnlock(handle);
    handle = GlobalHandle(param1);
    GlobalFree(handle);
}
