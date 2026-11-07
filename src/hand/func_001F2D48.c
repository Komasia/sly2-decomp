typedef unsigned long ulong;
typedef struct DL { void *head; void *tail; int ibDle; } DL;
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; } DLI;
extern DLI *s_pdliFirst;
struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *pvt; char pad2[0x28 - 0x10]; ulong fl; };
struct E { char pad[0xDC]; int nDC; };
struct P { char pad[0x64]; DL dl; char pad2[0xE8 - 0x70]; struct E *pe; char pad3[0x12C - 0xEC]; float f12C; int n130; };
struct K { int a, b; };
struct G;
extern struct G g_sw;
extern struct K D_002A8270;
void OnLoRemove__FP2LO(struct P *);
void RemoveAloSoes__FP3ALO(struct P *);
void CancelDeferredCalls__FPvUiiii(struct G *, int, struct P *, struct K, int);
void SetAloRegion__FP3ALOP9NAVREGION(struct P *, int);
static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = s_pdliFirst;
    s_pdliFirst = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
void OnSoRemove__FP2SO(struct P *p)
{
    DLI dli;
    struct O *po;
    int n;
    OnLoRemove__FP2LO(p);
    RemoveAloSoes__FP3ALO(p);
    p->n130 = 0;
    p->f12C = 1.0f;
    n = 0;
    if (p->pe) n = p->pe->nDC;
    if (n) {
        CancelDeferredCalls__FPvUiiii(&g_sw, 3, p, D_002A8270, 0);
        SetAloRegion__FP3ALOP9NAVREGION(p, 0);
    }
    InitDli(&dli, &p->dl);
    while ((po = PvNextDli(&dli)) != 0 && !(po->fl & (1L << 56)))
        po->pvt[12].pfn((char *)po + po->pvt[12].d);
    s_pdliFirst = dli.m_pdliNext;
}
