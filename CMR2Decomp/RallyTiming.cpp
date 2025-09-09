#include "RallyTiming.h"
#include "TimingUtils.h"

// GLOBAL: CMR2 0x00533638
char g_rallyOverallOrderDriverID[16];

// GLOBAL: CMR2 0x00533658
int g_rallyOverallTimesRaw[16];

// GLOBAL: CMR2 0x00533698
const int *unk0x533698 = (int *)g_rallyOverallTimesRaw[0] + 16;

// FUNCTION: CMR2 0x0040d390
int RallyTiming_GetOverallPositionDriverID(int iPosition)
{
	return g_rallyOverallOrderDriverID[iPosition];
}

// FUNCTION: CMR2 0x0040d3b0
int RallyTiming_GetOverallTimeForPosition(int iPosition)
{
	int iTime;

	iTime = g_rallyOverallTimesRaw[g_rallyOverallOrderDriverID[iPosition]];
	return ConvertRawTimeToCentiseconds(iTime);
}

// FUNCTION: CMR2 0x0040d100
void RallyTiming_ResetOverallPlayerTimes(void)
{
	int ix = 0;
	int *ptr = g_rallyOverallTimesRaw;

	do
	{
		*ptr = 0;
		g_rallyOverallOrderDriverID[ix] = ix;
		ix++;
	} while (++ptr < unk0x533698);
}
