#ifndef _RALLY_TIMING_H
#define _RALLY_TIMING_H

int __stdcall RallyTiming_GetOverallPositionDriverID(int iPosition);
int __stdcall RallyTiming_GetOverallTimeForPosition(int iPosition);
void RallyTiming_ResetOverallPlayerTimes(void);

#endif
