#ifndef _FRONTEND_H
#define _FRONTEND_H

#include "GenericFileLoader.h"
#include <windows.h>

// TODO: no idea if this is the right thing to call this
class CFrontend
{
public:
    static void __stdcall FUN_004d21e0(void);
    static BOOL __stdcall FUN_004b7560(unsigned int param_1);
    static BOOL __stdcall FUN_004b7590(unsigned int param_1);
    static BOOL __stdcall FUN_004a9700(void);

    // GLOBAL: CMR2 0x00663b60
    static char m_stringDest[MAX_PATH];

    // GLOBAL: CMR2 0x00523dd0
    static char m_feRes640CountrySpecific[19];
    // GLOBAL: CMR2 0x00523de4
    static char m_feRes640CCountrySpecific[20];
    // GLOBAL: CMR2 0x00523df8
    static char m_feRes1024CountrySpecific[20];
    // GLOBAL: CMR2 0x00523e0c
    static char m_feRes1024CCountrySpecific[21];
    // GLOBAL: CMR2 0x00523e24
    static char m_feRes640[14];
    // GLOBAL: CMR2 0x00523e34
    static char m_feRes640C[15];
    // GLOBAL: CMR2 0x00523e44
    static char m_feRes1024[15];
    // GLOBAL: CMR2 0x00523e54
    static char m_feRes1024C[16];

    // unknowns
    // GLOBAL: CMR2 0x00818260;
    static GenericFile m_unk0x00818260;
    // GLOBAL: CMR2 0x006e0c5c
    static unsigned int m_unk0x006e0c5c;
    // GLOBAL: CMR2 0x006e0c64
    static unsigned int m_unk0x006e0c64;
    // GLOBAL: CMR2 0x006e0c60
    static unsigned int m_unk0x006e0c60;
    // GLOBAL: CMR2 0x006e0c68
    static unsigned int m_unk0x006e0c68;
    // GLOBAL: CMR2 0x00663b38
    static unsigned int m_unk0x00663b38;
    // GLOBAL: CMR2 0x00663b48
    static unsigned int m_unk0x00663b48;
};

#endif
