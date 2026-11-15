/* RefCoerceS32__4CRef: the reference coerced to an integer (Sly 1 CRef::RefCoerceS32): an integer is copied, a
 * float truncated. */
#include "splice.h"
// name: SafeHouse port (CRef::RefCoerceS32)
CRef *RefCoerceS32__4CRef(CRef *pref, const CRef *prefSrc)
{
    if (prefSrc->m_tagk == TAGK_S32) {
        __4CRefRC4CRef(pref, prefSrc);
    } else {
        float g = prefSrc->m_tag.m_g;
        pref->m_tagk = TAGK_S32;
        pref->m_tag.m_n = (int)g;
    }
    return pref;
}
