/* v4 (Claude agent): 87/98 by count but only ~4 real diffs: InitDli loading ib first removes the dead dli.ppv store. Missing: target keeps pdl in s0 for the test/InitDli and a copy in s1 for the loop calls (daddu s1,s0 after the g store; block 2 computes a0 then s1=a0), which shifts everything by 2. */
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
static __inline__ void InitDli(DLI *pdli, DL *pdl)
{
    int ib = pdl->ibDle;
    pdli->m_pdliNext = D_002DD2FC;
    D_002DD2FC = pdli;
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = ib;
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
        InitDli(&dli, pdl);
        for (plo = PvNextDli(&dli); plo; plo = PvNextDli(&dli)) {
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
        InitDli(&dli, pdl);
        for (py = PvNextDli(&dli); py; py = PvNextDli(&dli)) {
            if (py->p1088)
                func_0011CD98(D_003E1530, py->p1088);
            func_0011A2E8(pdl, py);
            func_0011CD98(D_003E1518, py);
        }
        func_0011A200(pdl);
        D_002DD2FC = dli.m_pdliNext;
    }
}
