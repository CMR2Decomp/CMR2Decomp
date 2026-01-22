#include "Game.h"
#include "main.h"
#include "RegKey.h"
#include "GameInfo.h"
#include "InstallInfo.h"
#include "NetworkLeaderboards.h"
#include "Graphics.h"
#include "Input.h"
#include "FileBuffer.h"
#include "Frontend.h"
#include "Texture.h"

#include <stdio.h>
#include <time.h>

BOOL CGame::m_shouldExit = FALSE;
BOOL CGame::m_isActive = FALSE;
int CGame::m_unk0x00523c58 = -1;
int CGame::m_unk0x00523c5c = -1;
Unk0049c2c0 CGame::m_unk0x00817da0;
int CGame::m_unk0x0052ea4c;
bool CGame::m_unk0x00817eb0 = false;
Unk00817d98 CGame::m_unk0x00817d98;
BYTE CGame::m_unk0x00523c18;
BYTE CGame::m_unk0x00593cac;
BYTE CGame::m_unk0x00593ba8;
Unk00817d98 *CGame::m_unk0x00593ba4;

BYTE CGame::m_unk0x00523d68 = 1;
BYTE CGame::m_unk0x008180f9;
BYTE CGame::m_unk0x008180fc;
BYTE CGame::m_unk0x00516120 = 1;
BYTE CGame::m_unk0x00531768;
BYTE CGame::m_unk0x0052ea58;
BYTE CGame::m_unk0x0052ea59;

// GLOBAL: CMR2 0x00593ba0;
int CGame::m_unk0x00593ba0;

// GLOBAL: CMR2 0x005939a0
void* CGame::m_unk0x005939a0;

BYTE CGame::m_unk0x005a1818;
BYTE CGame::m_unk0x005a1819;
Unk0x005a1820 CGame::m_unk0x005a1820[7];
int CGame::m_unk0x005a1e34;
bool CGame::m_unk0x005a1fc0;
IDirectPlay4A *CGame::m_pDirectPlay4A = NULL;
DPID CGame::m_unk0x005a1ea0 = NULL;

IDirectPlayLobby3A *CGame::m_pDirectPlayLobby3A;

BOOL CGame::m_unk0x005a1fbc;
void *CGame::m_unk0x005a1fb8;

Unk0x00664750 CGame::m_unk0x00664750[10];
int CGame::m_unk0x00665218;
BOOL CGame::m_unk0x00532138 = FALSE;

char CGame::m_strUK[3] = "UK";
char CGame::m_strIta[4] = "Ita";
char CGame::m_strKen[4] = "Ken";
char CGame::m_strItaly[8] = "Italy";
char CGame::m_strAus[4] = "Aus";
char CGame::m_strSwe[4] = "Swe";
char CGame::m_strKenya[8] = "Kenya";
char CGame::m_strFra[4] = "Fra";
char CGame::m_strSweden[8] = "Sweden";
char CGame::m_strFrance[8] = "France";
char CGame::m_strGre[4] = "Gre";
char CGame::m_strFin[4] = "Fin";
char CGame::m_strFinland[8] = "Finland";
char CGame::m_strGreece[8] = "Greece";

FuncTableGroup CGame::m_initializeGameGroupedFuncTable[10] = {
    {InitializeGame,
     FUN_00501680},
};

// FUNCTION: CMR2 0x004a9a40
void CGame::SetShouldExit(void)
{
    // m_shouldExit = TRUE;
}

// STUB: CMR2 0x004b7a40
void CGame::FUN_004b7a40(void) {

}

// FUNCTION: CMR2 0x004d0780
BOOL CGame::FUN_004d0780(void)
{
    m_unk0x00523c5c = FUN_004057d0();
    if (m_unk0x00523c58 != m_unk0x00523c5c)
        m_unk0x00523c58 = m_unk0x00523c5c;

    switch (m_unk0x00523c5c)
    {
    case 3:
        return FUN_0041b060();

    case 2:
        return FUN_004ff450();

    case 0:
        if (m_unk0x00817eb0)
        {
            FUN_0049c2c0(&m_unk0x00817da0);
            FUN_0049c310(&m_unk0x00817da0);
            FUN_0049c370(&m_unk0x00817da0);
            return FALSE;
        }

        FUN_0049c150(&m_unk0x00817d98, 0, 0xFF);
        FUN_0049c190(&m_unk0x00817da0, 1, &m_unk0x00817d98, m_initializeGameGroupedFuncTable, &m_unk0x00523c18);
        m_unk0x00817eb0 = true;
        return FALSE;

    default:
        return FALSE;
    }
}

// FUNCTION: CMR2 0x004057d0
int CGame::FUN_004057d0(void)
{
    return m_unk0x0052ea4c;
}

// FUNCTION: CMR2 0x004d15e0
void CGame::InitializeGame(Unk0049c2c0 *p1, BYTE p2)
{
    time_t srandSeed;
    char *skuValue, *skuRegion;
    bool didLoadGameInfo = false;

    srandSeed = time(NULL);
    srand(srandSeed);

    // europe sku check
    skuValue = CRegKey::GetValueFromKey(CRegKey::m_regKeySkuType);
    skuRegion = CRegKey::m_skuEurope;
    if (strcmp(skuValue, skuRegion) == 0)
       CGameInfo::SetGameRegion(0);
    else
    {
       // america sku check
       skuValue = CRegKey::GetValueFromKey(CRegKey::m_regKeySkuType);
       skuRegion = CRegKey::m_skuAmerica;
       if (strcmp(skuValue, skuRegion) == 0)
           CGameInfo::SetGameRegion(1);
       else
       {
           // japan sku check
           skuValue = CRegKey::GetValueFromKey(CRegKey::m_regKeySkuType);
           skuRegion = CRegKey::m_skuJapan;
           if (strcmp(skuValue, skuRegion) == 0)
               CGameInfo::SetGameRegion(2);
           else
           {
               // poland sku check
               skuValue = CRegKey::GetValueFromKey(CRegKey::m_regKeySkuType);
               skuRegion = CRegKey::m_skuPoland;
               if (strcmp(skuValue, skuRegion) == 0)
                   CGameInfo::SetGameRegion(3);
               else // otherwise die
                   CGame::SetShouldExit();
           }
       }
    }

    CGameInfo::FUN_004f4b40();
    m_unk0x00523d68 = 1;
    m_unk0x008180f9 = 0;
    m_unk0x008180fc = FUN_004ea880();
    if (FUN_004ea880() != 0)
    {
        FUN_004083e0(0);
        FUN_00406810(0);
        FUN_004067e0();
        CGameInfo::FUN_00405de0(0);

        // if (CInstallInfo::FUN_0040e8d0() != 0)
        // {
            CGameInfo::FUN_00510410();
            CGameInfo::FUN_00406560();
            CGameInfo::FUN_00406580();
            CGameInfo::SetupInputs();
            didLoadGameInfo = CGameInfo::LoadGameInfo();
            CNetworkLeaderboards::Reset();
            CNetworkLeaderboards::LoadLeaderboards();
            CGameInfo::FUN_00405de0(0);
            if (CGraphics::InitializeDirectX()) {
                CGraphics::SetDefaults();
            }
            CInput::LoadControllerInfo();
            CGameInfo::FUN_0049ea90(1);
            CGameInfo::FUN_004d05d0();
            if (FUN_004aaa40() != false) {
                CGame::FUN_004d0a50(0x1);
            }
        // }
    }

    CGame::SetShouldExit();
}

// FUNCTION: CMR2 0x0049c2c0
void CGame::FUN_0049c2c0(Unk0049c2c0 *param1)
{
    FuncTableEntry func;
    BYTE counter;
    BYTE unkIx;

    counter = 0;
    unkIx = 0;
    if (param1->count > 0)
    {
        do
        {
            func = param1->funcLookupTable[param1->unk[unkIx].field0x1 & 0xFF].func1;
            if (func != NULL)
                (func)(param1, unkIx);

            counter++;
            unkIx = counter;
        } while (counter < param1->count);
    }
}

// FUNCTION: CMR2 0x0049c310
void CGame::FUN_0049c310(Unk0049c2c0 *param1)
{
    OtherFuncTableEntry func;
    BYTE counter;
    BYTE unkIx;

    if (m_unk0x00593cac == 0)
    {

        counter = 0;
        unkIx = 0;
        if (param1->count > 0)
        {
            do
            {
                func = param1->funcLookupTable[param1->unk[unkIx].field0x1 & 0xFF].func2;
                if (func != NULL)
                    (func)(param1, unkIx);

                counter++;
                unkIx = counter;
            } while (counter < param1->count);
        }
    }
    else
        m_unk0x00593cac = 0;
}

// FUNCTION: CMR2 0x0049c370
void CGame::FUN_0049c370(Unk0049c2c0 *param1)
{
    unsigned int tVar1;

    m_unk0x00593ba8 = m_unk0x00593ba8 & 0xffffff00;
    if (param1->count > 0)
    {
        do
        {
            m_unk0x00593ba4 = &param1->unk[m_unk0x00593ba8];
            tVar1 = m_unk0x00593ba4->field0x1;
            if (tVar1 & 0x3000000)
            {
                m_unk0x00593ba4->field0x1 = ((tVar1 >> 0x10) & 0xff) | (tVar1 & 0xffffff00);
                m_unk0x00593ba4->field0x1 = m_unk0x00593ba4->field0x1 & 0xff00ffff;
                m_unk0x00593ba4->field0x1 = m_unk0x00593ba4->field0x1 & 0xfcffffff;
                m_unk0x00593ba4->field0x2 = 0;
            }
            else
                m_unk0x00593ba4->field0x2 = m_unk0x00593ba4->field0x2 + 1;

            m_unk0x00593ba8++;
        } while (m_unk0x00593ba8 < param1->count);
    }
}

// FUNCTION: CMR2 0x0049c150
void CGame::FUN_0049c150(Unk00817d98 *param1, int param2, int param3)
{
    param1->field0x2 = 0;
    param1->field0x1 =
        (param1->field0x1 >> 8 & 0xfc0000) << 8 | param2 & 0xffU | (param3 & 0xffU) << 8;
}

// FUNCTION: CMR2 0x0049c190
void CGame::FUN_0049c190(Unk0049c2c0 *p1, BYTE count, Unk00817d98 *unk, FuncTableGroup *funcLookupTable, void *unk2)
{
    p1->count = count;
    p1->unk = unk;
    p1->funcLookupTable = funcLookupTable;
    p1->unk2 = unk2;
}
// STUB: CMR2 0x004ff450
BOOL CGame::FUN_004ff450() { return FALSE; }
// STUB: CMR2 0x0041b060
BOOL CGame::FUN_0041b060() { return FALSE; }

// FUNCTION: CMR2 0x00501680
void CGame::FUN_00501680(struct Unk0049c2c0 *, BYTE) { return; }

// FUNCTION: CMR2 0x004ea880
BYTE CGame::FUN_004ea880(void) { return m_unk0x00516120; }

// FUNCTION: CMR2 0x004083e0
void CGame::FUN_004083e0(BYTE param1)
{
    m_unk0x00531768 = param1;
}

// FUNCTION: CMR2 0x00406810
void CGame::FUN_00406810(BYTE param1)

{
    m_unk0x0052ea59 = param1;
    return;
}

// FUNCTION CMR2 0x004067e0
bool CGame::FUN_004067e0(void)
{
    if (m_unk0x0052ea58 != 0)
    {
        m_unk0x0052ea58 = 0;
        return true;
    }
    return false;
}

// FUNCTION: CMR2 0x0049c0a0
int CGame::RegisterCallback(void *param1, void *param2) {
    int iVar2;
    void **piVar3;

    if (param1 == NULL)
        return -1;

    iVar2 = 0;
    if (m_unk0x00593ba0 > 0) {
        piVar3 = &m_unk0x005939a0;
        while (1) {
            if (param1 == *piVar3)
                return iVar2;
    
            iVar2++;
            piVar3++;
            
            if (iVar2 >= m_unk0x00593ba0) break;
        }
    }

    if (m_unk0x00593ba0 >= 0x40)
        return -1;

    (&m_unk0x005939a0)[m_unk0x00593ba0] = param1;
    return m_unk0x00593ba0++;
}

// FUNCTION: CMR2 0x004a17b0
void CGame::FUN_004a17b0(void) {
    m_unk0x005a1fbc = FALSE;
    if (m_unk0x005a1fb8 != NULL) {
        CFileBuffer::FreeGenericFileBuffer(m_unk0x005a1fb8);
        m_unk0x005a1fb8 = NULL;
    }    
}

// FUNCTION: CMR2 0x004a17f0
void CGame::FUN_004a17f0(bool param1) {
    if (param1)
        m_unk0x005a1fc0 = false;

    Unk0x005a1820 *dest = m_unk0x005a1820;
    do {
        sprintf(dest->field_0x64, CMain::m_logFileBlankLine);
        sprintf(dest->field_0x0, CMain::m_logFileBlankLine);
        dest->field_0xc8 = 0;
        dest->field_0xcc = 0;
        dest++;
    } while ((int)dest < (int)&m_unk0x005a1e34);

    m_unk0x005a1818 = 0;
}

// FUNCTION: CMR2 0x004a1a90
BOOL CGame::FUN_004a1a90(void) {
    IDirectPlay4A *pVar1;
    HRESULT hr;
    if (m_unk0x005a1fc0) {
        pVar1 = GetDirectPlay();
        if (pVar1 != NULL) {
            hr = pVar1->DestroyPlayer(m_unk0x005a1ea0);
            if (hr > DPERR_UNAVAILABLE && hr != DPERR_CONNECTIONLOST && hr == DP_OK)
                return TRUE;
        }
    }

    return FALSE;
}

// FUNCTION: CMR2 0x004aaa10
void CGame::FUN_004aaa10(void) {
    Unk0x00664750* puVar1;
    puVar1 = m_unk0x00664750;
    do {
        if (puVar1->field_0x0 != NULL) {
            CFileBuffer::FreeGenericFileBuffer(puVar1->field_0x0);
            puVar1->field_0x0 = NULL;
        }
        puVar1++;
    } while ((int)puVar1 < (int)&m_unk0x00665218);
}

// FUNCTION: CMR2 0x004aaac0
bool CGame::Cleanup(void)
{
  FUN_004a1a90();
  DestroyDirectPlayLobby();
  DestroyDirectPlay();
  FUN_004aaa10();
  FUN_004a17b0();
  CoUninitialize();
  return 1;
}

// FUNCTION: CMR2 0x004aab40
void CGame::DestroyDirectPlay(void) {
    if (m_pDirectPlay4A != NULL) {
        m_pDirectPlay4A->Release();
        m_pDirectPlay4A = NULL;
    }
}

// FUNCTION: CMR2 0x004aabb0
void CGame::DestroyDirectPlayLobby(void) {
    if (m_pDirectPlayLobby3A != NULL) {
        m_pDirectPlayLobby3A->Release();
        m_pDirectPlayLobby3A = NULL;
    }
}

// FUNCTION: CMR2 0x004aad40
IDirectPlay4A* CGame::GetDirectPlay(void) {
    return m_pDirectPlay4A;
}

// FUNCTION: CMR2 0x004aaa40
bool CGame::FUN_004aaa40(void) {
    Unk0x00664750 *puVar1;

    m_pDirectPlay4A = NULL;
    m_pDirectPlayLobby3A = NULL;

    CGameInfo::FUN_004a0c60();
    FUN_004a17f0(true);
    FUN_004a17b0();
    
    puVar1 = m_unk0x00664750;
    do {
        sprintf((char*)&puVar1[-1].field_0x14, CMain::m_logFileBlankLine);
        puVar1->field_0x0 = NULL;
        puVar1++;
    } while ((int)puVar1 < (int)&m_unk0x00665218);

    m_unk0x00664750[9].field_0x15 = '\0';
    CoInitialize(NULL);

    RegisterCallback(Cleanup, NULL);

    return true;
}

// FUNCTION: CMR2 0x004d0a50
bool CGame::FUN_004d0a50(bool param1) {
    BOOL didLoadSplashScreens;
    BOOL bVar2;

    didLoadSplashScreens = LoadSplashScreens(param1);
    if (didLoadSplashScreens != FALSE) {
        FUN_0040bab0(TRUE);
        FUN_004e2e50();
        
        return true;
    }

    return false;
}

// STUB: CMR2 0x004d08d0
bool CGame::LoadSplashScreens(BYTE param1) {
    return true;
}

// FUNCTION: CMR2 0x0040bab0
void CGame::FUN_0040bab0(BOOL param1) {
    m_unk0x00532138 = param1;
}

// FUNCTION: CMR2 0x004e2e50
void CGame::FUN_004e2e50(void) {
    char* countries[8] = {
        m_strFinland,
        m_strGreece, 
        m_strFrance,
        m_strSweden,
        m_strKenya,
        m_strItaly,
        m_strUK,
        m_strAus
    };

    char* countryShort[8] = {
        m_strFin,
        m_strGre,
        m_strFra,
        m_strSwe,
        m_strKen,
        m_strIta,
        m_strUK,
        m_strAus
    };

    sprintf(CFrontend::m_stringDest, CFrontend::m_strFrontendTexturesAr640ATGA, CInstallInfo::GetGameCDPath());
    CFrontend::m_pAr640ATexture = CTexture::FindLoadTexture(CGenericFileLoader::GetGenericFile(), CFrontend::m_stringDest, NULL, NULL, false, 0);

    sprintf(CFrontend::m_stringDest, CFrontend::m_strFrontendTexturesAr640DTGA, CInstallInfo::GetGameCDPath());
    CFrontend::m_pAr640DTexture = CTexture::FindLoadTexture(CGenericFileLoader::GetGenericFile(), CFrontend::m_stringDest, NULL, NULL, false, 0);

    sprintf(CFrontend::m_stringDest, CFrontend::m_strFrontendTexturesLgMatrixTGA, CInstallInfo::GetGameCDPath());
    CFrontend::m_pLgMatrixTexture = CTexture::FindLoadTexture(CGenericFileLoader::GetGenericFile(), CFrontend::m_stringDest, NULL, NULL, false, 0);

    sprintf(CFrontend::m_stringDest, CFrontend::m_strFrontendTexturesSmMatrixTGA, CInstallInfo::GetGameCDPath());
    CFrontend::m_pSmMatrixTexture = CTexture::FindLoadTexture(CGenericFileLoader::GetGenericFile(), CFrontend::m_stringDest, NULL, NULL, false, 0);

    for (int i = 0; i < 8; i++) {
        sprintf(CFrontend::m_stringDest, CFrontend::m_strSetupRepTexturesBanners, CInstallInfo::GetGameCDPath(), countries[i]);
        CFrontend::m_pSetupRepBanners[i] = CTexture::FindLoadTexture(CGenericFileLoader::GetGenericFile(), CFrontend::m_stringDest, NULL, NULL, false, 0);

        sprintf(CFrontend::m_stringDest, CFrontend::m_strFrontendTinyFlags, CInstallInfo::GetGameCDPath(), countryShort[i]);
        CFrontend::m_pTinyFlags[i] = CTexture::FindLoadTexture(CGenericFileLoader::GetGenericFile(), CFrontend::m_stringDest, NULL, NULL, false, 0);
    }
}
