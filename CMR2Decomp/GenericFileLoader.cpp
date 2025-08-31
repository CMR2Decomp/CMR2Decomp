#include "GenericFileLoader.h"
#include "FileBuffer.h"

GenericFile CGenericFileLoader::m_genericFile;
DWORD CGenericFileLoader::m_unk0x00663fe8;

// FUNCTION: CMR2 0x004a9d70
bool __stdcall CGenericFileLoader::FUN_004a9d70(GenericFile *file, char *fileName)
{
    file->didFileLoad = FALSE;
    if (FUN_004a9c30(fileName, file) != FALSE)
        return file->didFileLoad = TRUE;

    return false;
}

// FUNCTION: CMR2 0x004a9c30
bool __stdcall CGenericFileLoader::FUN_004a9c30(char *fileName, GenericFile *param_2)
{
    param_2->buffer = CFileBuffer::GetGenericFileBuffer(fileName, 0);
    if (param_2->buffer != NULL)
    {
        param_2->fileSize = GetGenericFileSize();
        return true;
    }

    param_2->fileSize = 0;
    return false;
}

// FUNCTION: CMR2 0x004aa590
int CGenericFileLoader::GetGenericFileSize(void)
{
    return m_unk0x00663fe8;
}
