/* LockGuardActivation: an AI job holds the guard: the first lock keeps it active (0x1A6CA8 with 1, SafeHouse: its
 * root's state set); UnlockGuardActivation (0x20B478) undoes it. Layout: SafeHouse port (guard.h GUARD). */
#include "stepguard.h"
void func_001A6CA8(struct GUARD *pguard, int fActive);

// name: SafeHouse port (LockGuardActivation)
int LockGuardActivation__FP5GUARDi(struct GUARD *pguard)
{
    if (pguard->cActivationLocks == 0)
        func_001A6CA8(pguard, 1);
    return ++pguard->cActivationLocks;
}
