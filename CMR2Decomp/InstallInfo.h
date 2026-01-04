#ifndef _INSTALL_INFO_H
#define _INSTALL_INFO_H

#include <windows.h>

class CInstallInfo
{
public:
    static char *GetFrontendDir();
    static char *GetCountrySpecificDir();
    static BOOL ShowNoCDErrorMessage(int param1);
    static int FUN_0040e8d0(void);
    static void SetGameHDPath(char *filePath);
    static void SetGameCDPath(char *filePath);

private:
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

    // guess
    // GLOBAL: CMR2 0x006640f0
    static char m_hdPath[MAX_PATH];
    // GLOBAL: CMR2 0x00664604
    static int m_isHDInstall;

    // GLOBAL: CMR2 0x00664400
    static char m_cdPath[MAX_PATH];
    // GLOBAL: CMR2 0x00664608
    static int m_isCDInstall;

    // all the directories for assets
    // GLOBAL: CMR2 0x005361a8
    static char m_tracksDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516b0c
    static char m_tracksSubDir[15];
    // GLOBAL: CMR2 0x005364b4
    static char m_carsDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516afc
    static char m_carsSubDir[13];
    // GLOBAL: CMR2 0x00535fa0
    static char m_soundsDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516af0
    static char m_soundsSubDir[10];
    // GLOBAL: CMR2 0x005365b8
    static char m_savesDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516ae0
    static char m_savesSubDir[13];
    // GLOBAL: CMR2 0x005368c4
    static char m_musicDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516ad0
    static char m_musicSubDir[16];
    // GLOBAL: CMR2 0x005360a4
    static char m_videosDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516abc
    static char m_videosSubDir[19];
    // GLOBAL: CMR2 0x005366bc
    static char m_frontendDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516ab0
    static char m_frontendSubDir[12];
    // GLOBAL: CMR2 0x00535b90
    static char m_countrySpecificDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516a9c
    static char m_countrySpecificSubDir[19];
    // GLOBAL: CMR2 0x00535d98
    static char m_countrySpecificOtherDir[MAX_PATH];
    // GLOBAL: CMR2 0x00535e9c
    static char m_setupRepDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516a90
    static char m_setupRepSubDir[12];
    // GLOBAL: CMR2 0x005362ac
    static char m_bigFilesDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516a5c
    static char m_bigFilesSubDir[17];
    // GLOBAL: CMR2 0x005363b0
    static char m_texturesDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516a50
    static char m_texturesSubDir[11];
    // GLOBAL: CMR2 0x00535c94
    static char m_fontsDir[MAX_PATH];
    // GLOBAL: CMR2 0x00516a48
    static char m_fontsSubDir[8];
    // GLOBAL: CMR2 0x005367c0
    static char m_surprisedDir[3];
    // GLOBAL: CMR2 0x00516a44
    static char m_surprisedSubDir[3];
};

#endif
