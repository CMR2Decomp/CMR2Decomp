#ifndef _INSTALL_INFO_H
#define _INSTALL_INFO_H

#include <windows.h>

class CInstallInfo
{
public:
    static char *GetFrontendDir();
    static char *GetCountrySpecificDir();
    static BOOL ShowNoCDErrorMessage(int param1);

    static char *GetRegKeyValue(char *key);

private:
    // GLOBAL: CMR2 0x005366bc
    static char m_frontendDir[MAX_PATH];
    // GLOBAL: CMR2 0x00535b90
    static char m_countrySpecificDir[MAX_PATH];
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

    // GLOBAL: CMR2 0x00520ef0
    static char m_noCDBodyEnglish[43];
    // GLOBAL: CMR2 0x0000520d80
    static char m_noCDBodyFrench[55];
    // GLOBAL: CMR2 0x00520e90
    static char m_noCDBodyGerman[72];
    // GLOBAL: CMR2 0x00520e3c
    static char m_noCDBodyItalian[48];
    // GLOBAL: CMR2 0x00520dd8
    static char m_noCDBodySpanish[60];
    // GLOBAL: CMR2 0x00520d34
    static char m_noCDBodyPolish[43];
    // GLOBAL: CMR2 0x00520cf0
    static char m_noCDBodyAmerican[44];

    // GLOBAL: CMR2 0x00520ed8
    static char m_noCDHeaderEnglish[21];
    // GLOBAL: CMR2 0x00520d60
    static char m_noCDHeaderFrench[31];
    // GLOBAL: CMR2 0x00520e6c
    static char m_noCDHeaderGerman[33];
    // GLOBAL: CMR2 0x00520e14
    static char m_noCDHeaderItalian[37];
    // GLOBAL: CMR2 0x00520db8
    static char m_noCDHeaderSpanish[31];
    // GLOBAL: CMR2 0x00520d1c
    static char m_noCDHeaderPolish[23];
    // GLOBAL: CMR2 0x00520cd8
    static char m_noCDHeaderAmerican[24];

    // GLOBAL: CMR2 0x00520ca0
    static char *m_noCDMessages[7][2];
};

#endif
