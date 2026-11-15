/* CRef::CRef(CProc *): constructs a lambda-closure reference to pproc and counts the new reference
 * (a CProc starts with its reference count). */
#include "splice.h"
CRef *func_001294A0(CRef *ret, int *pproc)
{
    ret->m_tag.m_pv = pproc;
    ret->m_tagk = TAGK_Proc;
    (*pproc)++;
    return ret;
}
