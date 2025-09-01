#include "Game.h"

BOOL CGame::m_shouldExit = FALSE;
BOOL CGame::m_isActive = FALSE;
int CGame::m_unk0x00523c58 = -1;
int CGame::m_unk0x00523c5c = -1;
BYTE CGame::m_unk0x00817da0;
int CGame::m_unk0x0052ea4c;
bool CGame::m_unk0x00817eb0;
BYTE CGame::m_unk0x00817d98;
BYTE CGame::m_unk0x00523c18;

// FUNCTION: CMR2 0x004a9a40
void CGame::SetShouldExit(void)
{
    m_shouldExit = TRUE;
}

// FUNCTION: CMR2 0x004d0780
BOOL CGame::FUN_004d0780(void)
{
    m_unk0x00523c5c = FUN_004057d0();
    if (m_unk0x00523c58 != m_unk0x00523c5c)
        m_unk0x00523c58 = m_unk0x00523c5c;

    switch (m_unk0x00523c5c)
    {
    case 3:
        return FUN_0041b060();

    case 2:
        return FUN_004ff450();

    case 0:
        if (m_unk0x00817eb0)
        {
            FUN_0049c2c0(&m_unk0x00817da0);
            FUN_0049c310(&m_unk0x00817da0);
            FUN_0049c370(&m_unk0x00817da0);
            return FALSE;
        }

        FUN_0049c150(&m_unk0x00817d98, 0, 0xFF);
        FUN_0049c190(&m_unk0x00817da0, 1, &m_unk0x00817d98, InitializeGame, &m_unk0x00523c18);
        m_unk0x00817eb0 = true;
        return FALSE;

    default:
        return FALSE;
    }
}

// FUNCTION: CMR2 0x004057d0
int CGame::FUN_004057d0(void)
{
    return m_unk0x0052ea4c;
}

// STUB: CMR2 0x00523bc8
void CGame::InitializeGame(int p1, int p2) {}

// STUB: CMR2 0x0049c2c0
void __stdcall CGame::FUN_0049c2c0(void *param1) {}
// STUB: CMR2 0x0049c310
void __stdcall CGame::FUN_0049c310(void *param1) {}
// STUB: CMR2 0x0049c370
void __stdcall CGame::FUN_0049c370(void *param1) {}
// STUB: CMR2 0x0049c150
void __stdcall CGame::FUN_0049c150(void *param1, unsigned int param2, unsigned int param3) {}
// STUB: CMR2 0x0049c190
void __stdcall CGame::FUN_0049c190(void *p1, unsigned int p2, LPBYTE p3, void *p4, void *p5) {}
// STUB: CMR2 0x004ff450
BOOL CGame::FUN_004ff450() { return FALSE; }
// STUB: CMR2 0x0041b060
BOOL CGame::FUN_0041b060() { return FALSE; }
