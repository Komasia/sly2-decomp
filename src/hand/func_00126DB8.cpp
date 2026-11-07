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
struct NODE { int x0, x4; CRef ref; NODE *pnext; };
struct P { char pad[0xC]; struct { char pad[0x10]; NODE *pargs; } *pv; };
struct FRAME {
    int cref;
    ~FRAME();
};
struct SPF {
    FRAME *p;
    SPF() { p = 0; }
    ~SPF() { FRAME *pf = p; if (pf && --pf->cref == 0) delete pf; }
    void operator=(FRAME *pf);
};
extern "C" {
FRAME *PframeNew() asm("PframeNew__Fv");
CRef RefEval(NODE *p, FRAME *pframe) asm("RefEval__FP5CPairP6CFrame");
CRef RefAddBinding(FRAME *pframe, int sym, CRef *pref) asm("RefAddBinding__6CFrameUiP4CRef");
void SetSingleParent(FRAME *pframe, FRAME *pframeParent) asm("SetSingleParent__6CFrame");
CRef RefEvalLet(P *p, FRAME *pframe) asm("RefEvalLet__FP5CPairP6CFrame");
}
// name: SafeHouse port (RefEvalLet)
CRef RefEvalLet(P *p, FRAME *pframe)
{
    CRef ref;
    CRef refVal;
    CRef refT;
    SPF spf;
    NODE *pargs = p->pv->pargs;
    NODE *pn;
    if (pargs->ref.m_tagk == 0x1F) {
        FRAME *pfNew = PframeNew();
        spf = pfNew;
        for (pn = (NODE *)pargs->ref.u.pv; pn; pn = pn->pnext) {
            NODE *pb = (NODE *)pn->ref.u.pv;
            refVal = RefEval(pb->pnext, pframe);
            refT = RefAddBinding(spf.p, pb->ref.u.n, &refVal);
        }
        SetSingleParent(spf.p, pframe);
    } else {
        spf = pframe;
    }
    NODE *pq;
    for (pq = pargs->pnext; pq; pq = pq->pnext)
        ref = RefEval(pq, spf.p);
    return ref;
}
