/* CRef::CRef(const CRef &) (0x1291A8, __4CRefRC4CRef): copies the tag kind and value and takes a reference. */
#include "splice.h"

void Incref__4CRef(CRef *pref);

CRef *__4CRefRC4CRef(CRef *pref, const CRef *prefSrc)
{
    pref->m_tagk = prefSrc->m_tagk;
    pref->m_tag = prefSrc->m_tag;
    Incref__4CRef(pref);
    return pref;
}
