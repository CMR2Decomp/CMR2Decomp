#include "Frontend.h"
#include "FileBuffer.h"
#include "GameInfo.h"
#include "InstallInfo.h"
#include "main.h"

#include <stdio.h>

char CFrontend::m_stringDest[MAX_PATH];

char CFrontend::m_feRes640CountrySpecific[19] = "%s%sFERes640%c.bfl";
char CFrontend::m_feRes640CCountrySpecific[20] = "%s%sFERes640%cC.bfl";
char CFrontend::m_feRes1024CountrySpecific[20] = "%s%sFERes1024%c.bfl";
char CFrontend::m_feRes1024CCountrySpecific[21] = "%s%sFERes1024%cC.bfl";
char CFrontend::m_feRes640[14] = "%s\\Res640.bfl";
char CFrontend::m_feRes640C[15] = "%s\\Res640C.bfl";
char CFrontend::m_feRes1024[15] = "%s\\Res1024.bfl";
char CFrontend::m_feRes1024C[16] = "%s\\Res1024C.bfl";
char CFrontend::m_strFrontendTexturesAr640ATGA[36] = "%s\\frontend\\Textures\\Ar_640A.tga";
char CFrontend::m_strFrontendTexturesAr640DTGA[36] = "%s\\frontend\\Textures\\Ar_640D.tga";
char CFrontend::m_strFrontendTexturesLgMatrixTGA[36] = "%s\\frontend\\Textures\\LgMatrix.tga";
char CFrontend::m_strFrontendTexturesSmMatrixTGA[36]= "%s\\frontend\\Textures\\SmMatrix.tga";
Texture* CFrontend::m_pAr640ATexture;
Texture* CFrontend::m_pAr640DTexture;
Texture* CFrontend::m_pLgMatrixTexture;
Texture* CFrontend::m_pSmMatrixTexture;
Texture* CFrontend::m_pSetupRepBanners[8];
Texture* CFrontend::m_pTinyFlags[8];
Texture* CFrontend::m_pTBronze;
Texture* CFrontend::m_pTSilver;
Texture* CFrontend::m_pTGold;

char CFrontend::m_strUK[3] = "UK";
char CFrontend::m_strIta[4] = "Ita";
char CFrontend::m_strKen[4] = "Ken";
char CFrontend::m_strItaly[8] = "Italy";
char CFrontend::m_strAus[4] = "Aus";
char CFrontend::m_strSwe[4] = "Swe";
char CFrontend::m_strKenya[8] = "Kenya";
char CFrontend::m_strFra[4] = "Fra";
char CFrontend::m_strSweden[8] = "Sweden";
char CFrontend::m_strFrance[8] = "France";
char CFrontend::m_strGre[4] = "Gre";
char CFrontend::m_strFin[4] = "Fin";
char CFrontend::m_strFinland[8] = "Finland";
char CFrontend::m_strGreece[8] = "Greece";

char CFrontend::m_strEsc[4] = "Esc";
char CFrontend::m_strPum[4] = "Pum";
char CFrontend::m_str205[4] = "205";
char CFrontend::m_strStr[4] = "Str";
char CFrontend::m_str6R4[4] = "6R4";
char CFrontend::m_strMin[4] = "Min";
char CFrontend::m_strSie[4] = "Sie";
char CFrontend::m_strIA2[4] = "IA2";
char CFrontend::m_strIA1[4] = "IA1";
char CFrontend::m_strInt[4] = "Int";
char CFrontend::m_strSea[4] = "Sea";
char CFrontend::m_str206[4] = "206";
char CFrontend::m_strSubShort[4] = "Sub";
char CFrontend::m_strCor[4] = "Cor";
char CFrontend::m_strMA3[4] = "MA3";
char CFrontend::m_strMA2[4] = "MA2";
char CFrontend::m_strMA1[4] = "MA1";
char CFrontend::m_strMit[4] = "Mit";
char CFrontend::m_strFA2[4] = "FA2";
char CFrontend::m_strFA1[4] = "FA1";
char CFrontend::m_strF99Short[4] = "F99";
char CFrontend::m_strFoc[4] = "Foc";
char CFrontend::m_strEscort[7] = "escort";
char CFrontend::m_strPuma[7] = "puma";
char CFrontend::m_strStrts[7] = "strts";
char CFrontend::m_str6r4[4] = "6r4";
char CFrontend::m_strMini[7] = "mini";
char CFrontend::m_strSerra[7] = "serra";
char CFrontend::m_strDelta[7] = "delta";
char CFrontend::m_strCrdba[7] = "crdba";
char CFrontend::m_strSub[4] = "sub";
char CFrontend::m_strCrlla[7] = "crlla";
char CFrontend::m_strLncer[7] = "lncer";
char CFrontend::m_strF99[4] = "f99";
char CFrontend::m_strF2000[7] = "f2000";

char CFrontend::m_strSetupRepTexturesBanners[40] = "%s\\setuprep\\Textures\\banners\\b%s.tga";
char CFrontend::m_strFrontendTinyFlags[40] = "%s\\frontend\\Textures\\tinyflags\\t%s.tga";
char CFrontend::m_strFrontendTexturesTBronzeTGA[36] = "%s\\frontend\\Textures\\tbronze.tga";
char CFrontend::m_strFrontendTexturesTSilverTGA[36] = "%s\\frontend\\Textures\\tsilver.tga";
char CFrontend::m_strFrontendTexturesTGoldTGA[32] = "%s\\frontend\\Textures\\tgold.tga";

char CFrontend::m_strFrontendTexturesCarsLivery[40] = "%s\\frontend\\Textures\\cars\\livery%d.tga";
char CFrontend::m_strFrontendTexturesCarsB01[36] = "%s\\frontend\\Textures\\cars\\%sB01.tga";
char CFrontend::m_strFrontendTexturesCarsF01[36] = "%s\\frontend\\Textures\\cars\\%sF01.tga";

GenericFile CFrontend::m_unk0x00818260;
unsigned int CFrontend::m_unk0x006e0c5c;
unsigned int CFrontend::m_unk0x006e0c64;
unsigned int CFrontend::m_unk0x006e0c60;
unsigned int CFrontend::m_unk0x006e0c68;
unsigned int CFrontend::m_unk0x00663b38;
unsigned int CFrontend::m_unk0x00663b48;

Texture* CFrontend::m_unk0x00818530[3];
char* CFrontend::m_unk0x0081853c;
Texture* CFrontend::m_unk0x008182cc[22];
Texture* CFrontend::m_unk0x0081884c[22];

// FUNCTION: CMR2 0x004d21e0
void CFrontend::FUN_004d21e0(void)
{
    unsigned int regionID;
    char regionKey;

    if (CGenericFileLoader::m_genericFile.buffer != NULL)
    {
        CFileBuffer::FreeGenericFileBuffer(CGenericFileLoader::m_genericFile.buffer);
        CGenericFileLoader::m_genericFile.buffer = NULL;
    }

    CGenericFileLoader::m_genericFile.didFileLoad = 0;
    CGenericFileLoader::m_genericFile.fileSize = 0;

    if (CGameInfo::GetScreenWidth() >= 1024U)
    {
        if (FUN_004b7560(1024) != 0)
        {
            if (FUN_004b7590(1024) != 0)
            {
                if (FUN_004a9700() != FALSE)
                    sprintf(m_stringDest, m_feRes1024C, CInstallInfo::GetFrontendDir());

                else
                    sprintf(m_stringDest, m_feRes1024, CInstallInfo::GetFrontendDir());
            }
        }
    }
    else
    {

        if (FUN_004a9700() != FALSE)
            sprintf(m_stringDest, m_feRes640C, CInstallInfo::GetFrontendDir());
        else
            sprintf(m_stringDest, m_feRes640, CInstallInfo::GetFrontendDir());
    }

    CGenericFileLoader::FUN_004a9d70(&CGenericFileLoader::m_genericFile, m_stringDest);
    if (m_unk0x00818260.buffer != NULL)
    {
        CFileBuffer::FreeGenericFileBuffer(m_unk0x00818260.buffer);
        m_unk0x00818260.buffer = NULL;
    }
    m_unk0x00818260.didFileLoad = 0;
    m_unk0x00818260.fileSize = 0;

    // almost certainly not how this was written but this gets us better instruction matching
    // this is basically (if regionID is 3, then use poland)
    regionID = CGameInfo::GetGameRegion();
    if (regionID && --regionID && --regionID)
        regionKey = 0x50; // P
    else
        regionKey = 0x45; // E

    if (CGameInfo::GetScreenWidth() >= 1024U)
    {
        if (FUN_004b7560(1024) != FALSE)
        {
            if (FUN_004b7590(1024) != FALSE)
            {
                if (FUN_004a9700())
                    sprintf(m_stringDest, m_feRes1024CCountrySpecific, CInstallInfo::GetCountrySpecificDir(), CGameInfo::GetGameRegionDirectory(), regionKey);
                else
                    sprintf(m_stringDest, m_feRes1024CountrySpecific, CInstallInfo::GetCountrySpecificDir(), CGameInfo::GetGameRegionDirectory(), regionKey);
            }
        }
    }
    else
    {
        if (FUN_004a9700())
            sprintf(m_stringDest, m_feRes640CCountrySpecific, CInstallInfo::GetCountrySpecificDir(), CGameInfo::GetGameRegionDirectory(), regionKey);
        else
            sprintf(m_stringDest, m_feRes640CountrySpecific, CInstallInfo::GetCountrySpecificDir(), CGameInfo::GetGameRegionDirectory(), regionKey);
    }

    CGenericFileLoader::FUN_004a9d70(&m_unk0x00818260, m_stringDest);
}

// FUNCTION: CMR2 0x004b7560
BOOL CFrontend::FUN_004b7560(unsigned int param_1)
{
    if (m_unk0x006e0c5c <= param_1 && param_1 <= m_unk0x006e0c64)
        return TRUE;

    return FALSE;
}

// FUNCTION: CMR2 0x004b7590
BOOL CFrontend::FUN_004b7590(unsigned int param_1)
{
    if (m_unk0x006e0c60 <= param_1 && param_1 <= m_unk0x006e0c68)
        return TRUE;

    return FALSE;
}

// FUNCTION: CMR2 0x004a9700
BOOL CFrontend::FUN_004a9700(void)
{
    if (!m_unk0x00663b38 && !m_unk0x00663b48)
        return FALSE;

    return TRUE;
}

// FUNCTION: CMR2 0x004d2590
void CFrontend::FUN_004d2590(void) {
    int index;
    int ix;
    const char* carNames[22] = {
        m_strF2000,
        m_strF99,
        CMain::m_logFileBlankLine,
        CMain::m_logFileBlankLine,
        m_strLncer,
        CMain::m_logFileBlankLine,
        CMain::m_logFileBlankLine,
        CMain::m_logFileBlankLine,
        m_strCrlla,
        m_strSub,
        m_str206,
        m_strCrdba,
        m_strDelta,
        CMain::m_logFileBlankLine,
        CMain::m_logFileBlankLine,
        m_strSerra,
        m_strMini,
        m_str6r4,
        m_strStrts,
        m_str205,
        m_strPuma,
        m_strEscort
    };

    index = -2;
    ix = 0;
    
    do {
        const char* carName = carNames[ix];
        if (carName[0] != '\0') {
            // Load front texture (F01)
            sprintf(CFrontend::m_stringDest, CFrontend::m_strFrontendTexturesCarsF01, CInstallInfo::GetGameCDPath(), carName);
            m_unk0x0081884c[ix] = CTexture::FindLoadTexture(CGenericFileLoader::GetGenericFile(), CFrontend::m_stringDest, 0, 0, 0, 0);
            
            // Load back texture (B01)
            sprintf(CFrontend::m_stringDest,CFrontend::m_strFrontendTexturesCarsB01, CInstallInfo::GetGameCDPath(), carName);
            m_unk0x008182cc[ix] = CTexture::FindLoadTexture(CGenericFileLoader::GetGenericFile(), CFrontend::m_stringDest, 0, 0, 0, 0);
        } else {
            // Handle blank entries with switch/case based on index
            switch(index) {
                case 0:  // index 0, 1
                case 1:
                    m_unk0x0081884c[ix] = m_unk0x0081884c[1];
                    m_unk0x008182cc[ix] = m_unk0x008182cc[1];
                    break;
                    
                case 3:   // index 3, 4, 5
                case 4:
                case 5:
                    m_unk0x0081884c[ix] = m_unk0x0081884c[4];
                    m_unk0x008182cc[ix] = m_unk0x008182cc[4];
                    break;
                    
                case 11:  // index 11, 12
                case 12:
                    m_unk0x0081884c[ix] = m_unk0x0081884c[12];
                    m_unk0x008182cc[ix] = m_unk0x008182cc[12];
                    break;
            }
        }
        
        index++;
        ix++;
    } while (index + 2 < 22);
    
    // Load livery textures (1-3)
    Texture** pTexture = m_unk0x00818530;
    int liveryIndex = 0;

    do {
        liveryIndex++;  // Increment first so we use 1, 2, 3
        sprintf(CFrontend::m_stringDest, CFrontend::m_strFrontendTexturesCarsLivery, CInstallInfo::GetGameCDPath(), liveryIndex);
        *pTexture = CTexture::FindLoadTexture(CGenericFileLoader::GetGenericFile(), CFrontend::m_stringDest, 0, 0, 0, 0);
        pTexture++;
    } while ((int)pTexture < (int)&m_unk0x0081853c[0]);
}
