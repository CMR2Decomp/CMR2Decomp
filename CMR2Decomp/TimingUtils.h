#ifndef _TIMING_UTILS_H
#define _TIMING_UTILS_H

const char *g_minSecMSECFormatString = "%02d:%02d.%02d";

void __stdcall FormatCentisecondsAsMinSecMSec(int iTime, char *pcFormattedTime);

#endif
