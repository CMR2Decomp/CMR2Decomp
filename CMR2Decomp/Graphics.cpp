#include "Graphics.h"
#include "GameInfo.h"
#include "RegKey.h"
#include "main.h"
#include "Sound.h"
#include "Game.h"
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
void* CGraphics::m_unk0x0065fa2c;
int CGraphics::m_unk0x0065fa28;
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
    DWORD tier = 0;
    HDC hdc = 0;
    UINT uFlags;
    BOOL findMatchingDevice = FALSE;
    LPDIRECTDRAW7 pDD7;
    GraphicsStack s;

    int iHorzRes = 0, iVertRes = 0, iVar6 = 0, cx = 0;
    int iSystemMetricsScreenY = 0, iSystemMetricsScreenX = 0;

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
    hdc = GetDC(NULL);
    iHorzRes = GetDeviceCaps(hdc, HORZRES);
    g_pGraphics->screenResX = iHorzRes;
    iVertRes = GetDeviceCaps(hdc, VERTRES);
    g_pGraphics->screenResY = iVertRes;
    ReleaseDC(NULL, hdc);

    tier = FUN_004a8bc0();
    tier = FUN_004a96e0(tier);
    if (tier == 0) {
        g_pGraphics->isFullscreen = 1;
        FUN_004a8d90(0);
        m_unk0x00660040[tier].surfaceCap = 1;
    }

    g_pGraphics->isFullscreen = 1;
    
    pDD7 = g_pGraphics->pDD7;
    if (g_pGraphics->isFullscreen == 0) {
        pDD7->SetCooperativeLevel(CMain::m_hWndList[CMain::m_hWndIx], DDSCL_NORMAL);
        GetWindowRect(CMain::m_hWndList[CMain::m_hWndIx], &s.lpWindowRect);
        GetClientRect(CMain::m_hWndList[CMain::m_hWndIx], &s.lpClientRect);
        uFlags = SWP_NOZORDER;

        iVar6 = ((s.lpClientRect.top - s.lpClientRect.bottom) - s.lpWindowRect.top) + 0x1e0 + s.lpWindowRect.bottom;
        cx = ((s.lpClientRect.left - s.lpClientRect.right) - s.lpWindowRect.left) + 0x280 + s.lpWindowRect.right;

        iSystemMetricsScreenY = GetSystemMetrics(SM_CYSCREEN);
        iSystemMetricsScreenY = iSystemMetricsScreenY / 2 + -0xf0;

        iSystemMetricsScreenX = GetSystemMetrics(SM_CXSCREEN);

        SetWindowPos(CMain::m_hWndList[CMain::m_hWndIx], NULL, iSystemMetricsScreenX / 2 + -0x140, iSystemMetricsScreenY, cx, iVar6, uFlags);
        UpdateWindow(CMain::m_hWndList[CMain::m_hWndIx]);
        ShowWindow(CMain::m_hWndList[CMain::m_hWndIx], SW_SHOWNORMAL);
    } else {
        pDD7->SetCooperativeLevel(CMain::m_hWndList[CMain::m_hWndIx], 0x851);
    }

    g_pGraphics->pDD7->QueryInterface(IID_IDirect3D7, (LPVOID*)&m_pTextureManager);
    m_unk0x00663b18 = 0;
    m_unk0x00663b20 = 0;

    DirectDrawEnumerateExA(&FUN_004a8b30_DDEnumCallback, NULL, DDENUM_ATTACHEDSECONDARYDEVICES | DDENUM_DETACHEDSECONDARYDEVICES | DDENUM_NONDISPLAYDEVICES);

    m_pTextureManager->pDD->EnumDevices(FUN_004a8c30_DDEnumCallback, NULL);

    m_displayCount = 0;
    g_pGraphics->pDD7->EnumDisplayModes(0, NULL, NULL, FUN_004a8da0);

    findMatchingDevice = FUN_004a8f60(screenWidth, screenHeight, colourDepth);
    if (findMatchingDevice != FALSE) {
        g_pGraphics->resX = screenWidth;
        g_pGraphics->resY = screenHeight;
        g_pGraphics->depth = colourDepth;
    } else {
        g_pGraphics->resX = 640;
        g_pGraphics->resY = 480;
        s.ddsdDisplayMode.dwSize = sizeof(DDSURFACEDESC2);
        g_pGraphics->pDD7->GetDisplayMode(&s.ddsdDisplayMode);
        g_pGraphics->depth = s.ddsdDisplayMode.ddpfPixelFormat.dwRGBBitCount;
    }

    FUN_004a8ec0(g_pGraphics->resX, g_pGraphics->resY, g_pGraphics->depth);

    Unk0x0065ff90* deviceEntry = &m_unk0x0065ff90[m_unk0x00663b24];
    m_pTextureManager->pDeviceGUID = deviceEntry->pGUID;
    m_pTextureManager->field_0xc = deviceEntry->field_0x4;
    m_pTextureManager->field_0x10 = deviceEntry->field_0x8;
    m_pTextureManager->field_0x14 = deviceEntry->field_0xc;

    if (g_pGraphics->isFullscreen != 0) {
        g_pGraphics->pDD7->SetDisplayMode(g_pGraphics->resX, g_pGraphics->resY, g_pGraphics->depth, 0, 0);
        DWORD isFullScreen = g_pGraphics->isFullscreen;
        if (isFullScreen == 0) {
            memset(&s.ddsd, 0, sizeof(DDSURFACEDESC2));
            s.ddsd.dwSize = sizeof(DDSURFACEDESC2);
            s.ddsd.dwFlags = DDSD_CAPS;
            s.ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
            
            if (FUN_004a8d60() == 1 || FUN_004a8d60() == 2) {
                s.ddsd.ddsCaps.dwCaps |= 0x10004000;
            } else {
                s.ddsd.ddsCaps.dwCaps |= 0x800;
            }

            if (g_pGraphics->pDD7->CreateSurface(&s.ddsd, &g_pGraphics->pPrimarySurface, 0) != 0)
                return FALSE;

            s.pDDClipper = NULL;
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

            if (FUN_004a8d60() != 2) {
                s.ddsd.ddsCaps.dwCaps |= 0x10004000;
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
                s.ddsd.ddsCaps.dwCaps |= 0x10004000;
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

// STUB: CMR2 0x004a8c30
HRESULT CGraphics::FUN_004a8c30_DDEnumCallback(LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC7 lpD3DDeviceDesc, LPVOID lpUserArg) {
    return TRUE;
}
