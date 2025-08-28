#include "GameInfo.h"

GameInfo CGameInfo::m_gameInfo;
unsigned int CGameInfo::m_gameRegion;
char CGameInfo::m_installedFrontendDir[260];

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
int __stdcall CGameInfo::GetScreenWidth(void)
{
    return m_gameInfo.screenWidth;
}

// FUNCTION: CMR2 0x00405c30
int __stdcall CGameInfo::GetScreenHeight(void)
{
    return m_gameInfo.screenHeight;
}

// FUNCTION: CMR2 0x00405c50
int __stdcall CGameInfo::GetColourDepth(void)
{
    return m_gameInfo.screenColourDepth;
}

// FUNCTION: CMR2 0x0040ed90
char *__stdcall CGameInfo::GetInstalledFrontendDir()
{
    return m_installedFrontendDir;
}
