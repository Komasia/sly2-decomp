/* CRef::operator=(const CRef &) (0x129658): takes a reference on the source before dropping the old value (so
 * self-assignment is safe), then copies the tag kind and value. */
#include "splice.h"

void Incref__4CRef(const CRef *pref);

CRef *__as__4CRefRC4CRef(CRef *pref, const CRef *prefSrc)
{
    Incref__4CRef(prefSrc);
    Decref__4CRef(pref);
    pref->m_tagk = prefSrc->m_tagk;
    pref->m_tag = prefSrc->m_tag;
    return pref;
}
