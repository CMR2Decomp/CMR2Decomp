#ifndef _GAME_H
#define _GAME_H

#include <windows.h>

typedef void(__stdcall *FuncTableEntry)(struct Unk0049c2c0 *, BYTE);
typedef void(__stdcall *OtherFuncTableEntry)(struct Unk0049c2c0 *, BYTE);

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

class CGame
{
public:
    static void SetShouldExit(void);
    static BOOL FUN_004d0780(void);
    static int FUN_004057d0(void);
    static void __stdcall FUN_0049c2c0(Unk0049c2c0 *param1);
    static void __stdcall FUN_0049c310(Unk0049c2c0 *param1);
    static void __stdcall FUN_0049c370(Unk0049c2c0 *param1);
    static void __stdcall FUN_0049c150(Unk00817d98 *param1, int param2, int param3);
    static void __stdcall FUN_0049c190(Unk0049c2c0 *p1, BYTE count, Unk00817d98 *unk, FuncTableGroup *funcLookupTable, void *unk2);
    static void __stdcall InitializeGame(Unk0049c2c0 *p1, BYTE p2);
    static BOOL FUN_004ff450();
    static BOOL FUN_0041b060();
    static void __stdcall FUN_00501680(struct Unk0049c2c0 *, BYTE);

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
};

#endif
