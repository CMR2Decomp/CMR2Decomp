#include "Input.h"
#include "main.h"

// GLOBAL: CMR2 0x00511758
const GUID CInput::m_dInputDevice7 = IID_IDirectInput7A;

// GLOBAL: CMR2 0x0059f8c8
IDirectInput7* CInput::m_lpDirectInput7;

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

