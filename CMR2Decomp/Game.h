#ifndef _GAME_H
#define _GAME_H

#include <windows.h>

class CGame
{
public:
    static void SetShouldExit(void);
    static BOOL FUN_004d0780(void);
    static int FUN_004057d0(void);
    static void __stdcall FUN_0049c2c0(void *param1);
    static void __stdcall FUN_0049c310(void *param1);
    static void __stdcall FUN_0049c370(void *param1);
    static void __stdcall FUN_0049c150(void *param1, unsigned int param2, unsigned int param3);
    static void __stdcall FUN_0049c190(void *p1, unsigned int p2, LPBYTE p3, void *p4, void *p5);
    static void InitializeGame(int p1, int p2);
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
    static BYTE m_unk0x00817da0;
    // GLOBAL: CMR2 0x00817d98
    static BYTE m_unk0x00817d98;
    // GLOBAL: CMR2 0x00523c18
    static BYTE m_unk0x00523c18;
};

#endif
