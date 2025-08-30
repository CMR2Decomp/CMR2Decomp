#ifndef _INSTALL_INFO_H
#define _INSTALL_INFO_H

#include <windows.h>

class CInstallInfo
{
public:
    static char *GetFrontendDir();
    static char *GetCountrySpecificDir();
    static BOOL ShowNoCDErrorMessage(BOOL param1);

private:
    // GLOBAL: CMR2 0x005366bc
    static char m_frontendDir[MAX_PATH];
    // GLOBAL: CMR2 0x00535b90
    static char m_countrySpecificDir[MAX_PATH];
};

#endif
