#include "Graphics.h"
#include "Frontend.h"
#include "GameInfo.h"
#include "RegKey.h"
#include "Texture.h"
#include "main.h"
#include "Sound.h"
#include "Game.h"
#include "FileBuffer.h"
#include <basetsd.h>
#include <cstring>
#include <windef.h>
#include <wingdi.h>
#include <winnt.h>
#include <winuser.h>

// GLOBAL: CMR2 0x00660830
Graphics g_graphics;

// GLOBAL: CMR2 0x00520b74
Graphics *g_pGraphics = &g_graphics;
D3DTextureManager *CGraphics::m_pTextureManager;

char CGraphics::m_strSettingConfigurationToDefault[36] = "Setting configuration to defaults";

BOOL CGraphics::m_unk0x00520b7c = TRUE;
UINT CGraphics::m_unk0x0065fa20 = 0;
UINT CGraphics::m_unk0x0065fa28 = 0;
void* CGraphics::m_unk0x0065fa2c;
int CGraphics::m_unk0x006dd890;
int CGraphics::m_unk0x00663b1c;
Unk0x0065ff90 CGraphics::m_unk0x0065ff90[10];
BOOL CGraphics::m_unk0x0081709c;
DDDeviceEnumBuffer CGraphics::m_unk0x0065fd08;
DDDeviceEnumBuffer CGraphics::m_displayDevicePool;
int CGraphics::m_lifetimeDisplayDeviceCount = 0;
int CGraphics::m_totalPixelsForScreen = 0;
Unk0x00660040 CGraphics::m_unk0x00660040[10];
int CGraphics::m_unk0x00663b18 = 0;
int CGraphics::m_unk0x00663b20 = 0;
int CGraphics::m_unk0x00663b24 = 0;
int CGraphics::m_selectedDisplayDeviceIx = 0;
DWORD CGraphics::m_displayCount = 0;
Entry CGraphics::m_unk0x006634d8[10];
DisplayMode CGraphics::m_displays[10];
int CGraphics::m_releaseSurfaceCallbackID;
char CGraphics::m_setWindowsDesktopTo16Bit[47] = "Set windows desktop to 16 bit for this 3D card";
char CGraphics::m_direct3DHAL[13] = "Direct3D HAL";
char CGraphics::m_direct3DTLHAL[18] = "Direct3D T&L HAL";
BOOL CGraphics::m_unk0x0072d56c = FALSE;
BOOL CGraphics::m_unk0x00660bfc = FALSE;
Unk0x006e0bb0 CGraphics::m_d3dDeviceDesc7;
TextureInfo CGraphics::m_textureInfo00660c08;
TextureInfo CGraphics::m_textureInfo00663450;
TextureInfo CGraphics::m_textureInfo0065fa58;
TextureInfo CGraphics::m_textureInfo0065fb70;
TextureInfo CGraphics::m_textureInfo0065fae0;
TextureInfo CGraphics::m_textureInfo0065fbf8;
TextureInfo CGraphics::m_textureInfo0065fc80;
TextureInfo CGraphics::m_textureInfo00660698;
TextureInfo CGraphics::m_textureInfo00660720;
TextureInfo CGraphics::m_textureInfo006607a8;
BOOL CGraphics::m_unk0x00663b34;
BOOL CGraphics::m_unk0x00663b38;
BOOL CGraphics::m_unk0x00663b3c;
BOOL CGraphics::m_unk0x00663b40;
BOOL CGraphics::m_unk0x00663b44;
BOOL CGraphics::m_unk0x00663b48;
BOOL CGraphics::m_unk0x00663b4c;
BOOL CGraphics::m_unk0x00663b50;
BOOL CGraphics::m_bSupports16BitColourDepth;
BOOL CGraphics::m_bSupports32BitColourDepth;

// FUNCTION: CMR2 0x00405830
bool CGraphics::InitializeDirectX(void) {
    LPDIRECTDRAW lpDD;
    LPDIRECTDRAW7 lpDD7;
    DDDEVICEIDENTIFIER2 lpDDIdenitifer;

    DirectDrawCreateEx(NULL, (LPVOID*)&lpDD, IID_IDirectDraw7, 0);
    lpDD->QueryInterface(IID_IDirectDraw7, (LPVOID*)&lpDD7);
    lpDD7->GetDeviceIdentifier(&lpDDIdenitifer, 0);

    if (strcmp(lpDDIdenitifer.szDescription, CGameInfo::m_gameInfo.graphicsCardName) == 0) {
        if (g_pGraphics->pDD7 != NULL) {
            if (g_pGraphics->pDD7->Release() == 0)
                g_pGraphics->pDD7 = NULL;
        }

        if (g_pGraphics->pDD != NULL) {
            if (g_pGraphics->pDD->Release() == 0)
                g_pGraphics->pDD = NULL;
        }

        return false;
    }

    wsprintfA(CGameInfo::m_gameInfo.graphicsCardName, CRegKey::m_regKeyPathFormatValue, lpDDIdenitifer.szDescription);

    if (g_pGraphics->pDD7 != NULL) {
        if (g_pGraphics->pDD7->Release() == 0)
            g_pGraphics->pDD7 = NULL;
    }

    if (g_pGraphics->pDD != NULL) {
        if (g_pGraphics->pDD->Release() == 0)
            g_pGraphics->pDD = NULL;
    }

    MessageBoxA(CMain::m_hWndList[CMain::m_hWndIx], m_strSettingConfigurationToDefault, CMain::m_logFileBlankLine, MB_TOPMOST | MB_TASKMODAL);

    return true;
}

// FUNCTION: CMR2 0x00405990
void CGraphics::SetDefaults(void) {
    CGameInfo::m_gameInfo.unknownGraphicsOptions |= 0x40000000;
    CGameInfo::m_gameInfo.screenWidth = 0x280;
    g_pGraphics->resX = 0x280;
    CGameInfo::m_gameInfo.screenHeight = 0x1e0;
    g_pGraphics->resY = 0x1e0;
    CGameInfo::m_gameInfo.screenColourDepth = 0x10;
    g_pGraphics->depth = 0x10;
    CGameInfo::m_gameInfo.unknownGraphicsOptions |= 1;
    g_pGraphics->isFullscreen = 1;
    CGameInfo::m_gameInfo.unknownGraphicsOptions &= 0xfffffff9;
    g_pGraphics->field913_0x3bc &= 0xfffffff7;
    g_pGraphics->field913_0x3bc &= 0xffffffef;
    g_pGraphics->field913_0x3bc &= 0xffffff7f;
    CGameInfo::m_gameInfo.unknownGraphicsOptions &= 0xfffffff7;
    g_pGraphics->field913_0x3bc &= 0xffffffdf;
    CGameInfo::m_gameInfo.unknownGraphicsOptions &= 0xffffffef;
    g_pGraphics->field913_0x3bc &= 0xffffffbf;
    CGameInfo::m_gameInfo.unknownGraphicsOptions &= 0xfff3e01f;
    g_pGraphics->field913_0x3bc &= 0xfffffffe;
    g_pGraphics->field913_0x3bc &= 0xfffffffd;

    unsigned int unknownGraphicsOptions = CGameInfo::m_gameInfo.unknownGraphicsOptions;
    CGameInfo::m_gameInfo.unknownGraphicsOptions = (unknownGraphicsOptions & 0xfe3fffff) | 0x200000;
    
    g_pGraphics->field917_0x3c0 = 1;
    
    CGameInfo::m_gameInfo.field_0x34 =  (CGameInfo::m_gameInfo.field_0x34 & 0xfffffffe) | 2;
    CGameInfo::m_gameInfo.unknownGraphicsOptions = (unknownGraphicsOptions & 0xcbffffff) | 0xa000000;
    
    g_pGraphics->field913_0x3bc &= 0xfffffffb;
}

// FUNCTION: CMR2 0x004a78a0
void CGraphics::FUN_004a78a0(unsigned int screenWidth, unsigned int screenHeight, unsigned int colourDepth, unsigned int param4, unsigned int param5) {
    if (m_unk0x00520b7c == 0) {
        CSound::FUN_004a2b50(TRUE);
        FUN_004a5be0(); // TODO: UNFINISHED
        ReleaseDirect3D();
        ReleaseSurfaces();
    }

    FUN_004a8bd0(param4);
    FUN_004a8d90(param5);

    BOOL b = FUN_004a7910(screenWidth, screenHeight, colourDepth);
    if (b != FALSE) {
        b = FUN_004a8450(screenWidth, screenHeight, colourDepth);
        if (b != 0) {

        }
    }
}

// FUNCTION: CMR2 0x004a5be0
BOOL CGraphics::FUN_004a5be0(void) {
    int index, textureID, iVar4, iVar7;

    m_pTextureManager->pDD->EvictManagedTextures();
    m_unk0x0065fa2c = NULL;

    index = 0;
    textureID = 0;
    do {
        Texture* pTexture = m_pTextureManager->textureBuffer[index];
        if (pTexture != NULL && pTexture->pSurface != NULL && textureID == pTexture->textureId) {
            
            if (pTexture->pSurface->Release() == 0) {
                pTexture->pSurface = NULL;
            }
        }
        
        index++;
        textureID++;
    } while (index < 2048);

    FUN_004a5ba0();
    index = 0;

    if (m_unk0x0065fa28 != 0) {
        do {
            iVar4 = 0x5f0;
            iVar7 = 0x734;

            do {
                Texture* pTexture = m_pTextureManager->textureBuffer2[index];
                if (pTexture != NULL) {
                    IDirectDrawSurface7* pOther = pTexture->pSurface;
                    if (pOther->Release() == 0) {
                        pTexture->pSurface = NULL;
                    }
                }
            } while (0x71f < iVar7);
            
            index++;
        } while (index < m_unk0x0065fa28);
    }

    return TRUE;
}

// FUNCTION: CMR2 0x004a8810
BOOL CGraphics::ReleaseDirect3D(void)
{
    ReleaseVertexBuffers();

    if (m_pTextureManager->pD3D != NULL && m_pTextureManager->pD3D->Release() == 0)
        m_pTextureManager->pD3D = NULL;
    
    m_pTextureManager->pD3D = NULL;
    
    if (m_pTextureManager->pDD != NULL && m_pTextureManager->pDD->Release() == 0)
        m_pTextureManager->pDD = NULL;
    
    m_pTextureManager->pDD = NULL;
    return TRUE;
}

// STUB: CMR2 0x004a5ba0
void CGraphics::FUN_004a5ba0(void) {

}

// FUNCTION: CMR2 0x004b1de0
void CGraphics::ReleaseVertexBuffers(void) {
    int index = 99;
    if (m_pTextureManager->pVertexBuffer3 != NULL && m_pTextureManager->pVertexBuffer3->Release() == 0)
        m_pTextureManager->pVertexBuffer3 = NULL;
    
    if (m_pTextureManager->pVertexBuffer2 != NULL && m_pTextureManager->pVertexBuffer2->Release() == 0)
        m_pTextureManager->pVertexBuffer2 = NULL;

    if (m_pTextureManager->pVertexBuffer1 != NULL && m_pTextureManager->pVertexBuffer1->Release() == 0)
        m_pTextureManager->pVertexBuffer1 = NULL;

    // not sure if this loop is fully correct or not
    do {
        if (m_pTextureManager->pVertexBuffers[index] != NULL && m_pTextureManager->pVertexBuffers[index]->Release() == 0)
            m_pTextureManager->pVertexBuffers[index] = NULL;

        index--;
    } while (index >= 0);

    m_unk0x006dd890 = 0;
}

// FUNCTION: CMR2 0x004a8040
void CGraphics::ReleaseSurfaces(void) {
    if (g_pGraphics->pSurface3 != NULL && g_pGraphics->pSurface3->Release() == 0)
        g_pGraphics->pSurface3 = NULL;

    g_pGraphics->pSurface3 = NULL;

    if (g_pGraphics->pBackBufferSurface != NULL && g_pGraphics->pBackBufferSurface->Release() == 0)
        g_pGraphics->pBackBufferSurface = NULL;

    g_pGraphics->pBackBufferSurface = NULL;

    if (g_pGraphics->pPrimarySurface != NULL && g_pGraphics->pPrimarySurface->Release() == 0)
        g_pGraphics->pPrimarySurface = NULL;

    g_pGraphics->pPrimarySurface = NULL;
    
    g_pGraphics->pDD7->SetCooperativeLevel(CMain::m_hWndList[CMain::m_hWndIx], DDSCL_NORMAL);
    if (g_pGraphics->isFullscreen != 0) {
        g_pGraphics->pDD7->RestoreDisplayMode();
    }

    if (g_pGraphics->pDD7 != NULL && g_pGraphics->pDD7->Release() == 0) {
        g_pGraphics->pDD7 = NULL;
    }
}

// FUNCTION: CMR2 0x004a8bd0
void CGraphics::FUN_004a8bd0(int param1) {
    m_unk0x00663b1c = param1;
}

// FUNCTION: CMR2 0x004a8d90
void CGraphics::FUN_004a8d90(int param1) {
    m_unk0x00663b24 = param1;
}

struct GraphicsStack
{
    LPDIRECTDRAWCLIPPER pDDClipper;
    DDSURFACEDESC2 ddsd;
    tagRECT lpWindowRect;
    tagRECT lpClientRect;
    DDSURFACEDESC2 ddsdDisplayMode;
};

// FUNCTION: CMR2 0x004a7910
BOOL CGraphics::FUN_004a7910(int screenWidth, int screenHeight, int colourDepth) {
    BOOL findMatchingDevice = FALSE;
    DWORD tier = 0;
    HDC hdc = 0;
    LPDIRECTDRAW7 pDD7;
    DWORD capFlag = 0x10004000;
    GraphicsStack s;

    int iHorzRes = 0, iVertRes = 0, iVar6 = 0, cx = 0;

    m_pTextureManager->textureInfo2 = NULL;
    m_pTextureManager->textureInfo5 = NULL;
    m_pTextureManager->textureInfo1 = NULL;

    FUN_004bdb60(&m_unk0x0065fd08,CMain::m_hWndList[CMain::m_hWndIx]);
    tier = FUN_004a96c0(m_unk0x00663b1c);
    while (tier == 0) {
        if (m_unk0x00663b1c + 1 > m_unk0x0065fd08.count - 1) {
            return FALSE;
        }

        FUN_004a8bd0(m_unk0x00663b1c + 1U);
        tier = FUN_004a96c0(m_unk0x00663b1c);
    }

    m_unk0x0065fd08.reserved = m_unk0x00663b1c;
    DirectDrawCreateEx(m_unk0x0065fd08.entries[m_unk0x00663b1c].device.pGUID, (LPVOID*)&g_pGraphics->pDD, IID_IDirectDraw7, NULL);

    g_pGraphics->pDD->QueryInterface(IID_IDirectDraw7, (LPVOID*)&g_pGraphics->pDD7);
    if (g_pGraphics->pDD != NULL && g_pGraphics->pDD->Release() == 0) {
        g_pGraphics->pDD = NULL;
    }

    g_pGraphics->resX = screenWidth;
    g_pGraphics->resY = screenHeight;
    g_pGraphics->depth = colourDepth;
    g_pGraphics->screenResX = GetDeviceCaps(GetDC(NULL), HORZRES);
    g_pGraphics->screenResY = GetDeviceCaps(GetDC(NULL), VERTRES);
    ReleaseDC(NULL, GetDC(NULL));

    tier = FUN_004a8bc0();
    tier = FUN_004a96e0(tier);
    if (tier == 0) {
        g_pGraphics->isFullscreen = 1;
        FUN_004a8d90(0);
        m_unk0x00660040[tier].surfaceCap = 1;
    }

    g_pGraphics->isFullscreen = 1;
    
    if (g_pGraphics->isFullscreen == 0) {
        g_pGraphics->pDD7->SetCooperativeLevel(CMain::m_hWndList[CMain::m_hWndIx], DDSCL_NORMAL);
        GetWindowRect(CMain::m_hWndList[CMain::m_hWndIx], &s.lpWindowRect);
        GetClientRect(CMain::m_hWndList[CMain::m_hWndIx], &s.lpClientRect);

        SetWindowPos(CMain::m_hWndList[CMain::m_hWndIx], NULL,
            GetSystemMetrics(SM_CXSCREEN) / 2 - 0x140,
            GetSystemMetrics(SM_CYSCREEN) / 2 - 0xf0,
            s.lpWindowRect.right + 0x280 - s.lpWindowRect.left + s.lpClientRect.left - s.lpClientRect.right,
            s.lpWindowRect.bottom + 0x1e0 - s.lpWindowRect.top + s.lpClientRect.top - s.lpClientRect.bottom,
            4);
        UpdateWindow(CMain::m_hWndList[CMain::m_hWndIx]);
        ShowWindow(CMain::m_hWndList[CMain::m_hWndIx], SW_SHOWNORMAL);
    } else {
        g_pGraphics->pDD7->SetCooperativeLevel(CMain::m_hWndList[CMain::m_hWndIx], 0x851);
    }

    g_pGraphics->pDD7->QueryInterface(IID_IDirect3D7, (LPVOID*)&m_pTextureManager);
    m_unk0x00663b18 = 0;
    m_unk0x00663b20 = 0;

    DirectDrawEnumerateExA(&FUN_004a8b30_DDEnumCallback, NULL, DDENUM_ATTACHEDSECONDARYDEVICES | DDENUM_DETACHEDSECONDARYDEVICES | DDENUM_NONDISPLAYDEVICES);

    m_pTextureManager->pDD->EnumDevices(FUN_004a8c30_DDEnumCallback, NULL);

    m_displayCount = 0;
    g_pGraphics->pDD7->EnumDisplayModes(0, NULL, NULL, FUN_004a8da0);

    findMatchingDevice = FUN_004a8f60(screenWidth, screenHeight, colourDepth);
    s.ddsdDisplayMode.dwSize = sizeof(DDSURFACEDESC2);
    if (findMatchingDevice != FALSE) {
        g_pGraphics->resX = screenWidth;
        g_pGraphics->resY = screenHeight;
        g_pGraphics->depth = colourDepth;
    } else {
        g_pGraphics->resX = 640;
        g_pGraphics->resY = 480;
        g_pGraphics->pDD7->GetDisplayMode(&s.ddsdDisplayMode);
        g_pGraphics->depth = s.ddsdDisplayMode.ddpfPixelFormat.dwRGBBitCount;
    }

    FUN_004a8ec0(g_pGraphics->resX, g_pGraphics->resY, g_pGraphics->depth);

    Unk0x0065ff90* deviceEntry = &m_unk0x0065ff90[m_unk0x00663b24];
    D3DTextureManager* textureManager = m_pTextureManager;

    textureManager->deviceGUID = deviceEntry->guid;

    if (g_pGraphics->isFullscreen != 0) {
        g_pGraphics->pDD7->SetDisplayMode(g_pGraphics->resX, g_pGraphics->resY, g_pGraphics->depth, 0, 0);
        DWORD isFullScreen = g_pGraphics->isFullscreen;
        if (isFullScreen == 0) {
            memset(&s.ddsd, 0, sizeof(DDSURFACEDESC2));
            s.ddsd.dwSize = sizeof(DDSURFACEDESC2);
            s.ddsd.dwFlags = DDSD_CAPS;
            s.ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
            
            if (FUN_004a8d60() != 1 && FUN_004a8d60() != 2) {
                s.ddsd.ddsCaps.dwCaps |= 0x800;
            } else {
                s.ddsd.ddsCaps.dwCaps |= capFlag;
            }

            if (g_pGraphics->pDD7->CreateSurface(&s.ddsd, &g_pGraphics->pPrimarySurface, 0) != 0)
                return FALSE;

            if (g_pGraphics->pDD7->CreateClipper(0, &s.pDDClipper, 0) != 0)
                return FALSE;

            s.pDDClipper->SetHWnd(0, CMain::m_hWndList[CMain::m_hWndIx]);
            g_pGraphics->pPrimarySurface->SetClipper(s.pDDClipper);
            if (s.pDDClipper != NULL) {
                if (s.pDDClipper->Release() == 0) {
                    s.pDDClipper = NULL;
                }
            }

            memset(&s.ddsd, 0, sizeof(DDSURFACEDESC2));
            s.ddsd.dwSize = sizeof(DDSURFACEDESC2);
            s.ddsd.dwHeight = g_pGraphics->resY;
            s.ddsd.dwWidth = g_pGraphics->resX;
            s.ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
            s.ddsd.ddsCaps.dwCaps = DDSCAPS_3DDEVICE | DDSCAPS_OFFSCREENPLAIN;

            if (FUN_004a8d60() != 1) {
                if (FUN_004a8d60() != 2) {
                    s.ddsd.ddsCaps.dwCaps |= 0x800;
                }
            }

            if (g_pGraphics->pDD7->CreateSurface(&s.ddsd, &g_pGraphics->pBackBufferSurface, 0) != 0)
                return FALSE;            
        } else {
            memset(&s.ddsd, 0, sizeof(DDSURFACEDESC2));
            s.ddsd.dwSize = sizeof(DDSURFACEDESC2);
            s.ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
            s.ddsd.dwBackBufferCount = 1;
            s.ddsd.ddsCaps.dwCaps = DDSCAPS_COMPLEX | DDSCAPS_FLIP | DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;

            if (FUN_004a8d60() == 1 || FUN_004a8d60() == 2) {
                s.ddsd.ddsCaps.dwCaps |= capFlag;
            } else {
                s.ddsd.ddsCaps.dwCaps |= 0x800;
            }

            if (g_pGraphics->pDD7->CreateSurface(&s.ddsd, &g_pGraphics->pPrimarySurface, 0) != 0)
                return FALSE;

            memset(&s.ddsd, 0, sizeof(DDSURFACEDESC2));
            s.ddsd.dwSize = sizeof(DDSURFACEDESC2);
            s.ddsd.dwFlags = DDSD_CAPS;
            s.ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER | DDSCAPS_COMPLEX | DDSCAPS_FLIP | DDSCAPS_3DDEVICE;

            if (FUN_004a8d60() == 1 || FUN_004a8d60() == 2) {
                s.ddsd.ddsCaps.dwCaps |= capFlag;
            } else {
                s.ddsd.ddsCaps.dwCaps |= 0x800;
            }

            if (g_pGraphics->pPrimarySurface->GetAttachedSurface(&s.ddsd.ddsCaps, &g_pGraphics->pBackBufferSurface) != 0)
                return FALSE;
        }
    }

    g_pGraphics->field590_0x26c = 0;
    g_pGraphics->field591_0x26e = 0;
    g_pGraphics->field592_0x270 = (WORD)g_pGraphics->resX;
    g_pGraphics->field593_0x272 = (WORD)g_pGraphics->resY;

    LPDWORD pField590AsDword = (LPDWORD)&g_pGraphics->field590_0x26c;
    g_pGraphics->field295_0x13c = pField590AsDword[0];
    g_pGraphics->field296_0x140 = pField590AsDword[1];
    
    if (m_unk0x00520b7c != 0) {
        m_releaseSurfaceCallbackID = CGame::RegisterCallback(ReleaseSurfaces,NULL);
    }    

    return TRUE;
}

// FUNCTION: CMR2 0x004bdb60
BOOL CGraphics::FUN_004bdb60(DDDeviceEnumBuffer* param1, HWND hWnd) {
    LPDIRECTDRAW7 pDirectDraw = NULL;
    LPDIRECTDRAW7 pDirectDrawConfirm = NULL;
    DDEnumDeviceBufferEntry* pEntry;
    int index = 0;

    if (m_unk0x0081709c == FALSE)  {
        m_displayDevicePool.count = 0;
        memset(param1, 0, 0x288);

        DirectDrawEnumerateExA(&FUN_004bdb60_DDEnumCallback, param1, DDENUM_ATTACHEDSECONDARYDEVICES | DDENUM_DETACHEDSECONDARYDEVICES | DDENUM_NONDISPLAYDEVICES);
        param1->count = m_displayDevicePool.count;

        if (m_displayDevicePool.count > 0) {
            pEntry = param1->entries;
            do {
                DirectDrawCreateEx(pEntry->device.pGUID, (LPVOID*)&pDirectDraw, IID_IDirectDraw7, NULL);
                pDirectDraw->QueryInterface(IID_IDirectDraw7, (LPVOID*)&pDirectDrawConfirm);

                pDirectDrawConfirm->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_ALLOWMODEX);
                FUN_004bdd30(pEntry, pDirectDrawConfirm);

                pDirectDrawConfirm->SetCooperativeLevel(hWnd, DDSCL_NORMAL);

                FUN_004bde20(pEntry, pDirectDrawConfirm);

                if (pDirectDrawConfirm != NULL && pDirectDrawConfirm->Release() == 0) {
                    pDirectDrawConfirm = NULL;
                }
                
                if (pDirectDraw != NULL && pDirectDraw->Release() == 0) {
                    pDirectDraw = NULL;
                }

                index++;
                pEntry++;
            } while (index < param1->count);
        }

        // this suggests that `m_displayDevicePool` isnt correct? or they're doing something gnarly
        memcpy((BYTE*)&m_displayDevicePool + 0x20, param1, sizeof(DDDeviceEnumBuffer));
        m_unk0x0081709c = TRUE;
    }
    
    return TRUE;
}

// FUNCTION: CMR2 0x004bdc80
BOOL CGraphics::FUN_004bdb60_DDEnumCallback(GUID* lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName,
                                             LPVOID lpContext, HMONITOR hMonitor)
{
    DDDeviceEnumBuffer* pBuffer = (DDDeviceEnumBuffer*)lpContext;

    if (m_displayDevicePool.count == 10)
        return FALSE;

    if (lpGUID == NULL) {
        pBuffer->entries[m_displayDevicePool.count].device.pGUID = NULL;
    } else {
        pBuffer->entries[m_displayDevicePool.count].device.guid = *lpGUID;
        pBuffer->entries[m_displayDevicePool.count].device.pGUID = &pBuffer->entries[m_displayDevicePool.count].device.guid;
    }

    m_lifetimeDisplayDeviceCount++;
    m_displayDevicePool.count++;

    return TRUE;
}

// FUNCTION: CMR2 0x004bdd30
BOOL CGraphics::FUN_004bdd30(DDEnumDeviceBufferEntry *pEnumDevice,IDirectDraw7 *pDevice) {
    HDC hdc;
    int hRes, vRes, bpp;
    LPDDCAPS pDriverCaps;
    DDCAPS driverCaps, helCaps;
    DWORD totalLocalVidMem;

    if (pEnumDevice->device.pGUID == NULL) {
        hdc = GetDC(NULL);
        hRes = GetDeviceCaps(hdc, HORZRES);
        vRes = GetDeviceCaps(hdc, VERTRES);
        bpp = GetDeviceCaps(hdc, BITSPIXEL);
        ReleaseDC(NULL, hdc);

        if (bpp == 8 || bpp != 0x10) {
            m_totalPixelsForScreen = vRes * hRes;
        } else {
            m_totalPixelsForScreen = vRes * hRes * 2;
        }
    }

    pDriverCaps = &driverCaps;

    driverCaps.dwSize = sizeof(DDCAPS);
    helCaps.dwSize = sizeof(DDCAPS);

    pDevice->GetCaps(pDriverCaps, &helCaps);
    pEnumDevice->capFlag1 = driverCaps.dwCaps & 1;
    pEnumDevice->capFlag200 = driverCaps.dwCaps & 0x200;
    pEnumDevice->capFlag80000 = driverCaps.dwCaps2 & 0x80000;

    m_displayDevicePool.entries[0].caps.caps.dwCaps = DDSCAPS_LOCALVIDMEM;
    pDevice->GetAvailableVidMem((LPDDSCAPS2)&m_displayDevicePool.entries[0].device.pGUID, &totalLocalVidMem, NULL);

    if (totalLocalVidMem < 0x1c2000)
        pEnumDevice->capFlag1 = 0;

    return TRUE;
}

// FUNCTION: CMR2 0x004bde20
void CGraphics::FUN_004bde20(DDEnumDeviceBufferEntry *pEnumDevice,IDirectDraw7 *pDevice) {
    pDevice->QueryInterface(IID_IDirect3D7, (LPVOID*)&pDevice);

    ((IDirect3D7*)pDevice)->EnumDevices(FUN_004bde60, pEnumDevice);

    if (pDevice != NULL)
        pDevice->Release();
}

// FUNCTION: CMR2 0x004bde60
HRESULT CGraphics::FUN_004bde60(LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC7 lpD3DDeviceDesc, LPVOID lpUserArg) {
    if ((lpD3DDeviceDesc->dpcTriCaps.dwTextureFilterCaps & 1) == 0)
        return 1;

    DDEnumDeviceBufferEntry* pEntry = (DDEnumDeviceBufferEntry*)lpUserArg;
    pEntry->capTextureFilter1 = 1;
    pEntry->capTextureFilter3 = 1;

    if ((lpD3DDeviceDesc->dpcTriCaps.dwTextureFilterCaps & 2) != 0)
        pEntry->capTextureFilter2 = 1;

    if ((lpD3DDeviceDesc->dwDevCaps & 0x100) != 0)
        pEntry->capHardwareRasterization = 1;

    DWORD deviceZBufferBitDepth = lpD3DDeviceDesc->dwDeviceZBufferBitDepth;
    if ((deviceZBufferBitDepth & 0x400) != 0) {
        pEntry->zBufferBitDepth = 0x10;
        pEntry->hasZBuffer = 1;
    } else if ((deviceZBufferBitDepth & 0x200) != 0) {
        pEntry->zBufferBitDepth = 0x18;
        pEntry->hasZBuffer = 1;
    } else if ((deviceZBufferBitDepth & 0x100) != 0) {
        pEntry->zBufferBitDepth = 0x20;
        pEntry->hasZBuffer = 1;
    }
    
    if ((lpD3DDeviceDesc->dwDeviceRenderBitDepth & 0x100) != 0) {
        pEntry->capRender16Bit = 1;
        return 1;
    }
    
    pEntry->capRender16Bit = 0;
    return 1;
}

// FUNCTION: CMR2 0x004a96c0
DWORD CGraphics::FUN_004a96c0(int param1) {
    return m_unk0x0065fd08.entries[param1].capFlag1;
}

// FUNCTION: CMR2 0x004a8bc0
INT32 CGraphics::FUN_004a8bc0(void) {
    return m_unk0x00663b1c;
}

// FUNCTION: CMR2 0x004a96e0
DWORD CGraphics::FUN_004a96e0(int param_1) {
    return m_unk0x0065fd08.entries[param_1].capFlag80000;
}

// FUNCTION: CMR2 0x004a8b30
BOOL CGraphics::FUN_004a8b30_DDEnumCallback(GUID* lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext, HMONITOR hMonitor) {
    LPDIRECTDRAW7 lplpDD;
    DDDEVICEIDENTIFIER2 ddDeviceIdent;
    DirectDrawCreateEx(lpGUID, (LPVOID*)&lplpDD, IID_IDirectDraw7, NULL);
    
    lplpDD->GetDeviceIdentifier(&ddDeviceIdent, 0);
    if (lplpDD != NULL) {
        if (lplpDD->Release() == 0)
            lplpDD = NULL;
    }

    wsprintfA(m_unk0x006634d8[m_unk0x00663b18].unk_0x00, CRegKey::m_regKeyPathFormatValue, ddDeviceIdent.szDescription);

    m_unk0x00663b18++;

    return TRUE;
}

// FUNCTION: CMR2 0x004a8da0
HRESULT CGraphics::FUN_004a8da0(DDSURFACEDESC2* lpDDSurfaceDesc2, void* lpContext) {
    int width  = lpDDSurfaceDesc2->dwWidth, height = lpDDSurfaceDesc2->dwHeight, bpp = lpDDSurfaceDesc2->ddpfPixelFormat.dwRGBBitCount;
    DWORD canRender16Bit = 0, dwTextureMem = 0, dwVidMem = 0;

    DDSURFACEDESC2 ddsd;
    ddsd.dwSize = sizeof(DDSURFACEDESC2);
    g_pGraphics->pDD7->GetDisplayMode(&ddsd);

    canRender16Bit = FUN_004a8bc0();
    canRender16Bit = DeviceCanRender16Bit(canRender16Bit);

    if (((canRender16Bit != 0 || bpp != 0x20) &&  (g_pGraphics->isFullscreen != 0 || ddsd.ddpfPixelFormat.dwFlags == bpp)) && (width >= 0x280 && height >= 0x1e0) && (bpp == 0x10 || bpp == 0x20)) {
        dwTextureMem = FUN_004bdd00(DDSCAPS_TEXTURE);
        dwVidMem = FUN_004bdd00(DDSCAPS_LOCALVIDMEM);
        if (dwTextureMem < dwVidMem) {
            dwTextureMem = FUN_004bdd00(DDSCAPS_LOCALVIDMEM);            
            dwVidMem = FUN_004bdd00(DDSCAPS_TEXTURE);
            dwTextureMem = dwTextureMem + -dwVidMem;
        } else {
            dwTextureMem = FUN_004bdd00(DDSCAPS_LOCALVIDMEM);
        }

        if ((bpp / 8) * height * width * 3 < dwTextureMem) {
            m_displays[m_displayCount].width = width;
            m_displays[m_displayCount].height = height;
            m_displays[m_displayCount].colourDepth = bpp;
            m_displayCount++;
        }
    }

    return DDENUMRET_OK;
}

// FUNCTION: CMR2 0x004a96f0
int CGraphics::DeviceCanRender16Bit(int param1) {
    return CGraphics::m_unk0x0065fd08.entries[param1].capRender16Bit;
}

// FUNCTION: CMR2 0x004bdd00
DWORD CGraphics::FUN_004bdd00(DWORD caps) {
  DDEnumDeviceBufferEntry* pDVar1 = &m_displayDevicePool.entries[0];
  
  pDVar1->caps.caps.dwCaps = caps;
  g_pGraphics->pDD7->GetAvailableVidMem(&pDVar1->caps.caps, &caps, NULL);

  return caps;
}

// FUNCTION: CMR2 0x004a8f60
BOOL CGraphics::FUN_004a8f60(int width, int height, int colourDepth)
{
    for (int i = 0; i < m_displayCount; i++) {
        if (m_displays[i].width == width && m_displays[i].height == height && m_displays[i].colourDepth == colourDepth)
            return TRUE;
    }

    return FALSE;
}

// FUNCTION: CMR2 0x004a8ec0
void CGraphics::FUN_004a8ec0(int width, int height, int colourDepth)
{
    for (int i = 0; i < m_displayCount; i++) {
        if (m_displays[i].width == width && m_displays[i].height == height && m_displays[i].colourDepth == colourDepth)
            m_selectedDisplayDeviceIx = i;
    }
}

// FUNCTION: CMR2 0x004a8d60
DWORD CGraphics::FUN_004a8d60(void) {
  return m_unk0x00660040[m_unk0x00663b24].surfaceCap;
}

// FUNCTION: CMR2 0x004a8c30
HRESULT CGraphics::FUN_004a8c30_DDEnumCallback(LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC7 lpD3DDeviceDesc, LPVOID lpUserArg) {
    if (strcmp(lpDeviceName, m_direct3DHAL) == 0 && m_unk0x00660040[0].surfaceCap != 2) {
        m_unk0x0065ff90[0].guid = lpD3DDeviceDesc->deviceGUID;
        m_unk0x00660040[0].surfaceCap = 1;
    } else if (strcmp(lpDeviceName, m_direct3DTLHAL) == 0) {
        m_unk0x0065ff90[0].guid = lpD3DDeviceDesc->deviceGUID;
        m_unk0x00660040[0].surfaceCap = 2;
    }

    wsprintfA(m_unk0x0065ff90[0].deviceDesc, CRegKey::m_regKeyPathFormatValue, lpDeviceDescription);
    wsprintfA(m_unk0x0065ff90[0].deviceName, CRegKey::m_regKeyPathFormatValue, lpDeviceName);

    m_unk0x00663b20 = 1;

    return TRUE;
}

// FUNCTION: CMR2 0x004a8450
BOOL CGraphics::FUN_004a8450(int screenWidth, int screenHeight, int colourDepth) {
    BOOL b;
    DDSURFACEDESC2 ddsd;

    if (m_unk0x00520b7c != FALSE) {
        m_unk0x0072d56c = 0;
        CGame::RegisterCallback(ReleaseDirect3D, NULL);
        CGame::RegisterCallback(ReleaseTextureBuffers, NULL);
        CGame::RegisterCallback(FUN_004a5be0, NULL);
    }

    m_unk0x00660bfc = 1;
    memset(&m_pTextureManager->ddpfZBuffer, 0, sizeof(DDPIXELFORMAT));

    if (g_pGraphics->depth == 0x20) {
        m_pTextureManager->ddpfZBuffer.dwRGBBitCount = 0x20;
        m_pTextureManager->pDD->EnumZBufferFormats(m_pTextureManager->deviceGUID, FUN_004a87c0, &m_pTextureManager->ddpfZBuffer);

        if (m_pTextureManager->ddpfZBuffer.dwRGBBitCount != 0x20) {
            m_pTextureManager->ddpfZBuffer.dwRGBBitCount = 0x18;
            m_pTextureManager->pDD->EnumZBufferFormats(m_pTextureManager->deviceGUID, FUN_004a87c0, &m_pTextureManager->ddpfZBuffer);
        }

        if (m_pTextureManager->ddpfZBuffer.dwRGBBitCount != 0x18) {
            m_pTextureManager->ddpfZBuffer.dwRGBBitCount = 0x10;
            m_pTextureManager->pDD->EnumZBufferFormats(m_pTextureManager->deviceGUID, FUN_004a87c0, &m_pTextureManager->ddpfZBuffer);
        }        
    }
    
    if (g_pGraphics->depth == 0x10) {
        m_pTextureManager->ddpfZBuffer.dwRGBBitCount = 0x10;
        m_pTextureManager->pDD->EnumZBufferFormats(m_pTextureManager->deviceGUID, FUN_004a87c0, &m_pTextureManager->ddpfZBuffer);
    }

    b = FUN_004b74b0();
    if (b == FALSE) {
        memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
        ddsd.dwSize = sizeof(DDSURFACEDESC2);
        ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
        ddsd.ddsCaps.dwCaps = 0x20000;

        if ((g_pGraphics->field913_0x3bc & 0x20) != 0) {
            ddsd.ddsCaps.dwCaps = 0x24000;
        }

        ddsd.dwHeight = g_pGraphics->resY;
        ddsd.dwWidth = g_pGraphics->resX;
        ddsd.ddpfPixelFormat = m_pTextureManager->ddpfZBuffer;
        
        if (FUN_004a8d60() == 1 || FUN_004a8d60() == 2) {
            ddsd.ddsCaps.dwCaps |= 0x10004000;
        } else {
            ddsd.ddsCaps.dwCaps |= 0x800;
        }

        g_pGraphics->pDD7->CreateSurface(&ddsd, &g_pGraphics->pSurface3, NULL);
        if (g_pGraphics->pBackBufferSurface->AddAttachedSurface(g_pGraphics->pSurface3) != 0)
            return FALSE;
    }

    ddsd.dwSize = sizeof(DDSURFACEDESC2);
    g_pGraphics->pDD7->GetDisplayMode(&ddsd);
    if (g_pGraphics->isFullscreen == 0 && ddsd.dwAlphaBitDepth == 0x20) {
        if (DeviceCanRender16Bit(FUN_004a8bc0()) == 0) {
            MessageBoxA(CMain::m_hWndList[CMain::m_hWndIx], m_setWindowsDesktopTo16Bit, CMain::m_logFileBlankLine, MB_TASKMODAL | MB_TOPMOST);
        }
    }

    if (FUN_004a8d60() == 0) {
        m_pTextureManager->pDD->CreateDevice(IID_IDirect3DRGBDevice, g_pGraphics->pBackBufferSurface, &m_pTextureManager->pD3D);
    }

    if (FUN_004a8d60() == 1) {
        m_pTextureManager->pDD->CreateDevice(IID_IDirect3DHALDevice, g_pGraphics->pBackBufferSurface, &m_pTextureManager->pD3D);
    }

    if (FUN_004a8d60() == 2) {
        m_pTextureManager->pDD->CreateDevice(IID_IDirect3DTnLHalDevice, g_pGraphics->pBackBufferSurface, &m_pTextureManager->pD3D);
    }

    if (FUN_004a8d60() == 3) {
        m_pTextureManager->pDD->CreateDevice(IID_IDirect3DRefDevice, g_pGraphics->pBackBufferSurface, &m_pTextureManager->pD3D);
    }

    FUN_004b7210();
    FUN_004a8fb0();
    FUN_0049df90(m_unk0x00520b7c, 1);
    FUN_004b1980();
    
    m_unk0x00520b7c = 0;

    return TRUE;
}

// FUNCTION: CMR2 0x004a5d10
BOOL CGraphics::ReleaseTextureBuffers(void) {
    void* buffer = NULL;
    int i = 0;
    for (i = 0; i < 2048; i++) {
        buffer = m_pTextureManager->textureBuffer[i];
        if (buffer != NULL) {
            CFileBuffer::FreeGenericFileBuffer(buffer);
            m_pTextureManager->textureBuffer[i] = NULL;
            if (m_unk0x0065fa20 > 0)
                m_unk0x0065fa20--;
        }
    }

    for (i = 0; i < 20; i++) {
        buffer = m_pTextureManager->textureBuffer2[i];
        if (buffer != NULL) {
            CFileBuffer::FreeGenericFileBuffer(buffer);
            m_pTextureManager->textureBuffer2[i] = NULL;
            if (m_unk0x0065fa28 > 0)
                m_unk0x0065fa28--;
        }
    }

    return TRUE;
}

// FUNCTION: CMR2 0x004a87c0
HRESULT CGraphics::FUN_004a87c0(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext) {
    LPDDPIXELFORMAT ddpf = (LPDDPIXELFORMAT)lpContext;
    if (lpDDPixFmt != NULL && ddpf != NULL) {
        if ((ddpf->dwRGBBitCount != lpDDPixFmt->dwRGBBitCount) || (lpDDPixFmt->dwFlags & 0x400) == 0) {
            ddpf->dwRGBBitCount = 0;
            return DDENUMRET_OK;
        }
        
        memcpy(ddpf, lpDDPixFmt, sizeof(DDPIXELFORMAT));
    }


    return DDENUMRET_CANCEL;
}

// FUNCTION: CMR2 0x004b74b0
BOOL CGraphics::FUN_004b74b0(void) {
  return m_d3dDeviceDesc7.field0x80;
}

// FUNCTION: CMR2 0x004b7210
void CGraphics::FUN_004b7210(void) {
    D3DDEVICEDESC7 d3ddesc;
    
    memset(&m_d3dDeviceDesc7, 0, sizeof(Unk0x006e0bb0));
    m_pTextureManager->pD3D->GetCaps(&d3ddesc);

    if ((d3ddesc.dwDevCaps & 0x100) != 0) {
        m_d3dDeviceDesc7.flag100 = 1;
    }

    if ((d3ddesc.dwDevCaps & 0x200) != 0) {
        m_d3dDeviceDesc7.flag200 = 1;
    }

    if ((d3ddesc.dwDevCaps & 0x1000) != 0) {
        m_d3dDeviceDesc7.flag1000 = 1;
    }

    m_d3dDeviceDesc7.field0x7c = d3ddesc.dpcTriCaps.dwStippleHeight;
    if ((d3ddesc.dpcTriCaps.dwSize & 0x8000) != 0) {
        m_d3dDeviceDesc7.field0x80 = 1;
    }

    if (((BYTE)d3ddesc.dpcTriCaps.dwMiscCaps & 0x80) != 0) {
        m_d3dDeviceDesc7.field0x84 = 1;
    }

    if (((WORD)d3ddesc.dwFVFCaps > 1) && (d3ddesc.dwStencilCaps & 8) != 0) {
        m_d3dDeviceDesc7.field0x88 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwTextureFilterCaps & 4) != 0) {
        m_d3dDeviceDesc7.field0x18 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwShadeCaps & 1) != 0) {
        m_d3dDeviceDesc7.field0x1c = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwShadeCaps & 2) != 0) {
        m_d3dDeviceDesc7.field0x28 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwShadeCaps & 0x20) != 0) {
        m_d3dDeviceDesc7.field0x2c = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwAlphaCmpCaps & 1) != 0) {
        m_d3dDeviceDesc7.field0x20 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwAlphaCmpCaps & 0x20) != 0) {
        m_d3dDeviceDesc7.field0x24 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwAlphaCmpCaps & 8) != 0) {
        m_d3dDeviceDesc7.field0x30 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwTextureCaps & 0x80) != 0) {
        m_d3dDeviceDesc7.field0x44 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwTextureCaps & 0x40) != 0) {
        m_d3dDeviceDesc7.field0x48 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwTextureCaps & 1) != 0) {
        m_d3dDeviceDesc7.field0x4c = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwTextureCaps & 4) != 0) {
        m_d3dDeviceDesc7.field0x50 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwTextureCaps & 2) != 0) {
        m_d3dDeviceDesc7.field0x54 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwTextureCaps & 8) != 0) {
        m_d3dDeviceDesc7.field0x58 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwTextureCaps & 0x20) != 0) {
        m_d3dDeviceDesc7.field0x5c = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwSrcBlendCaps & 0x40) != 0) {
        m_d3dDeviceDesc7.field0x60 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwAlphaCmpCaps & 4) != 0) {
        m_d3dDeviceDesc7.field0x64 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwSize & 0x200) != 0) {
        m_d3dDeviceDesc7.field0x68 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwDestBlendCaps & 0x1000) != 0) {
        m_d3dDeviceDesc7.field0x6c = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwDestBlendCaps & 0x2000) != 0) {
        m_d3dDeviceDesc7.field0x70 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwDestBlendCaps & 0x4000) != 0) {
        m_d3dDeviceDesc7.field0x74 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwDestBlendCaps & 0x8000) != 0) {
        m_d3dDeviceDesc7.field0x78 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwRasterCaps & 0x10) != 0 &&
        (d3ddesc.dpcTriCaps.dwZCmpCaps & 0x20) != 0) {
        m_d3dDeviceDesc7.field0x34 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwRasterCaps & 2) != 0 &&
        (d3ddesc.dpcTriCaps.dwZCmpCaps & 2) != 0) {
        m_d3dDeviceDesc7.field0x38 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwRasterCaps & 4) != 0 &&
        (d3ddesc.dpcTriCaps.dwZCmpCaps & 2) != 0) {
        m_d3dDeviceDesc7.field0x3c = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwRasterCaps & 2) != 0 &&
        (d3ddesc.dpcTriCaps.dwZCmpCaps & 8) != 0) {
        m_d3dDeviceDesc7.field0x40 = 1;
    }

    if ((d3ddesc.dpcLineCaps.dwStippleHeight & 0x40) != 0) {
        m_d3dDeviceDesc7.field0xc = 1;
    }

    if ((d3ddesc.dpcLineCaps.dwStippleHeight & 0x20) != 0) {
        m_d3dDeviceDesc7.field0x8 = 1;
    }

    if ((d3ddesc.dpcLineCaps.dwStippleHeight & 0x10) != 0) {
        m_d3dDeviceDesc7.field0x4 = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwMiscCaps & 0x80) != 0) {
        m_d3dDeviceDesc7.field0x8c = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwMiscCaps & 0x100) != 0) {
        m_d3dDeviceDesc7.field0x90 = 1;
    }

    if ((WORD)d3ddesc.dwFVFCaps < 2) {
        m_d3dDeviceDesc7.field0x94 = 1;
    }

    m_d3dDeviceDesc7.field0xa4 = 1;

    if ((d3ddesc.dwStencilCaps & 0x400000) != 0) {
        m_d3dDeviceDesc7.field0x98 = 1;
    }

    if (((*(DWORD*)&d3ddesc.dvGuardBandBottom & 0x40) != 0) &&
        ((*(DWORD*)&d3ddesc.dvGuardBandBottom & 0x80) != 0) &&
        ((*(DWORD*)&d3ddesc.dvGuardBandBottom & 1) != 0) &&
        ((*(DWORD*)&d3ddesc.dvGuardBandBottom & 4) != 0)) {
        m_d3dDeviceDesc7.field0x9c = 1;
    }

    if ((d3ddesc.dpcTriCaps.dwAlphaCmpCaps & 0x800) != 0) {
        m_d3dDeviceDesc7.field0xa0 = 1;
    }

    m_d3dDeviceDesc7.field0xa8 = d3ddesc.dwDeviceRenderBitDepth;
    m_d3dDeviceDesc7.field0xac = d3ddesc.dwDeviceZBufferBitDepth;
    m_d3dDeviceDesc7.field0xb0 = d3ddesc.dwMinTextureWidth;
    m_d3dDeviceDesc7.field0xb4 = d3ddesc.dwMinTextureHeight;
}

// FUNCTION: CMR2 0x004a8fb0
void CGraphics::FUN_004a8fb0(void) {
    memset(&m_textureInfo00660698, 0, sizeof(TextureInfo));
    memset(&m_textureInfo0065fc80, 0, sizeof(TextureInfo));
    memset(&m_textureInfo0065fae0, 0, sizeof(TextureInfo));
    memset(&m_textureInfo0065fbf8, 0, sizeof(TextureInfo));
    memset(&m_textureInfo00660720, 0, sizeof(TextureInfo));
    memset(&m_textureInfo006607a8, 0, sizeof(TextureInfo));
    memset(&m_textureInfo0065fa58, 0, sizeof(TextureInfo));
    memset(&m_textureInfo00663450, 0, sizeof(TextureInfo));
    memset(&m_textureInfo0065fb70, 0, sizeof(TextureInfo));
    memset(&m_textureInfo00660c08, 0, sizeof(TextureInfo));

    m_unk0x00663b34 = FALSE;
    m_unk0x00663b38 = FALSE;
    m_unk0x00663b3c = FALSE;
    m_unk0x00663b40 = FALSE;
    m_unk0x00663b44 = FALSE;
    m_unk0x00663b48 = FALSE;
    m_unk0x00663b4c = FALSE;
    m_unk0x00663b50 = FALSE;
    m_bSupports16BitColourDepth = FALSE;
    m_bSupports32BitColourDepth = FALSE;

    m_pTextureManager->pD3D->EnumTextureFormats(FUN_004a91b0, NULL);
    if (m_textureInfo00660720.field_0x7c != 0x8) {
        m_unk0x00663b44 = TRUE;
        memcpy(&m_textureInfo00660720, &m_textureInfo0065fa58, sizeof(TextureInfo));
    }

    if (m_bSupports16BitColourDepth != FALSE && m_bSupports32BitColourDepth == FALSE) {
        m_bSupports32BitColourDepth = TRUE;
        memcpy(&m_textureInfo00660c08, &m_textureInfo0065fb70, sizeof(TextureInfo));
        m_textureInfo00660c08.ddsd.ddpfPixelFormat = m_textureInfo0065fb70.ddsd.ddpfPixelFormat;
    }

    if (g_pGraphics->depth != 0x10) {
        if (g_pGraphics->depth == 0x20) {
            m_pTextureManager->textureInfo1 = &m_textureInfo00660720;
            m_pTextureManager->textureInfo2 = &m_textureInfo0065fa58;
            m_pTextureManager->textureInfo3 = &m_textureInfo006607a8;
            m_pTextureManager->textureInfo4 = &m_textureInfo00663450;

            if (m_bSupports32BitColourDepth != FALSE) {
                m_pTextureManager->textureInfo5 = &m_textureInfo00660c08;
            }
        } 
    } else {
        m_pTextureManager->textureInfo1 = &m_textureInfo00660698;
        m_pTextureManager->textureInfo2 = &m_textureInfo0065fae0;
        m_pTextureManager->textureInfo3 = &m_textureInfo0065fc80;
        m_pTextureManager->textureInfo4 = &m_textureInfo0065fbf8;

        if (m_bSupports16BitColourDepth != FALSE) {
            m_pTextureManager->textureInfo5 = &m_textureInfo0065fb70;
        }
    }
}

void CGraphics::FUN_0049df90(BOOL param1, BOOL param2) {

}

void CGraphics::FUN_004b1980(void) {

}

// FUNCTION: CMR2 0x004b7560
BOOL CGraphics::FUN_004b7560(unsigned int param_1)
{
    if (m_d3dDeviceDesc7.field0xa8 <= param_1 && param_1 <= m_d3dDeviceDesc7.field0xb0)
        return TRUE;

    return FALSE;
}

// FUNCTION: CMR2 0x004b7590
BOOL CGraphics::FUN_004b7590(unsigned int param_1)
{
    if (m_d3dDeviceDesc7.field0xac <= param_1 && param_1 <= m_d3dDeviceDesc7.field0xb4)
        return TRUE;

    return FALSE;
}

// FUNCTION: CMR2 0x004a9700
BOOL CGraphics::FUN_004a9700(void)
{
    if (!m_unk0x00663b38 && !m_unk0x00663b48)
        return FALSE;

    return TRUE;
}

// STUB: CMR2 0x004a91b0
HRESULT CGraphics::FUN_004a91b0(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext) {
    return 0;
}
