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

GenericFile CFrontend::m_unk0x00818260;

// FUNCTION: CMR2 0x004d21e0
void __stdcall CFrontend::FUN_004d21e0(void)
{
    int iVar1, iVar2, iVar3, iVar5, iVar6, iVar7, iVar8, iVar9;
    BOOL bVar;
    unsigned int screenWidth, regionID;
    char *frontendDir, *regionDir, *countrySpecificDir, *filePath;
    char regionKey;

    if (CGenericFileLoader::m_genericFile.buffer != NULL)
    {
        FreeGenericFileBuffer(CGenericFileLoader::m_genericFile.buffer);
        CGenericFileLoader::m_genericFile.buffer = NULL;
    }

    CGenericFileLoader::m_genericFile.didFileLoad = NULL;
    CGenericFileLoader::m_genericFile.fileSize = NULL;

    if (CGameInfo::GetScreenWidth() > 1024U)
    {
        iVar7 = FUN_004b7560(1024);
        if (iVar7 != 0)
        {
            iVar8 = FUN_004b7590(1024);
            if (iVar8 != 0)
            {
                iVar9 = FUN_004a9700();
                if (iVar9 != FALSE)
                {
                    frontendDir = CInstallInfo::GetFrontendDir();
                    sprintf(m_stringDest, m_feRes1024C, frontendDir);
                }
                else
                {
                    frontendDir = CInstallInfo::GetFrontendDir();
                    sprintf(m_stringDest, m_feRes1024, frontendDir);
                }
            }
        }
    }

    iVar1 = FUN_004a9700();
    if (iVar1 != FALSE)
    {
        frontendDir = CInstallInfo::GetFrontendDir();
        sprintf(m_stringDest, m_feRes640C, frontendDir);
    }
    else
    {
        frontendDir = CInstallInfo::GetFrontendDir();
        sprintf(m_stringDest, m_feRes640, frontendDir);
    }

    CGenericFileLoader::FUN_004a9d70(&CGenericFileLoader::m_genericFile, m_stringDest);
    if (m_unk0x00818260.buffer != NULL)
    {
        FreeGenericFileBuffer(m_unk0x00818260.buffer);
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

    if (CGameInfo::GetScreenWidth() > 1024U)
    {
        iVar2 = FUN_004b7560(1024);
        if (iVar2 != FALSE)
        {
            iVar3 = FUN_004b7590(1024);
            if (iVar3 != FALSE)
            {
                bVar = FUN_004a9700();
                if (bVar != FALSE)
                {
                    iVar5 = regionKey;
                    regionDir = CGameInfo::GetGameRegionDirectory();
                    countrySpecificDir = CInstallInfo::GetCountrySpecificDir();
                    sprintf(m_stringDest, m_feRes1024CountrySpecific, countrySpecificDir, regionDir, iVar5);
                }
                else
                {
                    iVar5 = regionKey;
                    regionDir = CGameInfo::GetGameRegionDirectory();
                    countrySpecificDir = CInstallInfo::GetCountrySpecificDir();
                    sprintf(m_stringDest, m_feRes1024CCountrySpecific, countrySpecificDir, regionDir, iVar5);
                }
            }
        }
    }
    else
    {
        bVar = FUN_004a9700();
        if (bVar != FALSE)
        {
            regionDir = CGameInfo::GetGameRegionDirectory();
            countrySpecificDir = CInstallInfo::GetCountrySpecificDir();
            sprintf(m_stringDest, m_feRes640CountrySpecific, countrySpecificDir, regionDir);
        }
        else
        {
            regionDir = CGameInfo::GetGameRegionDirectory();
            countrySpecificDir = CInstallInfo::GetCountrySpecificDir();
            sprintf(m_stringDest, m_feRes640CCountrySpecific, countrySpecificDir, regionDir);
        }
    }

    CGenericFileLoader::FUN_004a9d70(&m_unk0x00818260, m_stringDest);
}

// STUB: CMR2 0x004b7560
BOOL __stdcall CFrontend::FUN_004b7560(unsigned int param_1)
{
    if (((unsigned int)0x006e0c5c <= param_1) && (param_1 <= (unsigned int)0x006e0c64))
    {
        return 1;
    }
    return 0;
}

// STUB: CMR2 0x004b7590
BOOL __stdcall CFrontend::FUN_004b7590(unsigned int param_1)
{
    if (((unsigned int)0x006e0c60 <= param_1) && (param_1 <= (unsigned int)0x006e0c68))
    {
        return 1;
    }
    return 0;
}

// STUB: CMR2 0x004a9700
BOOL __stdcall CFrontend::FUN_004a9700(void)
{
    if (((unsigned int)0x00663b38 == 0) && ((unsigned int)0x00663b48 == 0))
    {
        return 0;
    }
    return 1;
}
