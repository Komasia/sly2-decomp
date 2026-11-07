/* RefCoerceF32__4CRef: the reference coerced to a float (Sly 1 CRef::RefCoerceF32): a float is copied, an integer
 * converted. */
#include "splice.h"

// name: SafeHouse port (CRef::RefCoerceF32)
CRef *RefCoerceF32__4CRef(CRef *pref, const CRef *prefSrc)
{
    if (prefSrc->m_tagk == TAGK_F32) {
        __4CRefRC4CRef(pref, prefSrc);
    } else {
        pref->m_tag.m_g = (float)prefSrc->m_tag.m_n;
        pref->m_tagk = TAGK_F32;
    }
    return pref;
}
