#ifndef _GENERIC_FILE_LOADER_H
#define _GENERIC_FILE_LOADER_H

#include <windows.h>

struct GenericFile
{
    void *buffer;
    unsigned int fileSize;
    BOOL didFileLoad;
};

class CGenericFileLoader
{
public:
    // GLOBAL: CMR2 0x00818250
    static GenericFile m_genericFile;
    // GLOBAL: CMR2 0x00663fe8
    static int m_unk0x00663fe8;

    // TODO: should this not be a static class? seems silly to pass this in like this
    static bool __stdcall FUN_004a9d70(GenericFile *file, char *fileName);
    static bool __stdcall FUN_004a9c30(void *param_1, GenericFile *param_2);
    static int GetGenericFileSize(void);
    static void *__stdcall GetGenericFileBuffer(void *param1, BOOL param2);
};

#endif
