#include "InstallInfo.h"
#include "main.h"
#include "Logger.h"

char CInstallInfo::m_frontendDir[MAX_PATH];
char CInstallInfo::m_countrySpecificDir[MAX_PATH];
char CInstallInfo::m_regKeyLanguage[9] = "Language";
char CInstallInfo::m_regKeyValueAmerican[9] = "American";
char CInstallInfo::m_regKeyValuePolish[7] = "Polish";
char CInstallInfo::m_regKeyValueSpanish[8] = "Spanish";
char CInstallInfo::m_regKeyValueItalian[8] = "Italian";
char CInstallInfo::m_regKeyValueGerman[7] = "German";
char CInstallInfo::m_regKeyValueFrench[7] = "French";
char CInstallInfo::m_regKeyValueEnglish[8] = "English";

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

// STUB: CMR2 0x004aa720
char *CInstallInfo::GetRegKeyValue(char *key)
{
    return 0;
}

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
BOOL __stdcall CInstallInfo::ShowNoCDErrorMessage(int param1)
{
    char *gameLanguage;
    int languageID;

    gameLanguage = GetRegKeyValue(m_regKeyLanguage);
    languageID = _stricmp(gameLanguage, m_regKeyValueEnglish);
    if (languageID != 0)
    {
        if (_stricmp(gameLanguage, m_regKeyValueFrench) == 0)
            languageID = 4;
        else
        {
            if (_stricmp(gameLanguage, m_regKeyValueGerman) == 0)
                languageID = 1;
            else
            {
                if (_stricmp(gameLanguage, m_regKeyValueItalian) == 0)
                    languageID = 2;
                else
                {
                    if (_stricmp(gameLanguage, m_regKeyValueSpanish) == 0)
                        languageID = 3;
                    else
                    {
                        if (_stricmp(gameLanguage, m_regKeyValuePolish) == 0)
                            languageID = 5;
                        else
                        {
                            if (_stricmp(gameLanguage, m_regKeyValueAmerican) == 0)
                                languageID = 6;
                            else
                                languageID = param1;
                        }
                    }
                }
            }
        }
    }

    if (MessageBoxA(CMain::m_hWndList[CMain::m_hWndIx], m_noCDMessages[languageID][0], m_noCDMessages[languageID][1], MB_RETRYCANCEL) == 2)
    {
        CMain::FUN_0049c130();
        CLogger::CloseLogFile();
        ExitProcess(CMain::m_unk0x00663c70);
    }

    return TRUE;
}
