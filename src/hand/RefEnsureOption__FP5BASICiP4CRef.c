/* RefEnsureOption (Sly 1 spliceobj.c): give the object a sidebag if it has none; if the sidebag already binds
 * iopt, overwrite the binding (RefSetBinding), otherwise add it (RefAddBinding). */
#include "so.h"
#include "splice.h"

typedef struct CSidebag CSidebag;
void EnsureBasicSidebag__FP5BASIC(BASIC *pbasic);
int FFindBinding__8CSidebagiP4CRef(CSidebag *psidebag, int iopt, CRef *pref);
CRef *RefSetBinding__8CSidebagiP4CRef(CRef *pref, CSidebag *psidebag, int iopt, CRef *prefValue);
CRef *RefAddBinding__8CSidebagiP4CRef(CRef *pref, CSidebag *psidebag, int iopt, CRef *prefValue);

CRef *RefEnsureOption__FP5BASICiP4CRef(CRef *pref, BASIC *pbasic, int iopt, CRef *prefValue)
{
    EnsureBasicSidebag__FP5BASIC(pbasic);
    if (FFindBinding__8CSidebagiP4CRef((CSidebag *)pbasic->psidebag, iopt, NULL)) {
        RefSetBinding__8CSidebagiP4CRef(pref, (CSidebag *)pbasic->psidebag, iopt, prefValue);
    } else {
        RefAddBinding__8CSidebagiP4CRef(pref, (CSidebag *)pbasic->psidebag, iopt, prefValue);
    }
    return pref;
}
