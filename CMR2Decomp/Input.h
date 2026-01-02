#ifndef _INPUT_H
#define _INPUT_H

#include "../third_party/dx7sdk-7001/include/dinput.h"

struct DeviceStructMaybe {
    BOOL field_0x0;
    BOOL field_0x4;
    BYTE field_0x8;
    BYTE pad[15];
    BOOL field_0x18;
    BYTE pad2[96];
    char field_0x7c[12]; // device name?
    BYTE pad3[260];
    char field_0x180[12]; // device name again?
    BYTE pad4[716];
    BOOL field_0x464;
    BYTE field_0x468;
    BYTE field_0x469;
    BYTE field_0x46a;
    BYTE field_0x46b;
    BYTE field_0x46c;
    BYTE field_0x46d;
    BYTE field_0x46e;
    BYTE field_0x46f;
    BYTE field_0x470;
    BYTE field_0x471;
    BYTE field_0x472;
    BYTE field_0x473;
    BYTE field_0x474;
    BYTE field_0x475;
    BYTE field_0x476;
    BYTE field_0x477;
    BYTE pad5[148];
};

class CInput {
public:
    static const GUID m_dInputDevice7;
    static IDirectInput7A *m_lpDirectInput7;
    static char m_strKeyboard[12];
    static DeviceStructMaybe m_unk0x0059ce48[2];
    static DWORD m_mouseGranularity;
    static PVOID m_keyboardDelay;
    static PVOID m_keyboardSpeed;
    static REFGUID m_dinputRefGuidKeyboard;
    static REFGUID m_dinputRefGuidMouse;
    static LPDIRECTINPUTDEVICEA m_pOldDirectInputKeyboard;
    static LPDIRECTINPUTDEVICEA m_pDirectInputKeyboard;
    static LPDIRECTINPUTDEVICEA m_pOldDirectInputMouse;
    static LPDIRECTINPUTDEVICEA m_pDirectInputMouse;
    static DIDATAFORMAT m_objectDataFormat;

    static BOOL DInputCreate(void);
    static LPDIRECTINPUTDEVICEA DInputCreateDevice(REFGUID param1, LPDIRECTINPUTDEVICEA *existingDevice);
    static void FUN_0049c0a0(void *param1, void *param2);
    static void FUN_0049fd60(void);
    static BOOL SetupKeyboard(void);
    static void SetupMouse(void);
    static void SetMouseCoopLevel(BOOL param1);
    static BOOL GetAttachedJoysticks(void);
    static BOOL SetupJoystick(LPCDIDEVICEINSTANCEA lpddi, LPVOID pvRef);
};

#endif
