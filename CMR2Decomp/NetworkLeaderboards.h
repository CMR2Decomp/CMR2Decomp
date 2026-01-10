#ifndef _NETWORK_LEADERBOARDS_H
#define _NETWORK_LEADERBOARDS_H

#include "GenericFileLoader.h"

struct NetworkLeaderboard {
    BYTE isLoaded;
    BYTE pad[259];
};

struct NetworkLeaderboards {
    int leaderboardID;
    int totalLeaderboards;
    NetworkLeaderboard leaderboards[32];
};

class CNetworkLeaderboards {
    static void Reset(void);

    // GLOBAL: CMR2 0x00516a0c
    static GenericFile* m_leaderboardsFile;
    // GLOBAL: CMR2 0x00535b88
    static BOOL m_hasLoaded;
    // GLOBAL: CMR2 0x00533a08
    static NetworkLeaderboards m_leaderboards;
};

#endif
