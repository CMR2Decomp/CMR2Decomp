#pragma once

#include <cstdint>

const char* g_minSecMSECFormatString = "%02d:%02d.%02d";

void __stdcall FormatCentisecondsAsMinSecMSec(int32_t iTime, char* pcFormattedTime);
