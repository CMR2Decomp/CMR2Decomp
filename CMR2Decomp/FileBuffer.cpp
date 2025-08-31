#include "FileBuffer.h"
#include "GenericFileLoader.h"
#include "Graphics.h"
#include "InstallInfo.h"
#include "main.h"

#include <stdio.h>

byte *CFileBuffer::m_unk0x00520f1c;
int CFileBuffer::m_unk0x0066461c;
int CFileBuffer::m_unk0x00664620;

unsigned int FUN_004bec70(void *param1)
{
    return -2;
}

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
void *__stdcall CFileBuffer::GetGenericFileBuffer(char *fileName, BOOL isLocalFile)
{
    // isLocalFile is basically is it on the HDD? this function is called by loadnetworkleaderboards,loadcontrollerconfig,etc. with param2 as 1
    void *unk0x004bdee0, *lpBuffer;
    char *unk004be660Out;
    DWORD fileAttributes, fileSize, fileSizeRead;
    int iResult, iNoCDErrorMessageResult, iVar4;
    BOOL bDoesFileExist;
    HANDLE hFile;
    char _fileName[MAX_PATH];
    size_t size;
    Graphics *pGraphics;

    lpBuffer = NULL;
    bDoesFileExist = FALSE;
    sprintf(_fileName, fileName);

    do
    {
        unk0x004bdee0 = FUN_004bdee0(_fileName, m_unk0x00520f1c);
        if (!unk0x004bdee0)
        {
            pGraphics = g_pGraphics;

            // should be an install/cd file
            if (!isLocalFile && pGraphics)
            {
                // flip gdi surface
                if (pGraphics->pDD7 != NULL)
                {
                    pGraphics->pDD7->FlipToGDISurface();
                    ShowCursor(TRUE);
                }

                // show the no cd error message
                if (CInstallInfo::ShowNoCDErrorMessage())
                    // check again
                    unk0x004bdee0 = FUN_004bdee0(_fileName, m_unk0x00520f1c);
            }
        }
    } while (!unk0x004bdee0);

    ShowCursor(FALSE);
    ShowWindow(CMain::m_hWndList[CMain::m_hWndIx], SW_RESTORE);

    // make sure file exists
    fileAttributes = GetFileAttributesA(_fileName);
    if (fileAttributes == -1)
        return NULL;

    // retry counter?
    if (50 > ++m_unk0x0066461c)
        GetGenericFileBuffer(_fileName, isLocalFile);
    else
    {
        iResult = FUN_004be660(unk0x004bdee0, &unk004be660Out, 8);
        // check if its a BFL
        if (iResult == 8 && unk004be660Out[0x10] == 0x43 && unk004be660Out[0x11] == 0x4d && unk004be660Out[0x12] == 0x50 && unk004be660Out[0x13] == 0x52)
        {
            if (size == INVALID_FILE_SIZE)
                return NULL;

            lpBuffer = AllocateLockedBuffer(size);
            CGenericFileLoader::m_unk0x00663fe8 = size;
            FUN_004be660(unk0x004bdee0, lpBuffer, size);
            bDoesFileExist = true;
        }

        FUN_004bec70(unk0x004bdee0);

        if (!bDoesFileExist)
        {
            hFile = CreateFileA(_fileName, GENERIC_READ, 1, NULL, 3, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile != INVALID_HANDLE_VALUE)
            {
                pGraphics = g_pGraphics;
                if (pGraphics)
                {
                    if (pGraphics->pDD7 != NULL)
                        pGraphics->pDD7->FlipToGDISurface();

                    fileAttributes = GetFileAttributesA(_fileName);
                    if (fileAttributes == -1)
                    {
                        // another retry counter?
                        if (50 > ++m_unk0x00664620)
                            GetGenericFileBuffer(_fileName, isLocalFile);

                        return NULL;
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
                    return lpBuffer;
                }
            }
        }
    }
}

// STUB: CMR2 0x004bdee0
void *__stdcall CFileBuffer::FUN_004bdee0(char *fileName, void *param_2)
{
    // todo: implement
    return 0;
}

// STUB: CMR2 0x004be660
size_t CFileBuffer::FUN_004be660(void *param_1, void *param_2, size_t param_3)
{
    return NULL;
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
