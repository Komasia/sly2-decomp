/* FGuardFreeN (0x208D70): 0 while the guard is in one of the busy states (11 29 7 5 6 16 1 22 42), else nE64. */
#include "stepguard.h"
long func_00207A20(int st);   /* the state's mask bit */
// name: SafeHouse port (FGuardFreeN)
int FGuardFreeN__FP5GUARD(struct GUARD *pguard)
{
    long grfBusy = func_00207A20(0xB) | func_00207A20(0x1D) | func_00207A20(7) | func_00207A20(5) | func_00207A20(6)
           | func_00207A20(0x10) | func_00207A20(1) | func_00207A20(0x16) | func_00207A20(0x2A);
    if (grfBusy & pguard->grfState)
        return 0;
    return pguard->nE64;
}
