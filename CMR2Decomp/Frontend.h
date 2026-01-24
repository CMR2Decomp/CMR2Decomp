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

    // GLOBAL: CMR2 0x00516c78
    static char m_strEsc[4];

    // GLOBAL: CMR2 0x00516c7c
    static char m_strPum[4];

    // GLOBAL: CMR2 0x00516c80
    static char m_str205[4];

    // GLOBAL: CMR2 0x00516c84
    static char m_strStr[4];

    // GLOBAL: CMR2 0x00516c88
    static char m_str6R4[4];

    // GLOBAL: CMR2 0x00516c8c
    static char m_strMin[4];

    // GLOBAL: CMR2 0x00516c90
    static char m_strSie[4];

    // GLOBAL: CMR2 0x00516c94
    static char m_strIA2[4];

    // GLOBAL: CMR2 0x00516c98
    static char m_strIA1[4];

    // GLOBAL: CMR2 0x00516c9c
    static char m_strInt[4];

    // GLOBAL: CMR2 0x00516ca0
    static char m_strSea[4];

    // GLOBAL: CMR2 0x00516ca4
    static char m_str206[4];

    // GLOBAL: CMR2 0x00516ca8
    static char m_strSubShort[4];

    // GLOBAL: CMR2 0x00516cac
    static char m_strCor[4];

    // GLOBAL: CMR2 0x00516cb0
    static char m_strMA3[4];

    // GLOBAL: CMR2 0x00516cb4
    static char m_strMA2[4];

    // GLOBAL: CMR2 0x00516cb8
    static char m_strMA1[4];

    // GLOBAL: CMR2 0x00516cbc
    static char m_strMit[4];

    // GLOBAL: CMR2 0x00516cc0
    static char m_strFA2[4];

    // GLOBAL: CMR2 0x00516cc4
    static char m_strFA1[4];

    // GLOBAL: CMR2 0x00516cc8
    static char m_strF99Short[4];

    // GLOBAL: CMR2 0x00516ccc
    static char m_strFoc[4];    

    // GLOBAL: CMR2 0x00524c10
    static char m_strEscort[7];

    // GLOBAL: CMR2 0x00524c18
    static char m_strPuma[7];
    
    // GLOBAL: CMR2 0x00524c20
    static char m_strStrts[7];

    // GLOBAL: CMR2 0x00524c28
    static char m_str6r4[4];

    // GLOBAL: CMR2 0x00524c2c
    static char m_strMini[7];

    // GLOBAL: CMR2 0x00524c34
    static char m_strSerra[7];

    // GLOBAL: CMR2 0x00524c3c
    static char m_strDelta[7];

    // GLOBAL: CMR2 0x00524c44
    static char m_strCrdba[7];

    // GLOBAL: CMR2 0x00524c4c
    static char m_strSub[4];

    // GLOBAL: CMR2 0x00524c50
    static char m_strCrlla[7];

    // GLOBAL: CMR2 0x00524c58
    static char m_strLncer[7];

    // GLOBAL: CMR2 0x00524c60
    static char m_strF99[4];

    // GLOBAL: CMR2 0x00524c64
    static char m_strF2000[7];

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
