/* func_0015ED78: the first object of a class found from ploCtx (CFindObjectsByClass for one, counting all), or 0. */
#include "h2_find.h"
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *psw, int grf, int cid, void *ploCtx, int cMax, void **aplo);
void *func_0015ED78(void *psw, int grf, int cid, void *ploCtx)
{
    void *plo;
    if (!CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(psw, grf | GRFFIND_CountAll, cid, ploCtx, 1, &plo))
        return 0;
    return plo;
}
