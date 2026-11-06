/* RefSetOption (Sly 1 spliceobj.c): options below 0x4D1 are the class's built-in options (EOPID table, found by
 * PeopidFind) and are written through RefSetPeopid; any other option lives in the object's sidebag. */
#include "so.h"
#include "splice.h"

typedef struct CSidebag CSidebag;
typedef struct EOPID EOPID;
EOPID *PeopidFind__FP5BASICi(BASIC *pbasic, int iopt);
CRef *RefSetPeopid__FP5BASICP5EOPIDP4CRef(CRef *pref, BASIC *pbasic, EOPID *peopid, CRef *prefValue);
CRef *RefSetBinding__8CSidebagiP4CRef(CRef *pref, CSidebag *psidebag, int iopt, CRef *prefValue);

CRef *RefSetOption__FP5BASICiP4CRef(CRef *pref, BASIC *pbasic, int iopt, CRef *prefValue)
{
    if (iopt < 0x4D1) {
        RefSetPeopid__FP5BASICP5EOPIDP4CRef(pref, pbasic, PeopidFind__FP5BASICi(pbasic, iopt), prefValue);
    } else {
        RefSetBinding__8CSidebagiP4CRef(pref, (CSidebag *)pbasic->psidebag, iopt, prefValue);
    }
    return pref;
}
