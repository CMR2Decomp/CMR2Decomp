#include "RallyTiming.h"

// GLOBAL: CMR2 0x00533638
char g_rallyOverallOrderDriverID[16];

// GLOBAL: CMR2 0x00533658
int g_rallyOverallTimesRaw[32];

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
	int iVar1 = 0;
	int *puVar2 = g_rallyOverallTimesRaw;

	do
	{
		*puVar2 = 0;
		g_rallyOverallOrderDriverID[iVar1] = iVar1;
		puVar2 += 1;
		iVar1 += 1;
	} while (puVar2 < (int *)(0x00533698));
}
