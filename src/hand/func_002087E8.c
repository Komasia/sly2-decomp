#include "stepguard.h"
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
/* FTargetClass (0x2087E8): whether plo is of one of the guard's target classes. */
// name: SafeHouse port (FTargetClass)
int FTargetClass__FPvP2LO(struct GUARD *pguard, void *plo)
{
    int icid;
    for (icid = 0; icid < pguard->ccidTarget; icid++) {
        if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, pguard->acidTarget[icid])) return 1;
    }
    return 0;
}
