#ifndef _FILE_BUFFER_H
#define _FILE_BUFFER_H

#include <windows.h>

class CFileBuffer
{
public:
    static void *__stdcall AllocateLockedBuffer(size_t size);
    static void *__stdcall CFileBuffer::ReallocateLockedBuffer(void *buffer, size_t iSize);
    static void *__stdcall GetGenericFileBuffer(char *fileName, BOOL param2);
    static void __stdcall FreeGenericFileBuffer(void *buffer);

    // unknowns
    static void *__stdcall FUN_004bdee0(char *fileName, void *param_2);
    static size_t FUN_004be660(void *param_1, void *param_2, size_t param_3);
    static byte *m_unk0x00520f1c;
    static int m_unk0x0066461c;
    static int m_unk0x00664620;
};

#endif
