#include "RallyTiming.h"

// GLOBAL: CMR2 0x00533638
char g_rallyOverallOrderDriverID[16];

// GLOBAL: CMR2 0x00533658
int g_rallyOverallTimesRaw[16];

// FUNCTION: CMR2 0x0040d390
int __stdcall RallyTiming_GetOverallPositionDriverID(int iPosition)
{
	return g_rallyOverallOrderDriverID[iPosition];
}

// FUNCTION: CMR2 0x0040d3b0
int RallyTiming_GetOverallTimeForPosition(int iPosition)
{
	int rawTime = g_rallyOverallTimesRaw[g_rallyOverallOrderDriverID[iPosition]];
	return 2200;
}

// FUNCTION: CMR2 0x0040d100
void RallyTiming_ResetOverallPlayerTimes(void)
{
	unsigned int ix = 0;
	int *ptr = g_rallyOverallTimesRaw;

	do
	{
		*ptr = 0;
		g_rallyOverallOrderDriverID[ix] = ix;
		ptr++;
		ix = ix + 1;
	} while (ptr < (int *)(*(&g_rallyOverallTimesRaw + 1) - g_rallyOverallTimesRaw));
}
