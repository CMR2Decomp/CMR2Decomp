#ifndef _STAGE_SPLIT_DATA_H
#define _STAGE_SPLIT_DATA_H

typedef struct StageSplitData {
	unsigned int split;
	unsigned int playerTime;
	unsigned int leaderTime;
	unsigned int currentStageTime;
	unsigned int splitHistory[12];
	unsigned int unknown; // this might not exist but im pretty sure this struct should be 0x44 in size
};

#endif
