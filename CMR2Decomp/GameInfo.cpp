#include "GameInfo.h"
#include "main.h"

#include <stdio.h>

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

char CGameInfo::m_stringCMR[4] = "cmr";

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

// FUNCTION: CMR2 0x00510410
void CGameInfo::FUN_00510410(void)
{
    memset(&m_gameInfo, 0, sizeof(m_gameInfo));
    m_gameInfo.magicNumber = 0x11;

    strcpy(m_gameInfo.field_0x3950, CMain::m_logFileBlankLine);
    strcpy(m_gameInfo.field_0x3965, CMain::m_logFileBlankLine);

    m_gameInfo.field_0x3980 = 8;
    m_gameInfo.field_0x3990 = 8;
    m_gameInfo.field_0x9c = (m_gameInfo.field_0x9c & 0xffc11157U) | 0x11154;
    m_gameInfo.field_0x18 = (m_gameInfo.field_0x18 & 0xfcffffffU) | 0xbc000000;
    m_gameInfo.field_0x1c = (m_gameInfo.field_0x1c & 0xfff33d19U) | 0x33518;
    m_gameInfo.field_0x14 = (m_gameInfo.field_0x14 & 0x807627ffU) | 0x42400;
    m_gameInfo.field_0x397c = 10;
    m_gameInfo.field_0x3984 = 6;
    m_gameInfo.field_0x3988 = 3;
    m_gameInfo.field_0x398c = 30;

    FUN_00510570();

    m_gameInfo.field_0x98 = 4;
    m_gameInfo.field_0x18 = (m_gameInfo.field_0x18 & 0xfff93264) | 0x40393264;

    FUN_00406010(&m_gameInfo.field_0xa4);
    FUN_00406010(m_gameInfo.field_0x1368);
    FUN_00406010(m_gameInfo.field_0x262c);
}

// FUNCTION: CMR2 0x00510570
void CGameInfo::FUN_00510570(void)
{
    m_gameInfo.field_0x88 = 0x18000;
    m_gameInfo.field_0x8c = 0x68000;
    m_gameInfo.field_0x94 = 0x2d;
    m_gameInfo.field_0x90 = 0xe0000;
    return;
}

// FUNCTION: CMR2 0x00406010
void __stdcall CGameInfo::FUN_00406010(GameInfo0xa4 *param1)
{
    unsigned int outerLoop = 0, innerLoop = 0;
    GameInfo0xa4 *base, *otherBlock;

    // [3][5] block array?
    base = param1;

    // loop 3, sub loop 5
    outerLoop = 3;
    do
    {
        otherBlock = base;
        innerLoop = 5;

        do
        {
            strcpy(otherBlock->ident, m_stringCMR);

            otherBlock->bitMask = (otherBlock->bitMask & 0xFFFFC000) | 0x3C000;
            otherBlock->unk1 = 0;
            otherBlock->unk2 = 0;
            otherBlock++;
        } while (--innerLoop != 0);
    } while (--outerLoop != 0);

    // block = param1 + 0xab;

    // // loop 3, sub loop 5
    // outerLoop = 3;
    // do
    // {
    //     innerLoop = 5;
    //     otherBlock = block;

    //     do
    //     {
    //         strcpy((char *)&otherBlock->ident, m_stringCMR);

    //     } while (--innerLoop != 0);

    // } while (--outerLoop != 0);
    // loop 3, sub loop 3
}
