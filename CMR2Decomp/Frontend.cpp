#include "Frontend.h"
#include "FileBuffer.h"
#include "GameInfo.h"
#include "InstallInfo.h"

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

char CFrontend::m_strSetupRepTexturesBanners[40] = "%s\\setuprep\\Textures\\banners\\b%s.tga";
char CFrontend::m_strFrontendTinyFlags[40] = "%s\\frontend\\Textures\\tinyflags\\t%s.tga";
char CFrontend::m_strFrontendTexturesTBronzeTGA[36] = "%s\\frontend\\Textures\\tbronze.tga";
char CFrontend::m_strFrontendTexturesTSilverTGA[36] = "%s\\frontend\\Textures\\tsilver.tga";
char CFrontend::m_strFrontendTexturesTGoldTGA[32] = "%s\\frontend\\Textures\\tgold.tga";

GenericFile CFrontend::m_unk0x00818260;
unsigned int CFrontend::m_unk0x006e0c5c;
unsigned int CFrontend::m_unk0x006e0c64;
unsigned int CFrontend::m_unk0x006e0c60;
unsigned int CFrontend::m_unk0x006e0c68;
unsigned int CFrontend::m_unk0x00663b38;
unsigned int CFrontend::m_unk0x00663b48;

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
