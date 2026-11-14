/* class: a splice built-in (BIF 100: its pointer in the BIF table g_mpbifkbif 0x2BBB90; SafeHouse bif.cpp
 * RefOpGlobalObject<100>, "object-3E0F9C"): the global object at 0x3E0F9C as an object CRef. */
#include "splice.h"
#include "so.h"

CRef *func_001294C0(CRef *pref, BASIC *pbasic);   /* the CRef of an object */
extern BASIC *D_003E0F9C;

CRef *func_00123AD0(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    func_001294C0(pref, D_003E0F9C);
    return pref;
}
