#include "StageTiming.h"
#include "Stage.h"

// 10 - split id, 16 - drivers
// GLOBAL: CMR2 0x00541fac
char g_stageSplitDriverIndices[10][16];

// FUNCTION: CMR2 0x00455cf0
int __stdcall StageTiming_GetTimeForPosition(int positionIx)
{
    int iSplitIx = GetStageSplitCount();

    /* This isn't the driver name, just the index in the lookup table. It looks like
       driver ix 15 is the player */
    return g_stageSplitDriverIndices[iSplitIx][positionIx];
}
