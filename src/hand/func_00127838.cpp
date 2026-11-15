/* RefEval: evaluates one expression cell: self-evaluating values are returned as they are, symbols are looked up,
 * special forms dispatch to their RefEvalXxx, a list is an application (RefEvalApply). */
#include "splice_tagk.h"
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
struct NODE { int x0, x4; CRef ref; NODE *px10; };
extern "C" {
CRef RefEvalSymbol(NODE *p, CRef *aref) asm("RefEvalSymbol__FP5CPairP6CFrame");
CRef RefEvalSet(NODE *p, CRef *aref) asm("RefEvalSet__FP5CPairP6CFrame");
CRef RefEvalDefine(NODE *p, CRef *aref) asm("RefEvalDefine__FP5CPairP6CFrame");
CRef RefEvalAssert(NODE *p, CRef *aref) asm("RefEvalAssert__FP5CPairP6CFrame");
CRef RefEvalDebug(NODE *p, CRef *aref) asm("RefEvalDebug__FP5CPairP6CFrame");
CRef RefEvalIf(NODE *p, CRef *aref) asm("RefEvalIf__FP5CPairP6CFrame");
CRef RefEvalOr(NODE *p, CRef *aref) asm("RefEvalOr__FP5CPairP6CFrame");
CRef RefEvalAnd(NODE *p, CRef *aref) asm("RefEvalAnd__FP5CPairP6CFrame");
CRef RefEvalCond(NODE *p, CRef *aref) asm("RefEvalCond__FP5CPairP6CFrame");
CRef RefEvalCase(NODE *p, CRef *aref) asm("RefEvalCase__FP5CPairP6CFrame");
CRef RefEvalLet(NODE *p, CRef *aref) asm("RefEvalLet__FP5CPairP6CFrame");
CRef RefEvalWhile(NODE *p, CRef *aref) asm("RefEvalWhile__FP5CPairP6CFrame");
CRef RefEvalBegin(NODE *p, CRef *aref) asm("RefEvalBegin__FP5CPairP6CFrame");
CRef RefEvalLambda(NODE *p, CRef *aref) asm("RefEvalLambda__FP5CPairP6CFrame");
CRef RefEvalApply(NODE *p, CRef *aref) asm("RefEvalApply__FP5CPairP6CFrame");
CRef RefEval(NODE *p, CRef *aref) asm("RefEval__FP5CPairP6CFrame");
}
// name: SafeHouse port (RefEval)
CRef RefEval(NODE *p, CRef *aref)
{
    switch (p->ref.m_tagk) {
    default:
        return p->ref;
    case TAGK_Symid:
        return RefEvalSymbol(p, aref);
    case TAGK_Pair: {
        NODE *pn = (NODE *)p->ref.u.pv;
        switch (pn->ref.m_tagk) {
        case TAGK_Set: return RefEvalSet(p, aref);
        case TAGK_Define: return RefEvalDefine(p, aref);
        case TAGK_Assert: return RefEvalAssert(p, aref);
        case TAGK_Debug: return RefEvalDebug(p, aref);
        case TAGK_If: return RefEvalIf(p, aref);
        case TAGK_Or: return RefEvalOr(p, aref);
        case TAGK_And: return RefEvalAnd(p, aref);
        case TAGK_Cond: return RefEvalCond(p, aref);
        case TAGK_Case: return RefEvalCase(p, aref);
        case TAGK_Let: return RefEvalLet(p, aref);
        case TAGK_While: return RefEvalWhile(p, aref);
        case TAGK_Begin: return RefEvalBegin(p, aref);
        case TAGK_Lambda: return RefEvalLambda(p, aref);
        case TAGK_Quote: return pn->px10->ref;
        case TAGK_Import: return CRef(-1);
        }
        return RefEvalApply(p, aref);
    }
    }
}
