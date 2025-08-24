#include "RallyTiming.h"

// GLOBAL: CMR2 0x00533638
int8_t g_rallyOverallOrderDriverID[16];

// GLOBAL: CMR2 0x00533658
int32_t g_rallyOverallTimesRaw[32];

// FUNCTION: CMR2 0x0040d390
int32_t __stdcall RallyTiming_GetOverallPositionDriverID(int32_t iPosition) {
	return g_rallyOverallOrderDriverID[iPosition];
}

// FUNCTION: CMR2 0x0040d3b0
int32_t RallyTiming_GetOverallTimeForPosition(int32_t iPosition) {
	uint32_t rawTime = g_rallyOverallTimesRaw[g_rallyOverallOrderDriverID[iPosition]];
	return 2200;
}
