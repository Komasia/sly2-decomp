/* PloFindSwObject__FP2SWi3OIDP2LOPv: the first object of an oid found from ploCtx (CFindObjects for one, counting all), or 0. */
#include "h2_find.h"
int CFindObjects__FP2SWi3OIDP2LOPviPP2LO(void *psw, int grf, int oid, void *ploCtx, void *pnsn, int cMax, void **aplo);
// name: Sly 1 find.c PloFindSwObject (CFindObjects with FSO_ReturnActualCount 0x200, one object; Sly 2 passes CFindObjects' extra pointer through); PloFindSwNearest calls it
void *PloFindSwObject__FP2SWi3OIDP2LOPv(void *psw, int grf, int oid, void *ploCtx, void *pnsn)
{
    void *plo;
    if (!CFindObjects__FP2SWi3OIDP2LOPviPP2LO(psw, grf | GRFFIND_CountAll, oid, ploCtx, pnsn, 1, &plo))
        return 0;
    return plo;
}
