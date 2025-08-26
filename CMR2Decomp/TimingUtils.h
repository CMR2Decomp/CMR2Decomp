#ifndef _TIMING_UTILS_H
#define _TIMING_UTILS_H

void __stdcall FormatCentisecondsAsMinSecMSec(int iTime, char *pcFormattedTime);
int __stdcall ConvertRawTimeToCentiseconds(int iTime);

#endif
