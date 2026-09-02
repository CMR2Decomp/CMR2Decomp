#ifndef _GAME_H
#define _GAME_H

#include <windows.h>
#include "../third_party/dx7sdk-7001/include/dplay.h"
#include "../third_party/dx7sdk-7001/include/dplobby.h"

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

struct Unk0x00664750 {
	void* field_0x0;
	void* field_0x4;
	unsigned short field_0x8;
	unsigned short field_0xa;
	void* field_0xc;
    void* field_0x10;
	char field_0x14;
	BYTE field_0x15;
	BYTE field_0x16[254];
};

// GLOBAL: CMR2 0x00511a28
// CLSID_DirectPlay

// GLOBAL: CMR2 0x00511a18
// IID_IDirectPlay4A

// GLOBAL: CMR2 0x00511ae8
// CLSID_DirectPlayLobby

// GLOBAL: CMR2 0x00511ad8
// IID_IDirectPlayLobby3A

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
    static int RegisterCallback(void *param1, void *param2);
    static void FUN_004b7a40(void);
    static void FUN_004a17b0(void);
    static void FUN_004a17f0(bool param1);
    static BOOL FUN_004a1a90(void);
    static void FUN_004aaa10(void);
    static bool Cleanup(void);
    static void DestroyDirectPlay(void);
    static void DestroyDirectPlayLobby(void);
    static IDirectPlay4A *GetDirectPlay(void);
    static bool FUN_004d0a50(bool param1);
    static bool FUN_004aaa40(void);
    static void FUN_0040bab0(BOOL param1);
    static void FUN_004e2e50(void);
    
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

    static void* m_unk0x005939a0;
    static int m_unk0x00593ba0;    

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
    static IDirectPlay4A *m_pDirectPlay4A;

    // GLOBAL: CMR2 0x005a1ea0
    static DPID m_unk0x005a1ea0;

    // GLOBAL: CMR2 0x00665220
    static IDirectPlayLobby3A *m_pDirectPlayLobby3A;

    // GLOBAL: CMR2 0x005a1fb8 
    static void *m_unk0x005a1fb8;    

    // GLOBAL: CMR2 0x005a1fbc
    static BOOL m_unk0x005a1fbc;

    // GLOBAL: CMR2 0x00664750
    static Unk0x00664750 m_unk0x00664750[10];
    
    // GLOBAL: CMR2 0x00665218
    static int m_unk0x00665218;
    
    // GLOBAL: CMR2 0x00532138
    static BOOL m_unk0x00532138;
};

#endif
