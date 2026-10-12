/* near: DLI init variant - target never stores ppv=pdl (dli.ppv = first+ib), pdl copied s0->s1; tried InitDli/PvNextDli (33 diffs: extra dead store) */
typedef struct DL { void *pvFirst; void *pvLast; int ibDle; } DL;
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; void *m_pdliNext; } DLI;
extern void *D_002DD2FC;
struct VTE { short d; short pad; void (*pfn)(void *); };
struct LO { char pad[0xC]; struct VTE *vt; };
struct Y { char pad[0x1088]; void *p1088; };
struct FR { char pad[0x34]; DL dl34; DL dl40; };
extern char D_003E1530[];
extern char D_003E1518[];
int func_0011A3B0(DL *pdl);
void func_0011A2E8(DL *pdl, void *pv);
void func_0011A200(DL *pdl);
void func_0011CD98(void *pheap, void *pv);
static __inline__ void *PvInitDli(DLI *pdli, DL *pdl)
{
    int ib = pdl->ibDle;
    void *pv;
    pdli->m_pdliNext = D_002DD2FC;
    D_002DD2FC = pdli;
    pv = pdl->pvFirst;
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)((char *)pv + ib);
    pdli->m_ibDle = ib;
    return pv;
}
static __inline__ void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
void func_00160CE0(struct FR *pfr)
{
    DLI dli;
    DL *pdl = &pfr->dl34;
    if (!func_0011A3B0(pdl)) {
        struct LO *plo;
        for (plo = (struct LO *)PvInitDli(&dli, pdl); plo; plo = (struct LO *)PvNextDli(&dli)) {
            struct VTE *e;
            func_0011A2E8(pdl, plo);
            e = &plo->vt[2];
            e->pfn((char *)plo + e->d);
        }
        func_0011A200(pdl);
        D_002DD2FC = dli.m_pdliNext;
    }
    pdl = &pfr->dl40;
    if (!func_0011A3B0(pdl)) {
        struct Y *py;
        for (py = (struct Y *)PvInitDli(&dli, pdl); py; py = (struct Y *)PvNextDli(&dli)) {
            if (py->p1088)
                func_0011CD98(D_003E1530, py->p1088);
            func_0011A2E8(pdl, py);
            func_0011CD98(D_003E1518, py);
        }
        func_0011A200(pdl);
        D_002DD2FC = dli.m_pdliNext;
    }
}
