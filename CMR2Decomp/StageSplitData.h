#pragma once

#include <cstdint>

typedef struct StageSplitData {
	uint32_t split;
	uint32_t playerTime;
	uint32_t leaderTime;
	uint32_t currentStageTime;
	uint32_t splitHistory[12];
	uint32_t unknown; // this might not exist but im pretty sure this struct should be 0x44 in size
};
