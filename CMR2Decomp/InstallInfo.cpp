#include "InstallInfo.h"
#include "main.h"
#include "Logger.h"
#include "RegKey.h"
#include <stdio.h>

char CInstallInfo::m_noCDBodyEnglish[43] = "Make sure the CMR2 CD is in the CD drive";
char CInstallInfo::m_noCDBodyGerman[72] = "Vergewissern Sie sich, da\xdf sich die CMR2-CD im CD-ROM-Laufwerk befindet";
char CInstallInfo::m_noCDBodyItalian[48] = "Assicurate che il CD di CMR2 sia nel lettore CD";
char CInstallInfo::m_noCDBodySpanish[60] = "Asegura que el CD de CMR2 est\xe1 en la disquetera de los CD";
char CInstallInfo::m_noCDBodyFrench[55] = "Assurez vous que le CD CMR2 soit dans le lecteur de CD";
char CInstallInfo::m_noCDBodyPolish[43] = "P_Make sure the CMR2 CD is in the CD drive";
char CInstallInfo::m_noCDBodyAmerican[44] = "US_Make sure the CMR2 CD is in the CD drive";

char CInstallInfo::m_noCDHeaderEnglish[21] = "CMR2 File Load Error";
char CInstallInfo::m_noCDHeaderGerman[33] = "Fehler beim Laden der Datei CMR2";
char CInstallInfo::m_noCDHeaderItalian[37] = "Errore nel caricamento del file CMR2";
char CInstallInfo::m_noCDHeaderSpanish[31] = "Error cargando archivo de CMR2";
char CInstallInfo::m_noCDHeaderFrench[31] = "Erreur chargement fichier CMR2";
char CInstallInfo::m_noCDHeaderPolish[23] = "P_CMR2 File Load Error";
char CInstallInfo::m_noCDHeaderAmerican[24] = "US_CMR2 File Load Error";

char *CInstallInfo::m_noCDMessages[7][2] = {
    {m_noCDBodyEnglish, m_noCDHeaderEnglish},
    {m_noCDBodyGerman, m_noCDHeaderGerman},
    {m_noCDBodyItalian, m_noCDHeaderItalian},
    {m_noCDBodySpanish, m_noCDHeaderSpanish},
    {m_noCDBodyFrench, m_noCDHeaderFrench},
    {m_noCDBodyPolish, m_noCDHeaderPolish},
    {m_noCDBodyAmerican, m_noCDHeaderAmerican}};

char CInstallInfo::m_hdPath[MAX_PATH];
int CInstallInfo::m_isHDInstall = 0;

char CInstallInfo::m_cdPath[MAX_PATH];
int CInstallInfo::m_isCDInstall = 0;

// asset directories
char CInstallInfo::m_tracksDir[MAX_PATH] = "";
char CInstallInfo::m_carsDir[MAX_PATH] = "";
char CInstallInfo::m_soundsDir[MAX_PATH] = "";
char CInstallInfo::m_savesDir[MAX_PATH] = "";
char CInstallInfo::m_musicDir[MAX_PATH] = "";
char CInstallInfo::m_videosDir[MAX_PATH] = "";
char CInstallInfo::m_frontendDir[MAX_PATH] = "";
char CInstallInfo::m_countrySpecificDir[MAX_PATH] = "";
char CInstallInfo::m_countrySpecificOtherDir[MAX_PATH] = "";
char CInstallInfo::m_setupRepDir[MAX_PATH] = "";
char CInstallInfo::m_bigFilesDir[MAX_PATH] = "";
char CInstallInfo::m_texturesDir[MAX_PATH] = "";
char CInstallInfo::m_fontsDir[MAX_PATH] = "";
char CInstallInfo::m_surprisedDir[3] = "";

char CInstallInfo::m_tracksSubDir[15] = "%s\\Game\\Tracks";
char CInstallInfo::m_carsSubDir[13] = "%s\\Game\\Cars";
char CInstallInfo::m_soundsSubDir[10] = "%s\\sounds";
char CInstallInfo::m_savesSubDir[13] = "%s\\CMR2Saves";
char CInstallInfo::m_musicSubDir[16] = "%s\\sounds\\music";
char CInstallInfo::m_videosSubDir[19] = "%s\\FrontEnd\\Videos";
char CInstallInfo::m_frontendSubDir[12] = "%s\\FrontEnd";
char CInstallInfo::m_countrySpecificSubDir[19] = "%s\\CountrySpecific";
char CInstallInfo::m_setupRepSubDir[12] = "%s\\SetupRep";

char CInstallInfo::m_bigFilesSubDir[17] = "%s\\Game\\BigFiles";
char CInstallInfo::m_texturesSubDir[11] = ".\\Textures";
char CInstallInfo::m_fontsSubDir[8] = ".\\Fonts";
char CInstallInfo::m_surprisedSubDir[3] = "O:";

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

// FUNCTION: CMR2 0x004aa480
BOOL CInstallInfo::ShowNoCDErrorMessage(int param1)
{
    char *gameLanguage;
    int languageID;

    gameLanguage = CRegKey::GetValueFromKey(CRegKey::m_regKeyLanguage);
    languageID = _stricmp(gameLanguage, CRegKey::m_regKeyValueEnglish);
    if (languageID != 0)
    {
        if (_stricmp(gameLanguage, CRegKey::m_regKeyValueFrench) == 0)
            languageID = 4;
        else
        {
            if (_stricmp(gameLanguage, CRegKey::m_regKeyValueGerman) == 0)
                languageID = 1;
            else
            {
                if (_stricmp(gameLanguage, CRegKey::m_regKeyValueItalian) == 0)
                    languageID = 2;
                else
                {
                    if (_stricmp(gameLanguage, CRegKey::m_regKeyValueSpanish) == 0)
                        languageID = 3;
                    else
                    {
                        if (_stricmp(gameLanguage, CRegKey::m_regKeyValuePolish) == 0)
                            languageID = 5;
                        else
                        {
                            if (_stricmp(gameLanguage, CRegKey::m_regKeyValueAmerican) == 0)
                                languageID = 6;
                            else
                                languageID = param1;
                        }
                    }
                }
            }
        }
    }

    if (MessageBoxA(CMain::m_hWndList[CMain::m_hWndIx], m_noCDMessages[languageID][0], m_noCDMessages[languageID][1], MB_RETRYCANCEL) == IDCANCEL)
    {
        CMain::FUN_0049c130();
        CLogger::CloseLogFile();
        ExitProcess(CMain::m_win32Msg.wParam);
    }

    return TRUE;
}

// FUNCTION: CMR2 0x040e8d0
int __stdcall CInstallInfo::FUN_0040e8d0(void)
{
    char *regKeyValue;
    char hdPath[MAX_PATH], cdPath[MAX_PATH], installVersion[16], *bigFileLocation;

    // if the game is on the HD
    regKeyValue = CRegKey::GetValueFromKey(CRegKey::m_rkv_gameHDPath);
    if (*regKeyValue == 0)
        return 0;

    // store the HD path
    strcpy(hdPath, regKeyValue);
    CInstallInfo::SetGameHDPath(hdPath);

    // if the game is on the CD
    regKeyValue = CRegKey::GetValueFromKey(CRegKey::m_rkv_gameCDPath);
    if (*regKeyValue == 0)
        return 0;

    // store the CD path
    strcpy(cdPath, regKeyValue);
    CInstallInfo::SetGameCDPath(cdPath);

    // game install version
    regKeyValue = CRegKey::GetValueFromKey(CRegKey::m_rkv_installVersion);
    if (*regKeyValue == 0)
        return 0;

    strcpy(installVersion, regKeyValue);

    // if its the minimum version
    if (_stricmp(installVersion, CRegKey::m_rkv_installMinimum) == 0)
    {
        sprintf(m_tracksDir, m_tracksSubDir, cdPath);
        sprintf(m_carsDir, m_carsSubDir, cdPath);
        sprintf(m_soundsDir, m_soundsSubDir, cdPath);
        sprintf(m_savesDir, m_savesSubDir, hdPath);
        sprintf(m_musicDir, m_musicSubDir, cdPath);
        sprintf(m_videosDir, m_videosSubDir, cdPath);
        sprintf(m_frontendDir, m_frontendSubDir, cdPath);
        sprintf(m_countrySpecificDir, m_countrySpecificSubDir, cdPath);
        sprintf(m_countrySpecificOtherDir, m_countrySpecificSubDir, cdPath);
        sprintf(m_setupRepDir, m_setupRepSubDir, cdPath);
        bigFileLocation = cdPath;
    }
    else
    {
        // medium
        if (_stricmp(installVersion, CRegKey::m_rkv_installMedium) == 0)
        {
            sprintf(m_tracksDir, m_tracksSubDir, hdPath);
            sprintf(m_carsDir, m_carsSubDir, hdPath);
            sprintf(m_soundsDir, m_soundsSubDir, hdPath);
            sprintf(m_savesDir, m_savesSubDir, hdPath);
            sprintf(m_musicDir, m_musicSubDir, cdPath);
            sprintf(m_videosDir, m_videosSubDir, cdPath);
            sprintf(m_frontendDir, m_frontendSubDir, hdPath);
            sprintf(m_countrySpecificDir, m_countrySpecificSubDir, hdPath);
            sprintf(m_countrySpecificOtherDir, m_countrySpecificSubDir, cdPath);
            sprintf(m_setupRepDir, m_setupRepSubDir, hdPath);
            bigFileLocation = hdPath;
        }
        else
        {
            // full/network
            if (_stricmp(installVersion, CRegKey::m_rkv_installFull) == 0 || _stricmp(installVersion, CRegKey::m_rkv_installNetworkOnly) == 0)
            {
                sprintf(m_tracksDir, m_tracksSubDir, hdPath);
                sprintf(m_carsDir, m_carsSubDir, hdPath);
                sprintf(m_soundsDir, m_soundsSubDir, hdPath);
                sprintf(m_savesDir, m_savesSubDir, hdPath);
                sprintf(m_musicDir, m_musicSubDir, cdPath);
                sprintf(m_videosDir, m_videosSubDir, hdPath);
                sprintf(m_frontendDir, m_frontendSubDir, hdPath);
                sprintf(m_countrySpecificDir, m_countrySpecificSubDir, hdPath);
                sprintf(m_countrySpecificOtherDir, m_countrySpecificSubDir, hdPath);
                sprintf(m_setupRepDir, m_setupRepSubDir, hdPath);
                bigFileLocation = hdPath;
            }
            else
                return 0;
        }
    }

    // install dependant locations
    sprintf(m_bigFilesDir, m_bigFilesSubDir, bigFileLocation);
    sprintf(m_texturesDir, m_texturesSubDir);
    sprintf(m_fontsDir, m_fontsSubDir);

    return sprintf(m_surprisedDir, m_surprisedSubDir);
}

// FUNCTION: CMR2 0x004aa6c0
void __stdcall CInstallInfo::SetGameHDPath(char *filePath)
{
    lstrcpyA(m_hdPath, filePath);
    m_isHDInstall = 1;
    return;
}

// FUNCTION: CMR2 0x004aa6e0
void __stdcall CInstallInfo::SetGameCDPath(char *filePath)
{
    lstrcpyA(m_cdPath, filePath);
    m_isCDInstall = 1;
    return;
}
