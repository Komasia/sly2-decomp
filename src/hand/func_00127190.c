typedef struct CRef { int m_tagk; union { int n; float g; void *pv; } u; } CRef;
typedef struct LO { char pad[0x10]; struct LO *pnext; } LO;
typedef struct BASIC { char pad[0x18]; LO *plo; } BASIC;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
CRef *__as__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
CRef *RefEval__FP5CPairP6CFrame(CRef *ret, LO *plo, CRef *aref);
// name: Sly 1 eval.cpp RefEvalLambdaBody (evaluates the body expressions, keeps the last; called by RefEvalApply for a proc); SafeHouse eval.h RefEvalLambdaBody(CProc*, CFrame*) 0x127190
CRef *RefEvalLambdaBody__FP5CProcP6CFrame(CRef *ret, BASIC *pbasic, CRef *aref)
{
    CRef ref;
    CRef refT;
    LO *plo;
    ref.m_tagk = -1;
    plo = pbasic->plo;
    do {
        RefEval__FP5CPairP6CFrame(&refT, plo, aref);
        __as__4CRefRC4CRef(&ref, &refT);
        Decref__4CRef(&refT);
        plo = plo->pnext;
    } while (plo);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
