#ifndef _GAME_H
#define _GAME_H

#include <windows.h>

typedef void (*FuncTableEntry)(struct Unk0049c2c0 *, BYTE);

struct Unk00817d98
{
    int field0x1;
    int field0x2;
};

struct Unk0049c2c0
{
    BYTE count;
    BYTE pad[3];                     // is this meant to be something?
    Unk00817d98 *unk;                // pointer to an 8 byte struct?
    FuncTableEntry *funcLookupTable; // pointer to the function table which points to functions like initializegame
    void *unk2;                      // pointer to something that is 64 bytes?
};

class CGame
{
public:
    static void SetShouldExit(void);
    static BOOL FUN_004d0780(void);
    static int FUN_004057d0(void);
    static void __stdcall FUN_0049c2c0(Unk0049c2c0 *param1);
    static void __stdcall FUN_0049c310(void *param1);
    static void __stdcall FUN_0049c370(void *param1);
    static void __stdcall FUN_0049c150(Unk00817d98 *param1, int param2, int param3);
    static void __stdcall FUN_0049c190(Unk0049c2c0 *p1, BYTE count, Unk00817d98 *unk, FuncTableEntry *funcLookupTable, void *unk2);
    static void InitializeGame(Unk0049c2c0 *p1, BYTE p2);
    static BOOL FUN_004ff450();
    static BOOL FUN_0041b060();

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
    // GLOBAL: CMR2 0x00523bc8
    static FuncTableEntry m_funcTable[20];
};

#endif
