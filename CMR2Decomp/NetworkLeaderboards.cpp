#include "NetworkLeaderboards.h"

GenericFile* CNetworkLeaderboards::m_leaderboardsFile;
BOOL CNetworkLeaderboards::m_hasLoaded;
NetworkLeaderboards CNetworkLeaderboards::m_leaderboards;

// FUNCTION: CMR2 0x0040e3c0
void CNetworkLeaderboards::Reset() {
    m_leaderboardsFile = (GenericFile*)-1;
    m_hasLoaded = FALSE;
    
    int addr = (int)&m_leaderboards;
    int endAddr = addr + sizeof(NetworkLeaderboards);
    
    while (addr < endAddr) {
        *(BYTE*)addr = 0;
        addr += 0x104;
    }
}
