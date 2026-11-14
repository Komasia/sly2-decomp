/* class: a splice built-in (BIF 102: its pointer in the BIF table g_mpbifkbif 0x2BBB90; SafeHouse bif.cpp
 * RefOpGlobalObject<102>, "object-3E0FA4"): the global object at 0x3E0FA4 as an object CRef. */
#include "splice.h"
#include "so.h"

CRef *func_001294C0(CRef *pref, BASIC *pbasic);   /* the CRef of an object */
extern BASIC *D_003E0FA4;

CRef *func_00123B30(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    func_001294C0(pref, D_003E0FA4);
    return pref;
}
