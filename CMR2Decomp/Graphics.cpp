#include "Graphics.h"
#include "GameInfo.h"
#include "RegKey.h"
#include "main.h"
#include "Sound.h"
#include <basetsd.h>
#include <cstring>
#include <wingdi.h>
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
int CGraphics::m_unk0x00663b24;
BOOL CGraphics::m_unk0x0081709c;
DDDeviceEnumBuffer CGraphics::m_unk0x0065fd08;
DDDeviceEnumBuffer CGraphics::m_displayDevicePool;
int CGraphics::m_lifetimeDisplayDeviceCount = 0;
int CGraphics::m_totalPixelsForScreen = 0;

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

    BOOL b = FUN_004a7910();
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

    if (g_pGraphics->pSurface2 != NULL && g_pGraphics->pSurface2->Release() == 0)
        g_pGraphics->pSurface2 = NULL;

    g_pGraphics->pSurface2 = NULL;

    if (g_pGraphics->pSurface != NULL && g_pGraphics->pSurface->Release() == 0)
        g_pGraphics->pSurface = NULL;

    g_pGraphics->pSurface = NULL;
    
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

// FUNCTION: CMR2 0x004a7910
BOOL CGraphics::FUN_004a7910(void) {
    m_pTextureManager->textureInfo2 = NULL;
    m_pTextureManager->textureInfo5 = NULL;
    m_pTextureManager->textureInfo1 = NULL;

    FUN_004bdb60(&m_unk0x0065fd08,CMain::m_hWndList[CMain::m_hWndIx]);

    return TRUE;
}

// FUNCTION: CMR2 0x004bdb60
BOOL CGraphics::FUN_004bdb60(DDDeviceEnumBuffer* param1, HWND hWnd) {
    int index = 0;
    LPDIRECTDRAW7 pDirectDraw = NULL;
    LPDIRECTDRAW7 pDirectDrawConfirm = NULL;
    DDEnumDeviceBufferEntry* pEntry;

    if (m_unk0x0081709c != TRUE)  {
        m_displayDevicePool.count = 0;
        memset(param1, 0, 0xa2);

        DirectDrawEnumerateExA(&FUN_004bdb60_DDEnumCallback, param1, DDENUM_ATTACHEDSECONDARYDEVICES | DDENUM_DETACHEDSECONDARYDEVICES | DDENUM_NONDISPLAYDEVICES);
        param1->count = m_displayDevicePool.count;

        if (m_displayDevicePool.count > 0) {
            pEntry = &param1->entries[0];
            do {
                DirectDrawCreateEx(pEntry->pGUID, (LPVOID*)&pDirectDraw, IID_IDirectDraw7, NULL);
                pDirectDraw->QueryInterface(IID_IDirectDraw7, (LPVOID*)&pDirectDrawConfirm);

                // TODO: this should be something else?
                pDirectDraw->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_ALLOWMODEX);
                FUN_004bdd30(pEntry, pDirectDrawConfirm);

                pDirectDrawConfirm->SetCooperativeLevel(hWnd, DDSCL_NORMAL);

                FUN_004bde20(pEntry, pDirectDrawConfirm);

                index++;
            } while (index < param1->count);
        }
    }
    
    m_unk0x0081709c = TRUE;
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
        pBuffer->entries[m_displayDevicePool.count].pGUID = NULL;
    } else {
        pBuffer->entries[m_displayDevicePool.count].guid = *lpGUID;
        pBuffer->entries[m_displayDevicePool.count].pGUID = &pBuffer->entries[m_displayDevicePool.count].guid;
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

    if (pEnumDevice->pGUID == NULL) {
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

    ((DDSCAPS2*)&m_displayDevicePool.entries[0])->dwCaps = DDSCAPS_LOCALVIDMEM;
    pDevice->GetAvailableVidMem((LPDDSCAPS2)&m_displayDevicePool.entries[0].pGUID, &totalLocalVidMem, NULL);

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

// STUB: CMR2 0x004bde60
HRESULT CGraphics::FUN_004bde60(LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC7 lpD3DDeviceDesc, LPVOID lpUserArg) {
    return 0;
}
