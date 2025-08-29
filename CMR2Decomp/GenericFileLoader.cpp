#include "GenericFileLoader.h"

GenericFile CGenericFileLoader::m_genericFile;

// STUB: CMR2 0x004a9d70
unsigned int __stdcall CGenericFileLoader::FUN_004a9d70(GenericFile *file, char *fileName)
{
    unsigned int uVar1 = 0;

    file->didFileLoad = 0;
    // uVar1 = FUN_004a9c30(param_2, &file->buffer);
    if (uVar1 != '\0')
    {
        file->didFileLoad = 1;
        return 1;
    }
    return uVar1 & 0xffffff00;
}
