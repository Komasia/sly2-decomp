struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(float g);
};
struct Q { char pad[0x10]; Q *pnext; };
struct R { char pad[0x10]; Q *pq; };
struct P { char pad[0xC]; R *pr; };
extern "C" {
CRef RefEval(Q *pq, CRef *aref) asm("RefEval__FP5CPairP6CFrame");
CRef RefEvalWhile(P *p, CRef *aref) asm("RefEvalWhile__FP5CPairP6CFrame");
}
// name: SafeHouse port (RefEvalWhile)
CRef RefEvalWhile(P *p, CRef *aref)
{
    CRef ref;
    Q *pqCond = p->pr->pq;
    Q *pqBody = pqCond->pnext;
    for (;;) {
        ref = RefEval(pqCond, aref);
        if (ref.m_tagk == 0x17 && ref.u.n == 0)
            break;
        ref = RefEval(pqBody, aref);
    }
    ref.Decref();
    ref.InitTag(0x24);
    return ref;
}
