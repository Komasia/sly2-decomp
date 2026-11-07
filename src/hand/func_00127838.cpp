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
    case 0x18:
        return RefEvalSymbol(p, aref);
    case 0x1F: {
        NODE *pn = (NODE *)p->ref.u.pv;
        switch (pn->ref.m_tagk) {
        case 1: return RefEvalSet(p, aref);
        case 2: return RefEvalDefine(p, aref);
        case 5: return RefEvalAssert(p, aref);
        case 6: return RefEvalDebug(p, aref);
        case 7: return RefEvalIf(p, aref);
        case 8: return RefEvalOr(p, aref);
        case 9: return RefEvalAnd(p, aref);
        case 10: return RefEvalCond(p, aref);
        case 12: return RefEvalCase(p, aref);
        case 13: return RefEvalLet(p, aref);
        case 14: return RefEvalWhile(p, aref);
        case 16: return RefEvalBegin(p, aref);
        case 15: return RefEvalLambda(p, aref);
        case 18: return pn->px10->ref;
        case 17: return CRef(-1);
        }
        return RefEvalApply(p, aref);
    }
    }
}
