/* RefEvalSymbol (SafeHouse eval.cpp): evaluates a symbol cell: the value bound to its symid in pframe (searching
 * the enclosing frames), nil when unbound. */
#include "splice.h"
int FFindBinding__6CFrameUiiP4CRef(CFrame *pframe, unsigned int symid, int fRecurse, CRef *pref);
// name: SafeHouse port (RefEvalSymbol)
CRef *RefEvalSymbol__FP5CPairP6CFrame(CRef *ret, CPair *ppair, CFrame *pframe)
{
    CRef ref;
    ref.m_tagk = TAGK_Nil;
    FFindBinding__6CFrameUiiP4CRef(pframe, ppair->m_ref.m_tag.m_symid, 1, &ref);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
