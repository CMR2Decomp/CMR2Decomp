#include "Input.h"
#include "GameInfo.h"
#include "main.h"

#include <stdio.h>

// GLOBAL: CMR2 0x00511758
const GUID CInput::m_dInputDevice7 = IID_IDirectInput7A;

// GLOBAL: CMR2 0x0059f8c8
IDirectInput7* CInput::m_lpDirectInput7;

// GLOBAL: CMR2 0x00520874
char CInput::m_strKeyboard[12] = "Keyboard";

// GLOBAL: CMR2 0x0059ce48
DeviceStructMaybe CInput::m_unk0x0059ce48[2];

// GLOBAL: CMR2 0x0059f8d8
PVOID CInput::m_keyboardDelay;

// GLOBAL: CMR2 0x0059f8dc
PVOID CInput::m_keyboardSpeed;

// FUNCTION: CMR2 0x0049fd30
BOOL CInput::CreateDInput(void) {
    DirectInputCreateEx(CMain::m_hInstance, 0x700, m_dInputDevice7, (LPVOID*)&CInput::m_lpDirectInput7, NULL);
    FUN_0049c0a0(FUN_0049fd60, NULL);
    return TRUE;
}

// STUB: CMR2 0x0049c0a0
void CInput::FUN_0049c0a0(void *param1, void *param2) {
    return;
}

// release?
// STUB: CMR2 0x0049fd60
void CInput::FUN_0049fd60(void) {};

// FUNCTION: CMR2 0x0049f0e0
void CInput::FUN_0049f0e0(void) {
    unsigned int uVar1;
    BOOL bVar2;
    int iVar3 = 0;

    do {
        uVar1 = CGameInfo::m_unk0x0059f8cc & 0xff;
        m_unk0x0059ce48[uVar1].field_0x0 = TRUE;
        m_unk0x0059ce48[uVar1].field_0x18 = FALSE;

        sprintf(m_unk0x0059ce48[uVar1].field_0x7c, m_strKeyboard);
        sprintf(m_unk0x0059ce48[CGameInfo::m_unk0x0059f8cc & 0xff].field_0x180, m_strKeyboard);
        
        uVar1 = CGameInfo::m_unk0x0059f8cc & 0xff;
        m_unk0x0059ce48[uVar1].field_0x464 = FALSE;

        if (!iVar3) {
            m_unk0x0059ce48[uVar1].field_0x468 = 0xcb;
            m_unk0x0059ce48[uVar1].field_0x469 = 0xcd;
            m_unk0x0059ce48[uVar1].field_0x46a = 200;
            m_unk0x0059ce48[uVar1].field_0x46b = 0xd0;
            m_unk0x0059ce48[uVar1].field_0x46c = 0x39;
            m_unk0x0059ce48[uVar1].field_0x46d = 0x1b;
            m_unk0x0059ce48[uVar1].field_0x46e = 0x1a;
            m_unk0x0059ce48[uVar1].field_0x46f = 0x2e;
            m_unk0x0059ce48[uVar1].field_0x470 = 0x13;
        } else {
            m_unk0x0059ce48[uVar1].field_0x468 = 0x4b;
            m_unk0x0059ce48[uVar1].field_0x469 = 0x4d;
            m_unk0x0059ce48[uVar1].field_0x46a = 0x48;
            m_unk0x0059ce48[uVar1].field_0x46b = 0x50;
            m_unk0x0059ce48[uVar1].field_0x46c = 0x51;
            m_unk0x0059ce48[uVar1].field_0x46d = 0xc9;
            m_unk0x0059ce48[uVar1].field_0x46e = 0xd1;
            m_unk0x0059ce48[uVar1].field_0x46f = 0x49;
            m_unk0x0059ce48[uVar1].field_0x470 = 0x47;            
        }

        m_unk0x0059ce48[uVar1].field_0x471 = 0x0;
        m_unk0x0059ce48[uVar1].field_0x474 = 0x3b;
        m_unk0x0059ce48[uVar1].field_0x475 = 0x3c;
        m_unk0x0059ce48[uVar1].field_0x476 = 0x3e;
        m_unk0x0059ce48[uVar1].field_0x477 = 0x0;
        m_unk0x0059ce48[uVar1].field_0x472 = 0x1;
        m_unk0x0059ce48[uVar1].field_0x473 = 0x0;

        *(BYTE*)&CGameInfo::m_unk0x0059f8cc += 1;  // Directly increment the low byte
        iVar3++;
    } while (iVar3 < 2);

    bVar2 = SystemParametersInfoA(SPI_GETKEYBOARDDELAY, 0, &m_keyboardDelay, 0);
    if (!bVar2) m_keyboardDelay = (PVOID)0x3e8;
    else {
        switch ((int)m_keyboardDelay) {
            case 0:
                m_keyboardDelay = (PVOID)0x1f4;
            break;

            case 1:
                m_keyboardDelay = (PVOID)0x2ee;
            break;

            case 2:
                m_keyboardDelay = (PVOID)0x3e8;
            break;

            case 3:
                m_keyboardDelay = (PVOID)0x4e2;
            break;
        }
    }

    bVar2 = SystemParametersInfoA(SPI_GETKEYBOARDSPEED, 0, &m_keyboardSpeed, 0);
    if (!bVar2) m_keyboardSpeed = (PVOID)0x1f4;
    else m_keyboardSpeed = (PVOID)(503 - ((BYTE)m_keyboardSpeed * 13));
}

