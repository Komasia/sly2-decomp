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
struct Q { char pad[0x10]; void *pv; };
struct P { char pad[0xC]; Q *pq; };
extern "C" {
CRef RefEval(void *pv, CRef *aref) asm("RefEval__FP5CPairP6CFrame");
CRef RefEvalDebug(P *p, CRef *aref) asm("RefEvalDebug__FP5CPairP6CFrame");
}
// name: SafeHouse port (RefEvalDebug)
CRef RefEvalDebug(P *p, CRef *aref) { CRef ref; void *pv = p->pq->pv; if (pv) { ref = RefEval(pv, aref); } else { ref.Decref(); ref.InitTag(0x24); } return ref; }
