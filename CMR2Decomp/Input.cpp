#include "Input.h"
#include "GameInfo.h"
#include "Graphics.h"
#include "main.h"

#include <stdio.h>

// GLOBAL: CMR2 0x00511758
const GUID CInput::m_dInputDevice7 = IID_IDirectInput7A;

// GLOBAL: CMR2 0x0059f8c8
IDirectInput7A* CInput::m_lpDirectInput7;

// GLOBAL: CMR2 0x00520874
char CInput::m_strKeyboard[12] = "Keyboard";

// GLOBAL: CMR2 0x0059ce48
DeviceStructMaybe CInput::m_unk0x0059ce48[2];

// GLOBAL: CMR2 0x0059f8d4
DWORD CInput::m_mouseGranularity;

// GLOBAL: CMR2 0x0059f8d8
PVOID CInput::m_keyboardDelay;

// GLOBAL: CMR2 0x0059f8dc
PVOID CInput::m_keyboardSpeed;

// GLOBAL: CMR2 0x00511898
REFGUID CInput::m_dinputRefGuidMouse = GUID_SysMouse;

// GLOBAL: CMR2 0x005118a8
REFGUID CInput::m_dinputRefGuidKeyboard = GUID_SysKeyboard;

// GLOBAL: CMR2 0x00512e88
LPDIRECTINPUTDEVICEA CInput::m_pOldDirectInputKeyboard;

// GLOBAL: CMR2 0x00512e70
LPDIRECTINPUTDEVICEA CInput::m_pOldDirectInputMouse;

// GLOBAL: CMR2 0x005117c8
DIDATAFORMAT CInput::m_objectDataFormat;

// GLOBAL: CMR2 0x0059f6a8
LPDIRECTINPUTDEVICEA CInput::m_pDirectInputKeyboard;
// GLOBAL: CMR2 0x0059f7c4
LPDIRECTINPUTDEVICEA CInput::m_pDirectInputMouse;

// FUNCTION: CMR2 0x0049fd30
BOOL CInput::DInputCreate(void) {
    DirectInputCreateEx(CMain::m_hInstance, 0x700, m_dInputDevice7, (LPVOID*)&CInput::m_lpDirectInput7, NULL);
    FUN_0049c0a0(FUN_0049fd60, NULL);
    return TRUE;
}

// FUNCTION: CMR2 0x0049fe30
LPDIRECTINPUTDEVICEA CInput::DInputCreateDevice(REFGUID guid, LPDIRECTINPUTDEVICEA *previousDevice) {
    LPDIRECTINPUTDEVICEA pDevice = NULL;
    HRESULT h1, h2, h3, h4;
    
    h1 = m_lpDirectInput7->CreateDevice(guid, &pDevice, NULL);
    if (SUCCEEDED(h1)) {
        h2 = pDevice->SetDataFormat(&m_objectDataFormat);
        
        // release old device if it has one
        if (previousDevice != NULL) {
            // TODO: there seems to be an entire block missing here that sets the pointer to NULL?
            (*previousDevice)->Release();
        }
      
        if (SUCCEEDED(h2)) {
            h3 = pDevice->Acquire();
            if (FAILED(h3)) {
                if (pDevice != NULL) pDevice->Release();
                return NULL;
            }
            
            if (IsEqualGUID(guid, m_dinputRefGuidKeyboard)) {
                h4 = pDevice->SetCooperativeLevel(CMain::m_hWndList[CMain::m_hWndIx], DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);  // 10
            } else if (IsEqualGUID(guid, m_dinputRefGuidMouse)) {
                if (g_pGraphics->isFullscreen) {
                    h4 = pDevice->SetCooperativeLevel(CMain::m_hWndList[CMain::m_hWndIx], DISCL_EXCLUSIVE | DISCL_FOREGROUND);  // 5
                } else {
                    h4 = pDevice->SetCooperativeLevel(CMain::m_hWndList[CMain::m_hWndIx], DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);  // 6
                }
            } else {
                h4 = pDevice->SetCooperativeLevel(CMain::m_hWndList[CMain::m_hWndIx], 9);
            }
            
            // if we got a cooplevel success, return it
            if (FAILED(h4)) {
                if (pDevice != NULL) pDevice->Release();
                return NULL;
            }

            return pDevice;
        }
    }
    return NULL;
}

// STUB: CMR2 0x0049c0a0
void CInput::FUN_0049c0a0(void *param1, void *param2) {
    return;
}

// release?
// STUB: CMR2 0x0049fd60
void CInput::FUN_0049fd60(void) {};

// FUNCTION: CMR2 0x0049f0e0
BOOL CInput::SetupKeyboard(void) {
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

    m_pDirectInputKeyboard = DInputCreateDevice(m_dinputRefGuidKeyboard, &m_pOldDirectInputKeyboard);
    if (m_pDirectInputKeyboard != NULL)
        return TRUE;

    return FALSE;
}

// FUNCTION: CMR2 0x0049f060
void CInput::SetupMouse(void) {
    HRESULT hr;
    DIPROPDWORD diPropDword;
    m_pDirectInputMouse = DInputCreateDevice(m_dinputRefGuidMouse, &m_pOldDirectInputMouse);

    diPropDword.diph.dwSize = 0x14;
    diPropDword.diph.dwHeaderSize = 0x10;
    diPropDword.diph.dwObj = 0;
    diPropDword.diph.dwHow = 0;
    diPropDword.dwData = 0x10;

    m_pDirectInputMouse->SetProperty(DIPROP_BUFFERSIZE, &diPropDword.diph);
    m_pDirectInputMouse->Acquire();
    hr = m_pDirectInputMouse->GetProperty(DIPROP_GRANULARITY, &diPropDword.diph);
    if (SUCCEEDED(hr)) {
        m_mouseGranularity = diPropDword.dwData;
    }

    SetMouseCoopLevel(1);
}

// FUNCTION: CMR2 0x0049f000
void CInput::SetMouseCoopLevel(BOOL param1) {
    if (m_pDirectInputMouse != NULL) {
        m_pDirectInputMouse->Unacquire();

        if (param1 && g_pGraphics->isFullscreen) {
            m_pDirectInputMouse->SetCooperativeLevel(CMain::m_hWndList[CMain::m_hWndIx],DISCL_EXCLUSIVE | DISCL_FOREGROUND); // 5
        } else {
            m_pDirectInputMouse->SetCooperativeLevel(CMain::m_hWndList[CMain::m_hWndIx], DISCL_NONEXCLUSIVE | DISCL_FOREGROUND); // 6
        }

        m_pDirectInputMouse->Acquire();
    }
}

