#ifndef _FRONTEND_H
#define _FRONTEND_H

#include "GenericFileLoader.h"
#include "Texture.h"

// TODO: no idea if this is the right thing to call this
class CFrontend
{
public:
    static void FUN_004d21e0(void);
    static BOOL FUN_004b7560(unsigned int param_1);
    static BOOL FUN_004b7590(unsigned int param_1);
    static BOOL FUN_004a9700(void);

    // GLOBAL: CMR2 0x00663b60
    static char m_stringDest[MAX_PATH];

    // GLOBAL: CMR2 0x00523dd0
    static char m_feRes640CountrySpecific[19];
    // GLOBAL: CMR2 0x00523de4
    static char m_feRes640CCountrySpecific[20];
    // GLOBAL: CMR2 0x00523df8
    static char m_feRes1024CountrySpecific[20];
    // GLOBAL: CMR2 0x00523e0c
    static char m_feRes1024CCountrySpecific[21];
    // GLOBAL: CMR2 0x00523e24
    static char m_feRes640[14];
    // GLOBAL: CMR2 0x00523e34
    static char m_feRes640C[15];
    // GLOBAL: CMR2 0x00523e44
    static char m_feRes1024[15];
    // GLOBAL: CMR2 0x00523e54
    static char m_feRes1024C[16];

    // unknowns
    // GLOBAL: CMR2 0x00818260;
    static GenericFile m_unk0x00818260;
    // GLOBAL: CMR2 0x006e0c5c
    static unsigned int m_unk0x006e0c5c;
    // GLOBAL: CMR2 0x006e0c64
    static unsigned int m_unk0x006e0c64;
    // GLOBAL: CMR2 0x006e0c60
    static unsigned int m_unk0x006e0c60;
    // GLOBAL: CMR2 0x006e0c68
    static unsigned int m_unk0x006e0c68;
    // GLOBAL: CMR2 0x00663b38
    static unsigned int m_unk0x00663b38;
    // GLOBAL: CMR2 0x00663b48
    static unsigned int m_unk0x00663b48;

    // GLOBAL: CMR2 0x00525034
    static char m_strFrontendTexturesAr640ATGA[36];

    // GLOBAL: CMR2 0x00525010
    static char m_strFrontendTexturesAr640DTGA[36];

    // GLOBAL: CMR2 0x00524fec
    static char m_strFrontendTexturesLgMatrixTGA[36];

    // GLOBAL: CMR2 0x00524fc8
    static char m_strFrontendTexturesSmMatrixTGA[36];
    
    // GLOBAL: CMR2 0x00818548
    static Texture* m_pAr640ATexture;

    // GLOBAL: CMR2 0x008185b8
    static Texture* m_pAr640DTexture;

    // GLOBAL: CMR2 0x008182b8
    static Texture* m_pLgMatrixTexture;

    // GLOBAL: CMR2 0x00818324
    static Texture* m_pSmMatrixTexture;

    // GLOBAL: CMR2 0x00818328
    static Texture* m_pSetupRepBanners[8];

    // GLOBAL: CMR2 0x00818348
    static Texture* m_pTinyFlags[8];

    // GLOBAL: CMR2 0x008182bc
    static Texture* m_pTBronze;

    // GLOBAL: CMR2 0x008182c0
    static Texture* m_pTSilver;

    // GLOBAL: CMR2 0x008182c4
    static Texture* m_pTGold;

    // GLOBAL: CMR2 0x00524fa0
    static char m_strSetupRepTexturesBanners[40];

    // GLOBAL: CMR2 0x00524f78
    static char m_strFrontendTinyFlags[40];

    // GLOBAL: CMR2 0x00524f10
    static char m_strFrontendTexturesTBronzeTGA[36];    

    // GLOBAL: CMR2 0x00524f34
    static char m_strFrontendTexturesTSilverTGA[36];

    // GLOBAL: CMR2 0x00524f58
    static char m_strFrontendTexturesTGoldTGA[32];
};

#endif
