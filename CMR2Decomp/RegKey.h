#ifndef _REG_KEY_H
#define _REG_KEY_H

class CRegKey
{
public:
    static char *GetValueFromKey(char *key);

    // GLOBAL: CMR2 0x00520f88
    static char m_regKeyPathSoftware[9];
    // GLOBAL: CMR2 0x00520f7c
    static char m_regKeyPathCodemasters[12];
    // GLOBAL: CMR2 0x00520f68
    static char m_regKeyPathCMR2[20];
    // GLOBAL: CMR2 0x00516180
    static char m_regKeyPathFormatValue[3]; // TODO: move this somewhere more generic?
    // GLOBAL: CMR2 0x00663ee4
    static unsigned char m_regKeyReadData[100];

    // GLOBAL: CMR2 0x00520f5c
    static char m_regKeyLanguage[9];
    // GLOBAL: CMR2 0x00520f20
    static char m_regKeyValueAmerican[9];
    // GLOBAL: CMR2 0x00520f2c
    static char m_regKeyValuePolish[7];
    // GLOBAL: CMR2 0x00520f34
    static char m_regKeyValueSpanish[8];
    // GLOBAL: CMR2 0x00520f3c
    static char m_regKeyValueItalian[8];
    // GLOBAL: CMR2 0x00520f44
    static char m_regKeyValueGerman[7];
    // GLOBAL: CMR2 0x00520f4c
    static char m_regKeyValueFrench[7];
    // GLOBAL: CMR2 0x00520f54
    static char m_regKeyValueEnglish[8];

    // GLOBAL: CMR2 0x00523d98
    static char m_regKeySkuType[9];
    // GLOBAL: CMR2 0x00519340
    static char m_skuJapan[6];
    // GLOBAL: CMR2 0x00523d80
    static char m_skuPoland[7];
    // GLOBAL: CMR2 0x00523d88
    static char m_skuAmerica[8];
    // GLOBAL: CMR2 0x00523d90
    static char m_skuEurope[7];

    // rkv=reg key value
    // GLOBAL: CMR2 0x00516a38
    static char m_rkv_gameHDPath[12];
    // GLOBAL: CMR2 0x00516b34
    static char m_rkv_gameCDPath[12];
    // GLOBAL: CMR2 0x00516b24
    static char m_rkv_installVersion[16];
    // GLOBAL: CMR2 0x00516b1c
    static char m_rkv_installMinimum[8];
    // GLOBAL: CMR2 0x00516a88
    static char m_rkv_installMedium[7];
    // GLOBAL: CMR2 0x00516a80
    static char m_rkv_installFull[5];
    // GLOBAL: CMR2 0x00516a70
    static char m_rkv_installNetworkOnly[13];
};

#endif
