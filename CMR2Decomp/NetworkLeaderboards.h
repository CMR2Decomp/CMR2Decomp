#ifndef _NETWORK_LEADERBOARDS_H
#define _NETWORK_LEADERBOARDS_H

#include "GenericFileLoader.h"

struct NetworkLeaderboard {
    BOOL isLoaded;
    char name[4];
    int wins;
    BYTE pad[248];
};

struct NetworkLeaderboardsFile {
    int leaderboardID;
    int totalLeaderboards;
    NetworkLeaderboard leaderboards[32];
};

class CNetworkLeaderboards {
public:
    static void Reset(void);
    static bool LoadLeaderboards(void);

private:
    // GLOBAL: CMR2 0x00516a0c
    static int m_leaderboardId;
    // GLOBAL: CMR2 0x00535b88
    static int m_totalLeaderboards;
    // GLOBAL: CMR2 0x00533a08
    static NetworkLeaderboard m_leaderboards[32];
    // GLOBAL: CMR2 0x00516a10
    static char m_strNetworkLeaderboardsDir[40];
};

#endif
