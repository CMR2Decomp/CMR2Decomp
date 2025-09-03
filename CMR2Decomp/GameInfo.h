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
    unsigned int field_0x14;
    unsigned int field_0x18;
    unsigned int field_0x1c;
    unsigned int field_0x88;
    unsigned int field_0x8c;
    unsigned int field_0x90;
    short field_0x94;
    unsigned int field_0x98;
    unsigned int field_0x9c;
    char field_0x3950[21];
    char field_0x3965[23];
    int field_0x397c;
    BYTE field_0x3980;
    BYTE pad[3];
    int field_0x3984;
    int field_0x3988;
    int field_0x398c;
    int field_0x3990;
    BYTE buffer[3500];
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
    static void __stdcall SetScreenWidth(unsigned int width);
    static unsigned int GetScreenHeight(void);
    static void __stdcall SetScreenHeight(unsigned int height);
    static unsigned int GetColourDepth(void);
    static void __stdcall SetColourDepth(unsigned int depth);
    static char *GetGameRegionDirectory(void);
    static void FUN_004f4b40(void);
    static void __stdcall FUN_00405de0(BYTE param1);
    static void FUN_00510410(void);
    static void FUN_00510570(void);

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
