struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
typedef struct Q { char pad[0xC]; void *pv0C; void *pv10; } Q;
typedef struct R { char pad[0x10]; Q *pq; } R;
typedef struct P { char pad[0xC]; R *pr; } P;
extern "C" {
CRef RefEval(void *pv, CRef *aref) asm("RefEval__FP5CPairP6CFrame");
CRef RefSetBinding(CRef *aref, void *pv, CRef *pref) asm("RefSetBinding__6CFramePvP4CRef");
CRef RefEvalSet(P *p, CRef *aref) asm("RefEvalSet__FP5CPairP6CFrame");
}
// name: SafeHouse port (RefEvalSet)
CRef RefEvalSet(P *p, CRef *aref) { CRef ref; Q *pq = p->pr->pq; ref = RefEval(pq->pv10, aref); ref = RefSetBinding(aref, pq->pv0C, &ref); return ref; }
