#include "FileBuffer.h"
#include "GenericFileLoader.h"
#include "Graphics.h"
#include "InstallInfo.h"
#include "main.h"
#include "BFL.h"

#include <stdio.h>

char CFileBuffer::m_unk0x00520f1c[4]; // seems to be an fopen param? "rb"
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
    BFLHeader pFileHeaderOut;
    DWORD fileAttributes, fileSize, fileSizeRead;
    int iHeaderSize;
    BOOL bIsBFL;
    HANDLE hFile;
    char _fileName[MAX_PATH];
    // Graphics *pGraphics;
    IDirectDraw7 *pDD7;

    lpBuffer = NULL;
    bIsBFL = FALSE;
    sprintf(_fileName, fileName);

    unk0x004bdee0 = FUN_004bdee0(_fileName, m_unk0x00520f1c);
    if (!unk0x004bdee0)
    {
        if (!isLocalFile)
        {
            // should be an install/cd file
            if (g_pGraphics)
            {
                // flip gdi surface
                pDD7 = *g_pGraphics->pDD7;
                if (pDD7 != NULL)
                {
                    pDD7->FlipToGDISurface();
                    ShowCursor(TRUE);

                    do
                    {
                        if (CInstallInfo::ShowNoCDErrorMessage())
                            unk0x004bdee0 = FUN_004bdee0(_fileName, m_unk0x00520f1c);
                    } while (!unk0x004bdee0);

                    ShowCursor(FALSE);
                    ShowWindow(CMain::m_hWndList[CMain::m_hWndIx], SW_RESTORE);
                }
            }
        }
    }

    if (g_pGraphics)
    {
        if (g_pGraphics->pDD7)
            (*g_pGraphics->pDD7)->FlipToGDISurface();
    }

    // make sure file exists
    fileAttributes = GetFileAttributesA(_fileName);
    if (fileAttributes == -1)
    {
        // retry counter?
        if (++m_unk0x0066461c < 50)
            GetGenericFileBuffer(fileName, isLocalFile);
        else
            return NULL;
    }

    // check if its a BFL
    iHeaderSize = FUN_004be660(unk0x004bdee0, &pFileHeaderOut, 8);
    if (iHeaderSize == 8 && pFileHeaderOut.ident[0] == 0x43 && pFileHeaderOut.ident[1] == 0x4d && pFileHeaderOut.ident[2] == 0x50 && pFileHeaderOut.ident[3] == 0x52)
    {
        if (pFileHeaderOut.archiveSize == INVALID_FILE_SIZE)
            return NULL;

        lpBuffer = AllocateLockedBuffer(pFileHeaderOut.archiveSize);
        CGenericFileLoader::m_unk0x00663fe8 = pFileHeaderOut.archiveSize;
        FUN_004be660(unk0x004bdee0, lpBuffer, pFileHeaderOut.archiveSize);
        bIsBFL = true;
    }
    else

        FUN_004bec70(unk0x004bdee0);

    if (!bIsBFL)
    {
        hFile = CreateFileA(_fileName, GENERIC_READ, 1, NULL, 3, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            if (g_pGraphics)
            {
                if (g_pGraphics->pDD7)
                    (*g_pGraphics->pDD7)->FlipToGDISurface();
            }
        }
        else
        {

            fileAttributes = GetFileAttributesA(_fileName);
            if (fileAttributes == -1)
            {
                // another retry counter?
                if (50 > ++m_unk0x00664620)
                    GetGenericFileBuffer(_fileName, isLocalFile);
            }
            else
            {

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
        }
    }

    return lpBuffer;
}

// STUB: CMR2 0x004bdee0
void *__stdcall CFileBuffer::FUN_004bdee0(char *fileName, char *param_2)
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
