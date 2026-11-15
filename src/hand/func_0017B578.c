/* JOBB1::State: 7 once landed, else 1. SafeHouse port (aihit.cpp "int JOBB1::State() { return stLaunch == 3 ? 7 : 1; }
 * // orig: 0x0017B578"). */
#include "h2_aijobs.h"
int func_0017B578(JOBB1 *pjob) { return pjob->stLaunch != LAUNCHS_Land ? 1 : 7; }
