#ifndef _GAME_INFO_H
#define _GAME_INFO_H

#include <windows.h>

struct GameInfo0xa4SubStruct8 {
	char ident[4];
	unsigned int value;
};

struct GameInfo0xa4SubStruct12 {
	char ident[4];
	unsigned int flags;
	unsigned int value;
};

// and this is actually meant to be 0x12c4 (4804) bytes in size.
struct GameInfo0xa4
{
	GameInfo0xa4SubStruct12 firstLoop[15];
	GameInfo0xa4SubStruct12 secondLoop[120];
	GameInfo0xa4SubStruct8 rallyStageRecordTimes[88];
	short rallyStageRecordSplits[88][10];
	GameInfo0xa4SubStruct12 thirdLoop[45];
	GameInfo0xa4SubStruct8 arcadeRecordTimes[9];
	short arcadeRecordSplits[9][6];
};

// looks like this should be 0x3958 (14680) bytes in size.
struct GameInfo
{
    unsigned char empty[16];
    int magicNumber;          /* Always 0x11 */
    unsigned int field_0x14; /* first byte of this contains language */
    int field_0x18;
    int field_0x1c;
    BYTE field_0x20_padding[4];
    int screenWidth;
    int screenHeight;
    int screenColourDepth;
    unsigned int unknownGraphicsOptions; // first byte is fullscreen
    unsigned int field_0x34;
    char graphicsCardName[80];
    unsigned int field_0x88;
    unsigned int field_0x8c;
    unsigned int field_0x90;
    WORD field_0x94;
    BYTE field_0x96_padding[2];
    short field_0x98;
    short field_0x9a;
    unsigned int field_0x9c;
    unsigned int field_0xa0;
    GameInfo0xa4 field_0xa4;
    GameInfo0xa4 field_0x1368;
    GameInfo0xa4 field_0x262c;
    unsigned int field_0x38f0;
    unsigned int field_0x38f4;
    char field_0x38f8[88];
    char field_0x3950[21];
    char field_0x3965[21];
    short field_0x397a;
    int field_0x397c;
    BYTE field_0x3980;
    BYTE field_0x3981_padding[3];
    int field_0x3984;
    int field_0x3988;
    int field_0x398c;
    int field_0x3990;
    BYTE field_0x3994_padding[5]; // seems wrong that this 5 bytes, but we're a byte short without it
};

class CGameInfo
{
public:
    static unsigned char GetGameLanguage(void);
    static unsigned int GetGameRegion(void);
    static void SetGameRegion(unsigned int region);
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
    static void FUN_00405de0(BYTE param1);
    static void FUN_00510410(void);
    static void FUN_00510570(void);
    static void FUN_00406010(GameInfo0xa4 *param1);
    static void FUN_00406560(void);
    static void FUN_00406580(void);
    static DWORD SetupInputs(void);
    static bool LoadGameInfo(void);
    static unsigned int IsFullscreen(void);
    static int FUN_00405ca0(void);
    static bool FUN_00406410(int param1);
    static bool FUN_004eac50(int param1);
    static void FUN_004d0590(BYTE param1);

    // GLOBAL: CMR2 0x0052afa0
    static GameInfo m_gameInfo;

    // GLOBAL: CMR2 0x0052ea54
    static unsigned int m_gameRegion;

    // GLOBAL: CMR2 0x00516124
    static char *m_gameRegionStrings[4];

    // GLOBAL: CMR2 0x00817574
    static BYTE m_unk0x00817574;    

    // GLOBAL: CMR2 0x0081a754
    static int m_unk0x0081a754;

    // GLOBAL: CMR2 0x00516184
    static char m_stringCMR[4];

    // GLOBAL: CMR2 0x005250dc
    static char m_stringGameInfoRCF[32];
};

#endif
