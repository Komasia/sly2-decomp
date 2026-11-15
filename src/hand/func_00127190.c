/* RefEvalLambdaBody: evaluates a lambda's body expressions in order in pframe and returns the last value. */
#include "splice.h"
typedef struct CProc { char pad[0x18]; CPair *ppairBody; } CProc;   /* 0x18: the body expression list */
CRef *__as__4CRefRC4CRef(CRef *pref, const CRef *prefSrc);
CRef *RefEval__FP5CPairP6CFrame(CRef *ret, CPair *ppair, CFrame *pframe);
// name: Sly 1 eval.cpp RefEvalLambdaBody (evaluates the body expressions, keeps the last; called by RefEvalApply for a proc); SafeHouse eval.h RefEvalLambdaBody(CProc*, CFrame*) 0x127190
CRef *RefEvalLambdaBody__FP5CProcP6CFrame(CRef *ret, CProc *pproc, CFrame *pframe)
{
    CRef ref;
    CRef refT;
    CPair *ppair;
    ref.m_tagk = TAGK_Nil;
    ppair = pproc->ppairBody;
    do {
        RefEval__FP5CPairP6CFrame(&refT, ppair, pframe);
        __as__4CRefRC4CRef(&ref, &refT);
        Decref__4CRef(&refT);
        ppair = ppair->m_ppairNext;
    } while (ppair);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
