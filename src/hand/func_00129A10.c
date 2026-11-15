/* CRef::SetBasic: takes a script reference on the game object pbasic (if any) through its vtable slot 1, the
 * one Incref uses too, drops the old payload and makes the reference that object (null allowed). */
#include "vtbl.h"
#include "splice.h"
typedef struct BASIC { int pad[3]; VTENT *pvtbasic; } BASIC;
// name: SafeHouse port (CRef::SetBasic)
CRef *SetBasic__4CRefP5BASIC(CRef *pref, BASIC *pbasic)
{
    if (pbasic)
        ((void (*)(void *))pbasic->pvtbasic[1].pfn)(VT_THIS(pbasic, &pbasic->pvtbasic[1]));
    Decref__4CRef(pref);
    pref->m_tag.m_pbasic = pbasic;
    pref->m_tagk = TAGK_Basic;
    return pref;
}
