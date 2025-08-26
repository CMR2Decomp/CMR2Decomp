#include "TimingUtils.h"

#include <stdio.h>

// STRING: CMR2 0x00519f58
const char *g_minSecMSECFormatString = "%02d:%02d.%02d";

// FUNCTION: CMR2 0x004de170
void __stdcall FormatCentisecondsAsMinSecMSec(int iTime, char *pcFormattedTime)
{
	sprintf(pcFormattedTime, g_minSecMSECFormatString, iTime / 6000, (iTime % 6000) / 100, iTime % 100);
}

// FUNCTION: CMR2 0x0040d480
int __stdcall ConvertRawTimeToCentiseconds(int iTime)
{
	// TODO: actually make this correct because its way off. GHIDRA uses a CONCAT44 which i dont understand
	int iConvertedTime;
	iConvertedTime = iTime + 0x147;

	return ((((iConvertedTime >> 0x1f) << 0x10) | (iConvertedTime >> 0x10)) | (iConvertedTime * 0x10000)) / 0x28f5c28;
}
