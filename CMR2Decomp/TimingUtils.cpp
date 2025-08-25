#include "TimingUtils.h"

#include <cstdio>

// FUNCTION: CMR2 0x004de170
void __stdcall FormatCentisecondsAsMinSecMSec(int iTime, char* pcFormattedTime) {
	sprintf(pcFormattedTime, g_minSecMSECFormatString, iTime / 6000, (iTime % 6000) / 100, iTime % 100);
}
