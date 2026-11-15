/* func_001294C0: CRef constructor from an object: a non-null object is told through its
 * virtual slot 0 (vtable entry 1) that a script reference now holds it. */
#include "splice.h"
#include "so.h"

CRef *func_001294C0(CRef *pref, BASIC *pbasic)
{
    if (pbasic != NULL) {
        VTENT *pvt = pbasic->pvt;
        ((void (*)(void *))pvt[1].pfn)(VT_THIS(pbasic, &pvt[1]));
    }
    pref->m_tag.m_pbasic = pbasic;
    pref->m_tagk = TAGK_Basic;
    return pref;
}
