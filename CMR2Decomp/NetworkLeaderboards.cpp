#include "NetworkLeaderboards.h"
#include "RegKey.h"
#include "InstallInfo.h"
#include "FileBuffer.h"
#include <stdio.h>

int CNetworkLeaderboards::m_leaderboardId;
int CNetworkLeaderboards::m_totalLeaderboards;
NetworkLeaderboard CNetworkLeaderboards::m_leaderboards[32];
char CNetworkLeaderboards::m_strNetworkLeaderboardsDir[40] = "%s\\NetworkLeaderboards\\leaderboards.nlb";

// FUNCTION: CMR2 0x0040e3c0
void CNetworkLeaderboards::Reset() {
    m_leaderboardId = -1;
    m_totalLeaderboards = 0;

    int addr = (int)&m_leaderboards;
    int endAddr = addr + sizeof(m_leaderboards);
    
    while (addr < endAddr) {
        *(BYTE*)addr = 0;
        addr += 0x104;
    }
}

// FUNCTION: CMR2 0x0040e3f0
bool CNetworkLeaderboards::LoadLeaderboards(void) {
    char fileLocation[MAX_PATH];
    GenericFile * fileBuffer;
    bool hasLoaded = false;
    NetworkLeaderboardsFile* leaderboards;

    sprintf(fileLocation, m_strNetworkLeaderboardsDir, CRegKey::GetValueFromKey(CRegKey::m_rkv_gameHDPath));
    leaderboards = (NetworkLeaderboardsFile*)(((GenericFile*)CFileBuffer::GetGenericFileBuffer(fileLocation, TRUE))->buffer);
    if (leaderboards != NULL) {
        if (CGenericFileLoader::GetGenericFileSize() == 0x2088) {
            m_leaderboardId = leaderboards->leaderboardID;
            m_totalLeaderboards = leaderboards->totalLeaderboards;
            
            memcpy(&m_leaderboards, leaderboards->leaderboards, sizeof(leaderboards->leaderboards));
            hasLoaded = TRUE;
            
        }

        CFileBuffer::FreeGenericFileBuffer(leaderboards);
    }

    return hasLoaded;
}
