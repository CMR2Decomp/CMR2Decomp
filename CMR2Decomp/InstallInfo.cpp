#include "InstallInfo.h"

char CInstallInfo::m_frontendDir[MAX_PATH];
char CInstallInfo::m_countrySpecificDir[MAX_PATH];

// FUNCTION: CMR2 0x0040ed90
char *CInstallInfo::GetFrontendDir(void)
{
    return m_frontendDir;
}

// FUNCTION: CMR2 0x0040eda0
char *CInstallInfo::GetCountrySpecificDir(void)
{
    return m_countrySpecificDir;
}
