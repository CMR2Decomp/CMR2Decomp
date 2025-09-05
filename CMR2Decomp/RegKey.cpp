#include "RegKey.h"
#include "Frontend.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>

// registry key path value
char CRegKey::m_regKeyPathSoftware[9] = "SOFTWARE";
char CRegKey::m_regKeyPathCodemasters[12] = "Codemasters";
char CRegKey::m_regKeyPathCMR2[20] = "Colin McRae Rally 2";
char CRegKey::m_regKeyPathFormatValue[3] = "%s";
BYTE CRegKey::m_regKeyReadData[100] = "";

// language related values
char CRegKey::m_regKeyLanguage[9] = "Language";
char CRegKey::m_regKeyValueAmerican[9] = "American";
char CRegKey::m_regKeyValuePolish[7] = "Polish";
char CRegKey::m_regKeyValueSpanish[8] = "Spanish";
char CRegKey::m_regKeyValueItalian[8] = "Italian";
char CRegKey::m_regKeyValueGerman[7] = "German";
char CRegKey::m_regKeyValueFrench[7] = "French";
char CRegKey::m_regKeyValueEnglish[8] = "English";

// sku related values
char CRegKey::m_regKeySkuType[9] = "Sku_Type";
char CRegKey::m_skuJapan[6] = "JAPAN";
char CRegKey::m_skuPoland[7] = "POLAND";
char CRegKey::m_skuAmerica[8] = "AMERICA";
char CRegKey::m_skuEurope[7] = "EUROPE";

// installation related values
char CRegKey::m_rkv_gameHDPath[12] = "Game_HDPath";
char CRegKey::m_rkv_gameCDPath[12] = "Game_CDPath";
char CRegKey::m_rkv_installVersion[16] = "Install_Version";
char CRegKey::m_rkv_installMinimum[8] = "Minimum";
char CRegKey::m_rkv_installMedium[7] = "Medium";
char CRegKey::m_rkv_installFull[5] = "Full";
char CRegKey::m_rkv_installNetworkOnly[13] = "Network Only";

// FUNCTION: CMR2 0x004aa720
char *__stdcall CRegKey::GetValueFromKey(char *key)
{
    LONG regOpenKeyStatus;
    HKEY regKeyResult;
    HKEY regKeySoftwareResult;
    HKEY regKeyCodemastersResult;
    HKEY regKeyCMR2Result;
    DWORD regKeyType;
    DWORD regKeyFinalResult;
    char regKeySubValue[100];

    regKeyFinalResult = 100;

    strcpy(CFrontend::m_stringDest, key);
    regOpenKeyStatus = RegOpenKeyExA(HKEY_LOCAL_MACHINE, NULL, 0, KEY_EXECUTE, &regKeyResult);
    if (regOpenKeyStatus == ERROR_SUCCESS)
    {
        sprintf(regKeySubValue, m_regKeyPathSoftware);
        regOpenKeyStatus = RegOpenKeyExA(regKeyResult, regKeySubValue, 0, KEY_EXECUTE, &regKeySoftwareResult);
        if (regOpenKeyStatus == ERROR_SUCCESS)
        {
            sprintf(regKeySubValue, m_regKeyPathCodemasters);
            regOpenKeyStatus = RegOpenKeyExA(regKeySoftwareResult, regKeySubValue, 0, KEY_EXECUTE, &regKeyCodemastersResult);
            if (regOpenKeyStatus == ERROR_SUCCESS)
            {
                sprintf(regKeySubValue, m_regKeyPathCMR2);
                regOpenKeyStatus = RegOpenKeyExA(regKeyCodemastersResult, regKeySubValue, 0, KEY_EXECUTE, &regKeyCMR2Result);
                if (regOpenKeyStatus == ERROR_SUCCESS)
                {
                    sprintf(regKeySubValue, m_regKeyPathFormatValue, CFrontend::m_stringDest);
                    regOpenKeyStatus = RegQueryValueExA(regKeyCMR2Result, regKeySubValue, NULL, &regKeyType, m_regKeyReadData, &regKeyFinalResult);
                    if (regOpenKeyStatus != ERROR_SUCCESS)
                        m_regKeyReadData[0] = 0x0;
                }
            }
        }
    }

    RegCloseKey(regKeyCMR2Result);
    RegCloseKey(regKeyCodemastersResult);
    RegCloseKey(regKeySoftwareResult);
    RegCloseKey(regKeyResult);

    return (char *)m_regKeyReadData;
}
