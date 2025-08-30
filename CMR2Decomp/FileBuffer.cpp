#include "FileBuffer.h"
#include "GenericFileLoader.h"
#include "Graphics.h"
#include "InstallInfo.h"
#include "main.h"

#include <stdio.h>

void *CFileBuffer::m_unk0x00520f1c;
unsigned int CFileBuffer::m_unk0x0066461c;
unsigned int CFileBuffer::m_unk0x00664620;

// FUNCTION: CMR2 0x004aad70
void *__stdcall CFileBuffer::AllocateLockedBuffer(size_t iSize)
{
    HANDLE handle;
    void *buffer;

    handle = GlobalAlloc(0x42, iSize);
    buffer = GlobalLock(handle);
    return buffer;
}

// FUNCTION: CMR2 0x004aad90
void *__stdcall CFileBuffer::ReallocateLockedBuffer(void *buffer, size_t iSize)
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

// FUNCTION: CMR2 0x004aa220
void *__stdcall CFileBuffer::GetGenericFileBuffer(char *fileName, BOOL param2)
{
    // todo: check param2 is BOOL
    void *unk0x004bdee0, *lpBuffer;
    char unk004be660Out;
    IDirectDraw7 **dd7;
    DWORD fileAttributes, fileSize, fileSizeRead;
    int iResult;
    bool bDoesFileExist;
    HANDLE hFile;

    unk0x004bdee0 = FUN_004bdee0(fileName, m_unk0x00520f1c);
    if (!unk0x004bdee0)
    {
        if (!param2)
        {
            if (g_pGraphics != NULL)
            {
                if (g_pGraphics->pDD7 != NULL)
                {
                    (*g_pGraphics->pDD7)->FlipToGDISurface();
                    ShowCursor(TRUE);

                    while (unk0x004bdee0 == NULL)
                    {
                        if (CInstallInfo::ShowNoCDErrorMessage(TRUE))
                            unk0x004bdee0 = FUN_004bdee0(fileName, m_unk0x00520f1c);
                    }

                    ShowCursor(FALSE);
                    ShowWindow(CMain::m_hWndList[CMain::m_hWndIx], SW_RESTORE);
                    (*g_pGraphics->pDD7)->FlipToGDISurface();
                }
            }
        }
    }

    fileAttributes = GetFileAttributesA(fileName);
    if (fileAttributes == -1)
        return NULL;

    if ((m_unk0x0066461c + 1) >= 50)
        return NULL;

    iResult = FUN_004be660(unk0x004bdee0, &unk004be660Out, 8);
    if (iResult == 8)
    {
        size_t size;
        lpBuffer = AllocateLockedBuffer(size);
        CGenericFileLoader::m_unk0x00663fe8 = size;
        FUN_004be660(unk0x004bdee0, lpBuffer, size);
        bDoesFileExist = true;
    }

    if (!bDoesFileExist)
    {
        hFile = CreateFileA(fileName, GENERIC_READ, 1, NULL, 3, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            if (!g_pGraphics != NULL && g_pGraphics->pDD7)
                (*g_pGraphics->pDD7)->FlipToGDISurface();

            fileAttributes = GetFileAttributesA(fileName);
            if (fileAttributes == -1)
                return NULL;

            if ((m_unk0x00664620 + 1) >= 50)
                return NULL;

            GetGenericFileBuffer(fileName, param2);
        }

        fileSize = GetFileSize(hFile, NULL);
        CGenericFileLoader::m_unk0x00663fe8 = fileSize;
        if (fileSize == INVALID_FILE_SIZE)
            return NULL;

        lpBuffer = AllocateLockedBuffer(fileSize);
        ReadFile(hFile, lpBuffer, fileSize, &fileSizeRead, NULL);
        if (fileSizeRead != fileSize)
            return NULL;

        CloseHandle(hFile);
    }

    return lpBuffer;
}

// STUB: CMR2 0x004bdee0
void *CFileBuffer::FUN_004bdee0(char *fileName, void *param_2)
{
    // todo: implement
    return 0;
}

// STUB: CMR2 0x004be660
int CFileBuffer::FUN_004be660(void *param_1, void *param_2, size_t param_3)
{
    return 0;
}

// FUNCTION: CMR2 0x004aade0
void __stdcall CFileBuffer::FreeGenericFileBuffer(void *param1)
{
    HANDLE handle;

    handle = GlobalHandle(param1);
    GlobalUnlock(handle);
    handle = GlobalHandle(param1);
    GlobalFree(handle);
}
