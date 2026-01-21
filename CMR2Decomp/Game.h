#ifndef _GAME_H
#define _GAME_H

#include <windows.h>
#include "../third_party/dx7sdk-7001/include/dplay.h"

typedef void (*FuncTableEntry)(struct Unk0049c2c0 *, BYTE);
typedef void (*OtherFuncTableEntry)(struct Unk0049c2c0 *, BYTE);

struct Unk00817d98
{
    int field0x1;
    int field0x2;
};

struct FuncTableGroup
{
    FuncTableEntry func1;
    OtherFuncTableEntry func2;
};

struct Unk0049c2c0
{
    BYTE count;
    BYTE pad[3];                     // is this meant to be something?
    Unk00817d98 *unk;                // pointer to an 8 byte struct?
    FuncTableGroup *funcLookupTable; // pointer to the function table which points to functions like initializegame
    void *unk2;                      // pointer to something that is 64 bytes?
};

struct Unk0x005a1820 {
    char field_0x0[100];
    char field_0x64[100];
    unsigned int field_0xc8;
    unsigned int field_0xcc;
};

class CGame
{
public:
    static void SetShouldExit(void);
    static BOOL FUN_004d0780(void);
    static int FUN_004057d0(void);
    static void FUN_0049c2c0(Unk0049c2c0 *param1);
    static void FUN_0049c310(Unk0049c2c0 *param1);
    static void FUN_0049c370(Unk0049c2c0 *param1);
    static void FUN_0049c150(Unk00817d98 *param1, int param2, int param3);
    static void FUN_0049c190(Unk0049c2c0 *p1, BYTE count, Unk00817d98 *unk, FuncTableGroup *funcLookupTable, void *unk2);
    static void InitializeGame(Unk0049c2c0 *p1, BYTE p2);
    static BOOL FUN_004ff450();
    static BOOL FUN_0041b060();
    static void FUN_00501680(struct Unk0049c2c0 *, BYTE);
    static BYTE FUN_004ea880(void);
    static void FUN_004083e0(BYTE param1);
    static void FUN_00406810(BYTE param1);
    static bool FUN_004067e0(void);
    static void FUN_004b7a40(void);
    static void FUN_004a17b0(void);
    static void FUN_004a17f0(bool param1);
    static BOOL FUN_004a1a90(void);
    static void FUN_004aaa10(void);
    static bool FUN_004aaac0(void);
    static void FUN_004aab40(void);
    static void FUN_004aabb0(void);
    static IDirectPlay4A *FUN_004aad40(void);
    
    // GLOBAL: CMR2 0x00663db8
    static BOOL m_shouldExit;
    // GLOBAL: CMR2 0x00663db4
    static BOOL m_isActive;
    // GLOBAL: CMR2 0x00523c58
    static int m_unk0x00523c58;
    // GLOBAL: CMR2 0x00523c5c
    static int m_unk0x00523c5c;
    // GLOBAL: CMR2 0x0052ea4c
    static int m_unk0x0052ea4c;
    // GLOBAL: CMR2 0x00817eb0
    static bool m_unk0x00817eb0;
    // GLOBAL: CMR2 0x00817da0
    static Unk0049c2c0 m_unk0x00817da0;
    // GLOBAL: CMR2 0x00817d98
    static Unk00817d98 m_unk0x00817d98;
    // GLOBAL: CMR2 0x00523c18
    static BYTE m_unk0x00523c18;
    // GLOBAL: CMR2 0x00593cac
    static BYTE m_unk0x00593cac;

    // GLOBAL: CMR2 0x00593ba4
    static Unk00817d98 *m_unk0x00593ba4;
    // GLOBAL: CMR2 0x00593ba8
    static BYTE m_unk0x00593ba8;

    // GLOBAL: CMR2 0x00523bc8
    static FuncTableGroup m_initializeGameGroupedFuncTable[10];

    // GLOBAL: CMR2 0x00523d68
    static BYTE m_unk0x00523d68;
    // GLOBAL: CMR2 0x008180f9
    static BYTE m_unk0x008180f9;
    // GLOBAL: CMR2 0x008180fc
    static BYTE m_unk0x008180fc;
    // GLOBAL: CMR2 0x00516120
    static BYTE m_unk0x00516120;
    // GLOBAL: CMR2 0x00531768
    static BYTE m_unk0x00531768;
    // GLOBAL: CMR2 0x0052ea58
    static BYTE m_unk0x0052ea58;
    // GLOBAL: CMR2 0x0052ea59
    static BYTE m_unk0x0052ea59;

    // GLOBAL: CMR2 0x005a1818
    static BYTE m_unk0x005a1818;

    // GLOBAL: CMR2 0x005a1819
    static BYTE m_unk0x005a1819;

    // GLOBAL: CMR2 0x005a1820
    static Unk0x005a1820 m_unk0x005a1820[7];
    
    // GLOBAL: CMR2 0x005a1e34
    static int m_unk0x005a1e34;

    // GLOBAL: CMR2 0x005a1fc0
    static bool m_unk0x005a1fc0;

    // GLOBAL: CMR2 0x0066521c
    static IDirectPlay4A *m_unk0x0066521c;

    // GLOBAL: CMR2 0x005a1ea0
    static DPID m_unk0x005a1ea0;

    // GLOBAL: CMR2 0x00511a28
    static CLSID m_clsidDirectPlay;

    // GLOBAL: CMR2 0x00511a18
    static IID m_iidDirectPlay4A;
};

#endif
