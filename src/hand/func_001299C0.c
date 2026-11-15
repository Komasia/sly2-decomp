/* CRef::SetProc: counts a reference to the lambda closure pproc (its first word is the reference count), drops
 * the old payload and makes the reference that closure. */
#include "splice.h"
// name: SafeHouse port (CRef::SetProc)
CRef *SetProc__4CRefP5CProc(CRef *pref, int *pproc)
{
    (*pproc)++;
    Decref__4CRef(pref);
    pref->m_tag.m_pv = pproc;
    pref->m_tagk = TAGK_Proc;
    return pref;
}
