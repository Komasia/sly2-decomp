// ~60 diff: structure ok-ish; target reuses aref's s-reg for the list pointer, block layout differs
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
struct NODE { int cref; int x4; CRef ref; NODE *pnext; };
extern "C" CRef func_001238B0(void *pbasic, CRef *aref);
CRef func_001238B0(void *pbasic, CRef *aref)
{
    CRef ref(aref[0]);
    NODE *pn = (NODE *)aref;
    pn = pn->ref.m_tagk ? (NODE *)pn->ref.u.pv : 0;
    for (; pn; pn = pn->pnext) {
        if (ref.m_tagk == 0x15) {
            if (pn->ref.m_tagk == 0x15) {
                CRef *p = &pn->ref;
                if (ref.u.n > p->u.n)
                    ref = *p;
            } else {
                CRef *p = &pn->ref;
                if ((float)ref.u.n > p->u.g)
                    ref = *p;
            }
        } else {
            if (pn->ref.m_tagk == 0x15) {
                CRef *p = &pn->ref;
                if ((float)p->u.n < ref.u.g)
                    ref = *p;
            } else {
                CRef *p = &pn->ref;
                if (ref.u.g > p->u.g)
                    ref = *p;
            }
        }
    }
    return ref;
}
