#include "Game.h"

BOOL CGame::m_shouldExit = FALSE;
BOOL CGame::m_isActive = FALSE;
int CGame::m_unk0x00523c58 = -1;
int CGame::m_unk0x00523c5c = -1;
Unk0049c2c0 CGame::m_unk0x00817da0;
int CGame::m_unk0x0052ea4c;
bool CGame::m_unk0x00817eb0 = false;
Unk00817d98 CGame::m_unk0x00817d98;
BYTE CGame::m_unk0x00523c18;

FuncTableEntry CGame::m_funcTable[20] = {
    &CGame::InitializeGame,
};

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
        FUN_0049c190(&m_unk0x00817da0, 1, &m_unk0x00817d98, m_funcTable, &m_unk0x00523c18);
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

// STUB: CMR2 0x004d15e0
void CGame::InitializeGame(Unk0049c2c0 *p1, BYTE p2)
{
    return;
}

// FUNCTION: CMR2 0x0049c2c0
void __stdcall CGame::FUN_0049c2c0(Unk0049c2c0 *param1)
{
    FuncTableEntry func;
    BYTE counter;
    BYTE unkIx;

    counter = 0;
    unkIx = 0;
    if (param1->count > 0)
    {
        do
        {
            func = param1->funcLookupTable[param1->unk[unkIx].field0x1 & 0xFF];
            if (func != NULL)
                (func)(param1, unkIx);

            counter++;
            unkIx = counter;
        } while (counter < param1->count);
    }
}

// STUB: CMR2 0x0049c310
void __stdcall CGame::FUN_0049c310(void *param1) {}
// STUB: CMR2 0x0049c370
void __stdcall CGame::FUN_0049c370(void *param1) {}

// FUNCTION: CMR2 0x0049c150
void __stdcall CGame::FUN_0049c150(Unk00817d98 *param1, int param2, int param3)
{
    param1->field0x2 = 0;
    param1->field0x1 =
        (param1->field0x1 >> 8 & 0xfc0000) << 8 | param2 & 0xffU | (param3 & 0xffU) << 8;
}

// FUNCTION: CMR2 0x0049c190
void __stdcall CGame::FUN_0049c190(Unk0049c2c0 *p1, BYTE count, Unk00817d98 *unk, FuncTableEntry *funcLookupTable, void *unk2)
{
    p1->count = count;
    p1->unk = unk;
    p1->funcLookupTable = funcLookupTable;
    p1->unk2 = unk2;
}
// STUB: CMR2 0x004ff450
BOOL CGame::FUN_004ff450() { return FALSE; }
// STUB: CMR2 0x0041b060
BOOL CGame::FUN_0041b060() { return FALSE; }
