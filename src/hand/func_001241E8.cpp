/* BIF 113 find-objects: the list of objects with id aref[0], relative to aref[1] (kind 1) or global (5). */
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
struct Q { char pad[0x3C]; void *pv; };
struct W { char pad[0xC]; Q *pq; };
struct G { char pad[0x3F0C]; void *pv; };
extern G g_sw;
extern "C" {
int CFindObjects(G *pg, int k, void *a, Q *b, void *c, int n, void **ap) asm("CFindObjects__FP2SWi3OIDP2LOPviPP2LO");
CRef RefPairFromAplo__FiPP2LO(int c, void **ap);
CRef RefOpFindObjects__FiP4CRefP6CFrame(int carg, CRef *aref);
}
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 113: CFindObjects into a list, relative 1 / global 5)
CRef RefOpFindObjects__FiP4CRefP6CFrame(int carg, CRef *aref)
{
    CRef ref;
    void *ap[0x40];
    Q *pq = (Q *)aref[1].u.pv;
    Q *pqT;
    if (aref[2].m_tagk)
        pqT = ((W *)aref[2].u.pv)->pq;
    else
        pqT = pq;
    G *pg = &g_sw;
    int k = pq ? 1 : 5;
    void *p0 = aref[0].u.pv;
    void *pv;
    if (pqT)
        pv = pqT->pv;
    else
        pv = pg->pv;
    int c = CFindObjects(pg, k, p0, pq, pv, 0x40, ap);
    ref = RefPairFromAplo__FiPP2LO(c, ap);
    return ref;
}
