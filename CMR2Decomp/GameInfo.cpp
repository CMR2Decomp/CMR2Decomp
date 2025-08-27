#include "GameInfo.h"

// GLOBAL: CMR2 0x0052afa0
GameInfo g_gameInfo;

// GLOBAL: CMR2 0x0052ea54
unsigned int g_gameRegion;

// FUNCTION: CMR2 0x004057f0
unsigned char GetGameLanguage(void)
{
    return g_gameInfo.field2_0x14 & 7;
}

// FUNCTION: CMR2 0x00405800
unsigned int GetGameRegion(void)
{
    return g_gameRegion;
}

// FUNCTION: CMR2 0x00405d80
unsigned char FUN_00405d80(void)
{
    return g_gameInfo.field2_0x14 >> 3 & 0x7f;
}
