#include "RallyData.h"

// GLOBAL: CMR2 0x0052f2ac
unsigned int g_selectedRallyData = 0;

// FUNCTION: CMR2 0x00406910
unsigned int RallyDataCountryIndex(void) {
	return g_selectedRallyData & 0x1f;
}

// FUNCTION: CMR2 0x00406930
unsigned int RallyDataStageIndex(void) {
	return g_selectedRallyData >> 5 & 0x1f;
}

// FUNCTION: CMR2 0x004074f0
unsigned int RallyDataState(void) {
	return g_selectedRallyData >> 0xe & 3;
}
