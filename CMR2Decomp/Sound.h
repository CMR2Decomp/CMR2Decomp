#ifndef _SOUND_H
#define _SOUND_H

#include <windows.h>
#include <MMREG.H>
#include <MMSYSTEM.H>
#include <MSACM.H>
#include <DSOUND.H>

struct MMIOData {
    void* pBuffer;    // Offset 0x0
    HMMIO hmmio;      // Offset 0x4
};


class CSound {
public:
    static BOOL __fastcall FUN_004a2ac0(void);
    static bool FUN_004bd230(void);
    static HRESULT StopDirectSoundBuffer(void);
    static bool FUN_004a3250(HRESULT param1);
    static MMRESULT __fastcall CloseMMIO(MMIOData* hhmio);
    static void __fastcall CloseAndCleanupMMIO(MMIOData* pMMIO);

    // GLOBAL: CMR2 0x005a23e8
    static MMIOData *m_pMMIO;

    // GLOBAL: CMR2 0x005a2720
    static BOOL m_unk0x005a2720;

    // GLOBAL: CMR2 0x005a2728
    static BOOL m_unk0x005a2728;

    // GLOBAL: CMR2 0x005a272c
    static BOOL m_unk0x005a272c;

    // GLOBAL: CMR2 0x005a2730
    static BOOL m_unk0x005a2730;

    // GLOBAL: CMR2 0x005a2854
    static IDirectSoundBuffer* m_pDirectSoundBuffer;

    // GLOBAL: CMR2 0x00816a7c
    static HACMSTREAM m_unk0x00816a7c;
};

#endif
