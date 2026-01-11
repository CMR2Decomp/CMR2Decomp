#ifndef _NETWORK_LEADERBOARDS_H
#define _NETWORK_LEADERBOARDS_H

#include "GenericFileLoader.h"

#define MAX_LEADERBOARDS 32
#define MAX_LEADERBOARD_PLAYERS 32

struct NetworkLeaderboardEntry {
    char name[4];
    int wins;
};

struct NetworkLeaderboard {
    BOOL isLoaded;
    NetworkLeaderboardEntry entries[MAX_LEADERBOARD_PLAYERS];
};

struct NetworkLeaderboardsFile {
    int leaderboardID;
    int totalLeaderboards;
    NetworkLeaderboard leaderboards[MAX_LEADERBOARDS];
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
