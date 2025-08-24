#include "Stage.h"

// GLOBAL: CMR2 0x00542cac
int8_t g_stageSplitCount = 0;


// FUNCTION: CMR2 0x004583c0
int32_t GetStageSplitCount(void)
{
	return g_stageSplitCount;
}
