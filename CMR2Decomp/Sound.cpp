#include "Sound.h"

BOOL CSound::m_unk0x005a2728;
BOOL CSound::m_unk0x005a272c;
BOOL CSound::m_unk0x005a2730;
MMIOData *CSound::m_pMMIO;
IDirectSoundBuffer* CSound::m_pDirectSoundBuffer;
HACMSTREAM CSound::m_unk0x00816a7c;
BOOL CSound::m_unk0x005a2720;

// FUNCTION: CMR2 0x004a2ac0
BOOL __fastcall CSound::FUN_004a2ac0(void) {
    MMIOData* pvVar1;

    if (m_unk0x005a2728 != 0) {
        if (m_unk0x005a2730 != 0) {
            FUN_004bd230();
        }

        if (m_unk0x005a272c != 0) {
            StopDirectSoundBuffer();
            if (m_pDirectSoundBuffer != NULL) {
                m_pDirectSoundBuffer->Release();
            }

            m_pDirectSoundBuffer = NULL;
        }

        CloseMMIO(m_pMMIO);

        pvVar1 = m_pMMIO;
        if (m_pMMIO != NULL) {
            CloseAndCleanupMMIO(m_pMMIO);
            delete pvVar1;
        }

        m_pMMIO = NULL;
        m_unk0x005a2728 = FALSE;
        m_unk0x005a272c = FALSE;
        m_unk0x005a2730 = FALSE;
    }

    return TRUE;
}

// FUNCTION: CMR2 0x004bd230
bool CSound::FUN_004bd230(void) {
    return acmStreamClose(m_unk0x00816a7c, 0) == 0;
}

// FUNCTION: CMR2 0x004a2f00
HRESULT CSound::StopDirectSoundBuffer(void) {
    DWORD status;

    if (m_unk0x005a2730 != 0) {
        if (m_pDirectSoundBuffer != NULL) {
            m_pDirectSoundBuffer->GetStatus(&status);
            if ((status & DSBSTATUS_PLAYING) != 0)
                FUN_004a3250(m_pDirectSoundBuffer->Stop());
        }

        m_unk0x005a2720 = FALSE;
    }

    return 0;
}


// FUNCTION: CMR2 0x004a3250
bool CSound::FUN_004a3250(HRESULT param_1) {
    return -1 < param_1;
}

// FUNCTION: CMR2 0x004bd960
MMRESULT __fastcall CSound::CloseMMIO(MMIOData* pMMIOData) {
    mmioClose(pMMIOData->hmmio, 0);
    return 0;
}

// FUNCTION: CMR2 0x004bd8c0
void __fastcall CSound::CloseAndCleanupMMIO(MMIOData* pMMIOData) {
    CloseMMIO(pMMIOData);
    
    if (pMMIOData->pBuffer != NULL) {
        delete pMMIOData->pBuffer;
        pMMIOData->pBuffer = NULL;
    }
}
