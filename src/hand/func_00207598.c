/* func_00207598 (0x207598): GUARD vt slot 76, busy: +0x32C or +0x298 set, or in state 0x2A. */
#include "stepguard.h"
int FGuardState(struct GUARD *pguard, int st) asm("FGuardState__FP5GUARDi");
int func_00207598(struct GUARD *pguard) { if (pguard->f32C || pguard->step.nUnk298) return 1; return FGuardState(pguard, 0x2A) != 0; }
