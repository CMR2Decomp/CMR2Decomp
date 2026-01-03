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

// GLOBAL: CMR2 0x0059f8cc
unsigned int CInput::m_unk0x0059f8cc; // device count or something

// GLOBAL: CMR2 0x0059ce48
DeviceInfo CInput::m_availableDevices[2];

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

// GLOBAL: CMR2 0x00512ea0
LPDIRECTINPUTDEVICEA CInput::m_pDirectInputJoystick;

// GLOBAL: CMR2 0x00511400
USHORT CInput::m_unk0x00511400[8];

// GLOBAL: CMR2 0x0059f6b0
LPDIRECTINPUTDEVICEA CInput::m_unk0x0059f6b0[4];

// GLOBAL: CMR2 0x00520880
CHAR CInput::m_strD[4] = " D";
// GLOBAL: CMR2 0x00520884
CHAR CInput::m_strU[4] = " U";
// GLOBAL: CMR2 0x00520888
CHAR CInput::m_strR[4] = " R";
// GLOBAL: CMR2 0x0052088C
CHAR CInput::m_strL[4] = " L";

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
        uVar1 = m_unk0x0059f8cc & 0xff;
        m_availableDevices[uVar1].field_0x0 = 1;
        m_availableDevices[uVar1].field_0x18 = FALSE;

        sprintf(m_availableDevices[uVar1].deviceInstanceName, m_strKeyboard);
        sprintf(m_availableDevices[m_unk0x0059f8cc & 0xff].deviceProductName, m_strKeyboard);
        
        uVar1 = m_unk0x0059f8cc & 0xff;
        m_availableDevices[uVar1].unk_isJoystick = FALSE;

        if (!iVar3) {
            m_availableDevices[uVar1].keyboard.field_0x468 = 0xcb;
            m_availableDevices[uVar1].keyboard.field_0x469 = 0xcd;
            m_availableDevices[uVar1].keyboard.field_0x46a = 0xc8;
            m_availableDevices[uVar1].keyboard.field_0x46b = 0xd0;
            m_availableDevices[uVar1].keyboard.field_0x46c = 0x39;
            m_availableDevices[uVar1].keyboard.field_0x46d = 0x1b;
            m_availableDevices[uVar1].keyboard.field_0x46e = 0x1a;
            m_availableDevices[uVar1].keyboard.field_0x46f = 0x2e;
            m_availableDevices[uVar1].keyboard.field_0x470 = 0x13;
        } else {
            m_availableDevices[uVar1].keyboard.field_0x468 = 0x4b;
            m_availableDevices[uVar1].keyboard.field_0x469 = 0x4d;
            m_availableDevices[uVar1].keyboard.field_0x46a = 0x48;
            m_availableDevices[uVar1].keyboard.field_0x46b = 0x50;
            m_availableDevices[uVar1].keyboard.field_0x46c = 0x51;
            m_availableDevices[uVar1].keyboard.field_0x46d = 0xc9;
            m_availableDevices[uVar1].keyboard.field_0x46e = 0xd1;
            m_availableDevices[uVar1].keyboard.field_0x46f = 0x49;
            m_availableDevices[uVar1].keyboard.field_0x470 = 0x47;            
        }

        m_availableDevices[uVar1].keyboard.field_0x471 = 0x0;
        m_availableDevices[uVar1].keyboard.field_0x474 = 0x3b;
        m_availableDevices[uVar1].keyboard.field_0x475 = 0x3c;
        m_availableDevices[uVar1].keyboard.field_0x476 = 0x3e;
        m_availableDevices[uVar1].keyboard.field_0x477 = 0x0;
        m_availableDevices[uVar1].keyboard.field_0x472 = 0x1;
        m_availableDevices[uVar1].keyboard.field_0x473 = 0x0;

        *(BYTE*)&m_unk0x0059f8cc += 1;  // Directly increment the low byte
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

// FUNCTION: CMR2 0x0049f690
BOOL CInput::GetAttachedJoysticks(void) {
    HRESULT hr;
    hr = m_lpDirectInput7->EnumDevices(DIDEVTYPE_JOYSTICK, SetupJoystick, m_lpDirectInput7, DIEDFL_ATTACHEDONLY);
    return SUCCEEDED(hr);
}

// FUNCTION: CMR2 0x0049f6d0
BOOL CInput::SetupJoystick(LPCDIDEVICEINSTANCEA lpddi, LPVOID pvRef) {
    HRESULT hr;
    unsigned int uVar2;
    DeviceInfo *pDeviceInfo;
    LPDIRECTINPUTDEVICEA pDevice;
    BYTE iVar6[4];
    int iVar10, axisID, iVar11;
    JoystickBinding * joystickBinding;
    DIPROPDWORD dipd;
    DIDEVCAPS devCaps;
    DIDEVICEOBJECTINSTANCEA didoi;

    uVar2 = m_unk0x0059f8cc & 0xff;
    pDeviceInfo = &m_availableDevices[m_unk0x0059f8cc & 0xff];
    if (GET_DIDEVICE_TYPE(lpddi->dwDevType) == DIDEVTYPE_JOYSTICK) {
        if (GET_DIDEVICE_SUBTYPE(lpddi->dwDevType) == DIDEVTYPE_MOUSE) pDeviceInfo->field_0x0 = 0;
        else pDeviceInfo->field_0x0 = 3;
    
        pDevice = DInputCreateDevice(lpddi->guidInstance, &m_pDirectInputJoystick);
        m_unk0x0059f6b0[m_unk0x0059f8cc >> 0x10 & 0xff] = pDevice;

        if (pDevice != NULL) {
            strncpy(m_availableDevices[uVar2].deviceInstanceName, lpddi->tszInstanceName, sizeof(m_availableDevices[uVar2].deviceInstanceName));
            strncpy(m_availableDevices[uVar2].deviceProductName, lpddi->tszProductName, sizeof(m_availableDevices[uVar2].deviceProductName));
        
            pDeviceInfo->field_0x18 = m_unk0x0059f8cc >> 0x10 & 0xFF;

            SetupJoystickDeviceInfo(pDeviceInfo);

            iVar10 = 0;
            axisID = 0;

            if (pDeviceInfo->joystick.controlCount > 0) {
                joystickBinding = pDeviceInfo->joystick.bindings;
                do {
                    if (joystickBinding[-1].field_0x10 != FALSE) {
                        SetJoystickAxisRange(m_unk0x0059f8cc & 0xff, axisID, joystickBinding->range);
                        SetJoystickAxisDeadzone(m_unk0x0059f8cc & 0xff, axisID, joystickBinding->deadzone);
                        SetJoystickAxisSaturation(m_unk0x0059f8cc & 0xff, axisID, joystickBinding->saturation);
                        iVar10++;
                    }

                    axisID++;
                    joystickBinding ++;
                } while (axisID < pDeviceInfo->field_0x8);
            }

            devCaps.dwSize = 0x2c;
            hr = m_unk0x0059f6b0[m_unk0x0059f8cc >> 0x10 & 0xff]->GetCapabilities(&devCaps);
            
            if (SUCCEEDED(hr)) {
                if ((devCaps.dwFlags & DIDC_FORCEFEEDBACK)) {
                    m_availableDevices[m_unk0x0059f8cc >> 0x10 & 0xff].unk_isJoystick = TRUE;
                    
                    dipd.diph.dwSize = 0x14;
                    dipd.diph.dwHeaderSize = 0x10;
                    dipd.diph.dwHow = DIPH_DEVICE;
                    dipd.dwData = 0;

                    m_unk0x0059f6b0[m_unk0x0059f8cc >> 0x10 & 0xFF]->SetProperty(DIPROP_AUTOCENTER, &dipd.diph);
                    FUN_004aae20(m_unk0x0059f8cc & 0xff, m_unk0x0059f6b0[m_unk0x0059f8cc >> 0x10 & 0xff]);

                } else {
                    m_availableDevices[m_unk0x0059f8cc >> 0x10 & 0xff].unk_isJoystick = FALSE;
                }

                iVar10 = 0;
                didoi.dwSize = 0x13c;
                m_availableDevices[uVar2].field_0x14 = 0;

                if (devCaps.dwAxes > 0) {
                    
                    do {
                        hr = m_unk0x0059f6b0[m_unk0x0059f8cc >> 0x10 & 0xFF]->GetObjectInfo(&didoi, iVar10 + 0x30, DIPH_BYOFFSET);
                        
                        if (SUCCEEDED(hr)) {
                            strncpy(m_availableDevices[uVar2].field_0x284[iVar10], didoi.tszName, 20);
                            m_availableDevices[uVar2].field_0x14++;
                        }
                        iVar10++;
                    } while (iVar10 < devCaps.dwAxes);
                }

                if (devCaps.dwAxes > 0) {
                    iVar10 = 0;
                    iVar11 = 0x20;

                    do {
                        if (iVar11 > 0x20) break;
                        hr = m_unk0x0059f6b0[m_unk0x0059f8cc >> 0x10 & 0xFF]->GetObjectInfo(&didoi, iVar11, DIPH_BYOFFSET);
                        
                        if (SUCCEEDED(hr)) {
                            strncpy(m_availableDevices[uVar2].field_0x414, didoi.tszName, 0x11);
                            strcat(m_availableDevices[uVar2].field_0x414, m_strL);
                            
                            strncpy(m_availableDevices[uVar2].field_0x425, didoi.tszName, 0x11);
                            strcat(m_availableDevices[uVar2].field_0x425, m_strR);
                            
                            strncpy(m_availableDevices[uVar2].field_0x436, didoi.tszName, 0x11);
                            strcat(m_availableDevices[uVar2].field_0x436, m_strU);
                            
                            strncpy(m_availableDevices[uVar2].field_0x447, didoi.tszName, 0x11);
                            strcat(m_availableDevices[uVar2].field_0x447, m_strD);

                            m_availableDevices[uVar2].field_0x14++;
                        }
                        iVar10++;
                        iVar11 += 4;
                    } while (iVar10 < devCaps.dwAxes);
                }

                iVar10 = 0;

                if (m_availableDevices[uVar2].field_0x14 > 0) {
                    DWORD * unk_0x1c = &m_availableDevices[uVar2].field_0x1c;
                    do {
                        BYTE bVar6 = iVar10;
                        iVar10 ++;
                        *unk_0x1c = 1 << (bVar6 & 0xFF);
                        unk_0x1c++;
                    } while ((int)unk_0x1c < (int)&m_availableDevices[uVar2].field_0x14);
                }
            }
        }
    }

    return DIENUM_CONTINUE;
}

// FUNCTION: CMR2 0x0049fad0
void CInput::SetupJoystickDeviceInfo(DeviceInfo *deviceInfo) {
    HRESULT hr;
    USHORT * unk0x00511400;
    JoystickBinding * bindings;

    DIPROPDWORD dipd;
    dipd.diph.dwSize = 0x18;
    dipd.diph.dwHeaderSize = 0x10;
    dipd.diph.dwHow = DIPH_BYOFFSET;

    deviceInfo->joystick.controlCount = 0;
    unk0x00511400 = m_unk0x00511400;
    bindings = deviceInfo->joystick.bindings;

    do {
        dipd.diph.dwObj = *unk0x00511400;
        hr = m_unk0x0059f6b0[deviceInfo->field_0x18]->GetProperty(DIPROP_RANGE, &dipd.diph);

        if (SUCCEEDED(hr)) {
            bindings[-1].field_0x10 = TRUE; // esentially just deviceInfo->unk_isJoystick but it doesnt match
            bindings->deadzone = 0xc8;
            bindings->range = 0x10000;
            bindings->saturation = 0x2710;

            deviceInfo->joystick.controlCount ++;
        }
        else {
            bindings[-1].field_0x10 = FALSE;
        }

        unk0x00511400++;
        bindings++;
    } while ((int)unk0x00511400 < (int)(m_unk0x00511400 + 16));
}

// FUNCTION: CMR2 0x0049ee10
void CInput::SetJoystickAxisRange(int deviceID, int axisID, DWORD range) {
    USHORT * unk0x00511400;
    DeviceInfo * pDeviceInfo = &m_availableDevices[deviceID];

    DIPROPRANGE dipd;
    dipd.diph.dwSize = 0x18;
    dipd.diph.dwHeaderSize = 0x10;
    dipd.diph.dwHow = DIPH_BYOFFSET;
    dipd.lMax = range;
    dipd.lMin = -range;
    dipd.diph.dwObj = m_unk0x00511400[axisID];

    m_unk0x0059f6b0[pDeviceInfo->field_0x18]->SetProperty(DIPROP_RANGE, &dipd.diph);
    pDeviceInfo->joystick.bindings[axisID].range = range;
}

// FUNCTION: CMR2 0x0049ee90
void CInput::SetJoystickAxisDeadzone(int deviceID, int axisID, DWORD deadzone) {
    USHORT * unk0x00511400;
    DeviceInfo * pDeviceInfo = &m_availableDevices[deviceID];

    DIPROPDWORD dipd;
    dipd.diph.dwSize = 0x14;
    dipd.diph.dwHeaderSize = 0x10;
    dipd.diph.dwHow = DIPH_BYOFFSET;
    dipd.dwData = deadzone;
    dipd.diph.dwObj = m_unk0x00511400[axisID];

    m_unk0x0059f6b0[pDeviceInfo->field_0x18]->SetProperty(DIPROP_DEADZONE, &dipd.diph);
    pDeviceInfo->joystick.bindings[axisID].deadzone = deadzone;
}

// FUNCTION: CMR2 0x0049ef10
void CInput::SetJoystickAxisSaturation(int deviceID, int axisID, DWORD saturation) {
    USHORT * unk0x00511400;
    DeviceInfo * pDeviceInfo = &m_availableDevices[deviceID];

    DIPROPDWORD dipd;
    dipd.diph.dwSize = 0x14;
    dipd.diph.dwHeaderSize = 0x10;
    dipd.diph.dwHow = DIPH_BYOFFSET;
    dipd.dwData = saturation;
    dipd.diph.dwObj = m_unk0x00511400[axisID];

    m_unk0x0059f6b0[pDeviceInfo->field_0x18]->SetProperty(DIPROP_SATURATION, &dipd.diph);
    pDeviceInfo->joystick.bindings[axisID].saturation = saturation;
}

// STUB: CMR2 0x004aae20
BOOL CInput::FUN_004aae20(int deviceID, LPDIRECTINPUTDEVICEA pDevice) {
    return TRUE;
}