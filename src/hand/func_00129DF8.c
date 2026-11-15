/* CRef::Incref (Sly 1 ref.h): counts one more reference to the payload: the pooled vector / matrix / clq / lm /
 * smp node, the pair / closure / method (refcount first), or a game object through its vtable slot 1. */
#include "vtbl.h"
#include "splice_ref.h"
typedef struct BASIC { char pad[0xC]; VTENT *pvtbasic; } BASIC;
void Incref__4CRef(CRef *pref)
{
    switch (pref->m_tagk) {
    case TAGK_Matrix:
        ((REFMATRIX *)pref->m_tag.m_pv)->cref++;
        break;
    case TAGK_Vector:
    case TAGK_Clq:
        ((REFVECTOR *)pref->m_tag.m_pv)->cref++;
        break;
    case TAGK_Lm:
        ((REFLM *)pref->m_tag.m_pv)->cref++;
        break;
    case TAGK_Smp:
        ((REFSMP *)pref->m_tag.m_pv)->cref++;
        break;
    case TAGK_Basic: {
        BASIC *pbasic = pref->m_tag.m_pbasic;
        if (pbasic)
            ((void (*)(void *))pbasic->pvtbasic[1].pfn)(VT_THIS(pbasic, &pbasic->pvtbasic[1]));
        break;
    }
    case TAGK_Pair:
    case TAGK_Proc:
    case TAGK_Method:
        (*(int *)pref->m_tag.m_pv)++;
        break;
    }
}
