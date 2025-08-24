#pragma once

#include <cstdint>

// GLOBAL: CMR2 0x00519f58
const char* g_minSecMSECFormatString = "%02d:%02d.%02d";

void __stdcall FormatCentisecondsAsMinSecMSec(int32_t iTime, char* pcFormattedTime);
