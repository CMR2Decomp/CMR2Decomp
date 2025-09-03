#include "GameInfo.h"

// GLOBAL: CMR2 0x00516134
char gameRegionPoland[9] = "\\Poland\\";
// GLOBAL: CMR2 0x00516140
char gameRegionJapan[8] = "\\Japan\\";
// GLOBAL: CMR2 0x00516148
char gameRegionUSA[6] = "\\Usa\\";
// GLOBAL: CMR2 0x00516150
char gameRegionEurope[9] = "\\Europe\\";

GameInfo CGameInfo::m_gameInfo;
unsigned int CGameInfo::m_gameRegion;
char *CGameInfo::m_gameRegionStrings[4] = {
    gameRegionEurope, gameRegionUSA, gameRegionJapan, gameRegionPoland};

int CGameInfo::m_unk0x0081a754;

// FUNCTION: CMR2 0x004057f0
unsigned char CGameInfo::GetGameLanguage(void)
{
    return m_gameInfo.field2_0x14 & 7;
}

// FUNCTION: CMR2 0x00405800
unsigned int CGameInfo::GetGameRegion(void)
{
    return m_gameRegion;
}

// FUNCTION: CMR2 0x00405810
void __stdcall CGameInfo::SetGameRegion(unsigned int region)
{
    m_gameRegion = region;
}

// FUNCTION: CMR2 0x00405820
char *CGameInfo::GetGameRegionDirectory(void)
{
    return m_gameRegionStrings[m_gameRegion];
}

// FUNCTION: CMR2 0x00405d80
unsigned char CGameInfo::FUN_00405d80(void)
{
    return m_gameInfo.field2_0x14 >> 3 & 0x7f;
}

unsigned char CGameInfo::FUN_00405d90(void)
{
    return m_gameInfo.field2_0x14 >> 10 & 7;
}

// FUNCTION: CMR2 0x00405c10
unsigned int CGameInfo::GetScreenWidth(void)
{
    return m_gameInfo.screenWidth;
}

// FUNCTION: CMR2 0x00405c30
unsigned int CGameInfo::GetScreenHeight(void)
{
    return m_gameInfo.screenHeight;
}

// FUNCTION: CMR2 0x00405c50
unsigned int CGameInfo::GetColourDepth(void)
{
    return m_gameInfo.screenColourDepth;
}

// FUNCTION: CMR2 0x00405c20
void CGameInfo::SetScreenWidth(unsigned int width)
{
    m_gameInfo.screenWidth = width;
}

// FUNCTION: CMR2 0x00405c40
void CGameInfo::SetScreenHeight(unsigned int height)
{
    m_gameInfo.screenHeight = height;
}

// FUNCTION: CMR2 0x00405c60
void CGameInfo::SetColourDepth(unsigned int depth)
{
    m_gameInfo.screenColourDepth = depth;
}

// FUNCTION: CMR2 0x004f4b40
void CGameInfo::FUN_004f4b40(void)
{
    switch (GetGameRegion())
    {
    case 0:
        m_unk0x0081a754 = 5;
        return;
    case 1:
        m_unk0x0081a754 = 3;
        return;
    case 2:
    case 3:
        m_unk0x0081a754 = 1;
    }
}

// FUNCTION: CMR2 0x00405de0
void __stdcall CGameInfo::FUN_00405de0(BYTE param1)
{
    m_gameInfo.field2_0x14 = ((param1 & 1) << 0x13) | (m_gameInfo.field2_0x14 & 0xfff7ffffU);
}
