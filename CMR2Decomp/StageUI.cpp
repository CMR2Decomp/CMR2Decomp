#include "StageUI.h"

// GLOBAL: CMR2 0x00517e14
char g_positiveSymbol[2] = "+";

// GLOBAL: CMR2 0x00517e18
char g_negativeSymbol[2] = "-";

// STUB: CMR2 0x00415bd0
void FormatGapToLeader(int iLeaderGap, unsigned int param_2, unsigned char param_3, int param_4, int param_5, void *param_6, unsigned int param_7, char *pcNegPosSymbol, int param_9)
{
}

// FUNCTION: CMR2 0x00415db0
void PrepareFormatGapToLeader(int iLeaderGap, unsigned char param_2, unsigned int param_3, unsigned char param_4, int param_5, int param_6, void *param_7, unsigned int param_8, BOOL bIsAhead, int param_10)
{
    if (bIsAhead)
    {
        FormatGapToLeader(iLeaderGap, param_3, param_4, param_5, param_6, param_7, param_8, g_negativeSymbol, param_10);
        return;
    }

    FormatGapToLeader(iLeaderGap, param_3, param_4, param_5, param_6, param_7, param_8, g_positiveSymbol, param_10);
}
