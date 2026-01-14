#ifndef _INPUT_H
#define _INPUT_H

#include "../third_party/dx7sdk-7001/include/dinput.h"

struct JoystickBinding {
    DWORD range;
    DWORD deadzone;
    DWORD saturation;
    DWORD field_0xc;
    BOOL field_0x10;
};

struct JoystickInfo {
    DWORD controlCount; // or button count?
    DWORD field_0x4;
    JoystickBinding bindings[7];
};

struct KeyboardInfo {
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
};

struct DeviceInfo {
    DWORD field_0x0;
    BOOL field_0x4;
    DWORD field_0x8;
    BYTE pad[6];
    int field_0x14;
    int field_0x18;
    int field_0x1c;
    BYTE pad2[92];
    char deviceInstanceName[MAX_PATH];
    char deviceProductName[MAX_PATH];
    CHAR field_0x284[8][20];
    BYTE pad4[240];
    CHAR field_0x414[20];
    CHAR field_0x425[20];
    CHAR field_0x436[20];
    CHAR field_0x447[20];
    BOOL unk_isJoystick; // not 100% sure on this
    // this makes sense in terms of joystick related stuff
    // but does break matching on SetupKeyboard due to it doing eax + <OFFSET> instead
    // of matching completely to eax + CInput::m_availableDevices[0].field_0x46d
    union {
        KeyboardInfo keyboard;
        JoystickInfo joystick;
    };
    BYTE pad6[16];
};

struct Unk0x0059f8cc {
    BYTE field_0x0;
    BYTE field_0x1;
    BYTE field_0x2;
    BYTE field_0x3;
};

struct ForceFeedbackDevice {
    BOOL field_0x0;              // +0x0 (active flag)
    LPDIRECTINPUTDEVICE7A device; // +0x4
    BYTE field_0x8;              // +0x8 (flag cleared at end)
    BYTE padding1[3];            // +0x9-0xB
    LPDIRECTINPUTEFFECT effects[10];       // +0xC (10 effect pointers)
};

struct ControllerData {
    unsigned int field_0x0;
    unsigned int field_0x4;
    BYTE field_0x8;
    BYTE field_0x9;
    BYTE field_0xa_padding[742];
};

struct ControllerInfo {
    int field_0x0;
    int field_0x4;
    BYTE field_0x8;
    BYTE field_0x9;
    BYTE field_0xa_padding[308];
    BYTE field_0x13e;
    BYTE field_0x13f;
    BYTE field_0x140;
    BYTE field_0x141;
    BYTE field_0x142;
    BYTE field_0x143;
    BYTE field_0x144;
    BYTE field_0x145;
    BYTE field_0x146;
    BYTE pad[4185];
};

class CInput {
public:
    static const GUID m_dInputDevice7;
    static IDirectInput7A *m_lpDirectInput7;
    static Unk0x0059f8cc m_unk0x0059f8cc;
    static char m_strKeyboard[12];
    static DeviceInfo m_availableDevices[8];
    static PVOID m_keyboardDelay;
    static DWORD m_mouseGranularity;
    static PVOID m_keyboardSpeed;
    static REFGUID m_dinputRefGuidKeyboard;
    static REFGUID m_dinputRefGuidMouse;
    static LPDIRECTINPUTDEVICEA m_pOldDirectInputKeyboard;
    static LPDIRECTINPUTDEVICEA m_pDirectInputKeyboard;
    static LPDIRECTINPUTDEVICEA m_pOldDirectInputMouse;
    static LPDIRECTINPUTDEVICEA m_pDirectInputMouse;
    static DIDATAFORMAT m_objectDataFormat;
    static LPDIRECTINPUTDEVICEA m_pDirectInputJoystick;
    static USHORT m_unk0x00511400[8];
    static LPDIRECTINPUTDEVICEA m_unk0x0059f6b0[4];
    static CHAR m_strD[4];
    static CHAR m_strU[4];
    static CHAR m_strR[4];
    static CHAR m_strL[4];
    static ForceFeedbackDevice m_forceFeedbackDevices[8];
    static BOOL m_unk0x00666ee8;
    static int m_unk0x00593ba0;
    static void* m_unk0x005939a0;

    // GLOBAL: CMR2 0x00516908
    static char m_strControllerInfoDir[32];

    // GLOBAL: CMR2 0x005334f0
    static BOOL m_hasLoadedControllerInfo;

    // GLOBAL: CMR2 0x00532250
    static ControllerData m_controllerInfo[6];

    // GLOBAL: CMR2 0x005168f4
    static unsigned short m_unk0x005168f4[8];

    static BOOL DInputCreate(void);
    static LPDIRECTINPUTDEVICEA DInputCreateDevice(REFGUID param1, LPDIRECTINPUTDEVICEA *existingDevice);
    static int FUN_0049c0a0(void *param1, void *param2);
    static BOOL DInputRelease(void);
    static int FUN_0049ef90();
    static BOOL FUN_0049f6b0(LPCDIDEVICEINSTANCEA lpddi, LPVOID pvRef);
    static BOOL SetupKeyboard(void);
    static void SetupMouse(void);
    static void SetMouseCoopLevel(BOOL param1);
    static BOOL GetAttachedJoysticks(void);
    static BOOL SetupJoystick(LPCDIDEVICEINSTANCEA lpddi, LPVOID pvRef);
    static void SetupJoystickDeviceInfo(DeviceInfo *deviceStruct);
    static void SetJoystickAxisRange(int param1, int param2, DWORD range);
    static void SetJoystickAxisDeadzone(int deviceID, int axisID, DWORD deadzone);
    static void SetJoystickAxisSaturation(int deviceID, int axisID, DWORD saturation);
    static BOOL FUN_004aae20(int deviceID, LPDIRECTINPUTDEVICE7 pDevice);
    static bool FUN_004ab5f0(HRESULT hr);
    static void SetForceFeedbackAutocenter(DWORD param1, int deviceID);
    static void ResetForceFeedbackEffects(void);
    static BOOL ResetForceFeedbackEffectsAlt(void);
    static void DInputReleaseDevices(void);
    static void LoadControllerInfo(void);
    static void FUN_0040be90(unsigned int param1);
    static void FUN_0040c440(short param1, ControllerData * param2);
    static void FUN_0049eb90(int param1, unsigned int param2, unsigned int param3);
    static int FUN_0040c530(unsigned int param1);
};

#endif
