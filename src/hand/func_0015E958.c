/* func_0015E958: the first object of an oid found from ploCtx (CFindObjects for one, counting all), or 0. */
#include "h2_find.h"
int CFindObjects__FP2SWi3OIDP2LOPviPP2LO(void *psw, int grf, int oid, void *ploCtx, void *pnsn, int cMax, void **aplo);
void *func_0015E958(void *psw, int grf, int oid, void *ploCtx, void *pnsn)
{
    void *plo;
    if (!CFindObjects__FP2SWi3OIDP2LOPviPP2LO(psw, grf | GRFFIND_CountAll, oid, ploCtx, pnsn, 1, &plo))
        return 0;
    return plo;
}
