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
unsigned int CFrontend::m_unk0x006e0c5c;
unsigned int CFrontend::m_unk0x006e0c64;
unsigned int CFrontend::m_unk0x006e0c60;
unsigned int CFrontend::m_unk0x006e0c68;
unsigned int CFrontend::m_unk0x00663b38;
unsigned int CFrontend::m_unk0x00663b48;

// FUNCTION: CMR2 0x004d21e0
void __stdcall CFrontend::FUN_004d21e0(void)
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
BOOL __stdcall CFrontend::FUN_004b7560(unsigned int param_1)
{
    if (m_unk0x006e0c5c <= param_1 && param_1 <= m_unk0x006e0c64)
        return TRUE;

    return FALSE;
}

// FUNCTION: CMR2 0x004b7590
BOOL __stdcall CFrontend::FUN_004b7590(unsigned int param_1)
{
    if (m_unk0x006e0c60 <= param_1 && param_1 <= m_unk0x006e0c68)
        return TRUE;

    return FALSE;
}

// FUNCTION: CMR2 0x004a9700
BOOL __stdcall CFrontend::FUN_004a9700(void)
{
    if (!m_unk0x00663b38 && !m_unk0x00663b48)
        return FALSE;

    return TRUE;
}
