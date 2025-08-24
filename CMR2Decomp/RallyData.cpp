#include "RallyData.h"

// GLOBAL: CMR2 0x0052f2ac
uint32_t g_selectedRallyData = 0;

// FUNCTION: CMR2 0x00406910
uint32_t RallyDataCountryIndex(void) {
	return g_selectedRallyData & 0x1f;
}

// FUNCTION: CMR2 0x00406930
uint32_t RallyDataStageIndex(void) {
	return g_selectedRallyData >> 5 & 0x1f;
}

// FUNCTION: CMR2 0x004074f0
uint32_t RallyDataState(void) {
	return g_selectedRallyData >> 0xe & 3;
}
