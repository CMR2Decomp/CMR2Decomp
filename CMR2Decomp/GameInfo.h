#ifndef _GAME_INFO_H
#define _GAME_INFO_H

typedef unsigned char undefined;
struct GameInfo
{
    unsigned char empty[16];
    int magicNumber;          /* Always 0x11 */
    unsigned int field2_0x14; /* first byte of this contains language */
    int field3_0x18;
    undefined field4_0x1c;
    undefined field5_0x1d;
    undefined field6_0x1e;
    undefined field7_0x1f;
    undefined field8_0x20;
    undefined field9_0x21;
    undefined field10_0x22;
    undefined field11_0x23;
    int screenWidth;
    int screenHeight;
    int screenColourDepth;
    undefined field15_0x30_field14704_0x399a;
};

class CGameInfo
{
public:
    static unsigned char GetGameLanguage(void);
    static unsigned int GetGameRegion(void);
    static unsigned char FUN_00405d80(void);
    static unsigned char FUN_00405d90(void);
    static int __stdcall GetScreenWidth(void);
    static int __stdcall GetScreenHeight(void);
    static int __stdcall GetColourDepth(void);
    static char *__stdcall GetInstalledFrontendDir();

    // GLOBAL: CMR2 0x0052afa0
    static GameInfo m_gameInfo;
    // GLOBAL: CMR2 0x0052ea54
    static unsigned int m_gameRegion;
    // GLOBAL: CMR2 0x005366bc
    static char m_installedFrontendDir[260];
};

#endif
