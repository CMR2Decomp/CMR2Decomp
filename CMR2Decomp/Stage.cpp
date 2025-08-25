#include "Stage.h"

// GLOBAL: CMR2 0x00542cac
char g_stageSplitCount = 0;


// FUNCTION: CMR2 0x004583c0
int GetStageSplitCount(void)
{
	return g_stageSplitCount;
}
