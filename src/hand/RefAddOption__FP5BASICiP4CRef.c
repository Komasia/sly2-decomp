/* RefAddOption (Sly 1 spliceobj.c): give the object a sidebag if it has none, then add the binding
 * (iopt, *prefValue) to it. Returns the CRef the sidebag hands back (g++ return slot first). */
#include "so.h"
#include "splice.h"

typedef struct CSidebag CSidebag;
void EnsureBasicSidebag__FP5BASIC(BASIC *pbasic);
CRef *RefAddBinding__8CSidebagiP4CRef(CRef *pref, CSidebag *psidebag, int iopt, CRef *prefValue);

CRef *RefAddOption__FP5BASICiP4CRef(CRef *pref, BASIC *pbasic, int iopt, CRef *prefValue)
{
    EnsureBasicSidebag__FP5BASIC(pbasic);
    RefAddBinding__8CSidebagiP4CRef(pref, (CSidebag *)pbasic->psidebag, iopt, prefValue);
    return pref;
}
