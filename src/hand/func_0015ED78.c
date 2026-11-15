/* PloFindSwObjectByClass__FP2SWi3CIDP2LO: the first object of a class found from ploCtx (CFindObjectsByClass for one, counting all), or 0. */
#include "h2_find.h"
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *psw, int grf, int cid, void *ploCtx, int cMax, void **aplo);
// name: Sly 1 find.c PloFindSwObjectByClass (CFindObjectsByClass with FSO_ReturnActualCount 0x200, one object)
void *PloFindSwObjectByClass__FP2SWi3CIDP2LO(void *psw, int grf, int cid, void *ploCtx)
{
    void *plo;
    if (!CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(psw, grf | GRFFIND_CountAll, cid, ploCtx, 1, &plo))
        return 0;
    return plo;
}
