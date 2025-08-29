#include "GenericFileLoader.h"

GenericFile CGenericFileLoader::m_genericFile;
int CGenericFileLoader::m_unk0x00663fe8;

// FUNCTION: CMR2 0x004a9d70
bool __stdcall CGenericFileLoader::FUN_004a9d70(GenericFile *file, char *buffer)
{
    file->didFileLoad = FALSE;
    if (FUN_004a9c30(buffer, file) != FALSE)
        return file->didFileLoad = TRUE;

    return false;
}

// FUNCTION: CMR2 0x004a9c30
bool __stdcall CGenericFileLoader::FUN_004a9c30(void *param_1, GenericFile *param_2)
{
    param_2->buffer = GetGenericFileBuffer(param_1, 0);
    if (param_2->buffer != NULL)
    {
        param_2->fileSize = GetGenericFileSize();
        return true;
    }

    param_2->fileSize = 0;
    return false;
}

// STUB: CMR2 0x004aa220
void *__stdcall CGenericFileLoader::GetGenericFileBuffer(void *param1, BOOL param2)
{
    // todo: implementation
    // todo: check param2
    return 0;
}

// FUNCTION: CMR2 0x004aa590
int CGenericFileLoader::GetGenericFileSize(void)
{
    return m_unk0x00663fe8;
}
