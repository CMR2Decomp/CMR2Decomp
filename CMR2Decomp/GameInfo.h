#ifndef _GAME_INFO_H
#define _GAME_INFO_H

#include <windows.h>

struct GameInfo
{
    unsigned char empty[16];
    int magicNumber;          /* Always 0x11 */
    unsigned int field2_0x14; /* first byte of this contains language */
    int field3_0x18;
    BYTE field4_0x1c;
    BYTE field5_0x1d;
    BYTE field6_0x1e;
    BYTE field7_0x1f;
    BYTE field8_0x20;
    BYTE field9_0x21;
    BYTE field10_0x22;
    BYTE field11_0x23;
    int screenWidth;
    int screenHeight;
    int screenColourDepth;
    BYTE field15_0x30_field14704_0x399a;
};

class CGameInfo
{
public:
    static unsigned char GetGameLanguage(void);
    static unsigned int GetGameRegion(void);
    static void __stdcall SetGameRegion(unsigned int region);
    static unsigned char FUN_00405d80(void);
    static unsigned char FUN_00405d90(void);
    static unsigned int GetScreenWidth(void);
    static void SetScreenWidth(unsigned int width);
    static unsigned int GetScreenHeight(void);
    static void SetScreenHeight(unsigned int height);
    static unsigned int GetColourDepth(void);
    static void SetColourDepth(unsigned int depth);
    static char *GetGameRegionDirectory(void);
    static void FUN_004f4b40(void);
    static void __stdcall FUN_00405de0(BYTE param1);

    // GLOBAL: CMR2 0x0052afa0
    static GameInfo m_gameInfo;
    // GLOBAL: CMR2 0x0052ea54
    static unsigned int m_gameRegion;

    // GLOBAL: CMR2 0x00516124
    static char *m_gameRegionStrings[4];

    // GLOBAL: CMR2 0x0081a754
    static int m_unk0x0081a754;
};

#endif
