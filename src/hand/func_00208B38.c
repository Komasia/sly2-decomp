/* func_00208B38 (0x208B38): whether plo is of one of the guard's immediate classes. */
#include "stepguard.h"
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
int func_00208B38(struct GUARD *pguard, void *plo)
{
    int icid;
    for (icid = 0; icid < pguard->ccidImmediate; icid++) {
        if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, pguard->acidImmediate[icid])) return 1;
    }
    return 0;
}
