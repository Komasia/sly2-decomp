struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct DLI { struct DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; };
extern struct DLI *s_pdliFirst;
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct E { char pad[0x4C]; float t; };
struct P { char pad[0x4118]; char pool[0x18]; struct DL dl; };
void RemoveDlEntry__FP2DLPv(struct DL *, void *);
void func_0011CD98(void *, void *);
static inline void InitDli(struct DLI *pdli, struct DL *pdl)
{
    pdli->pdl = pdl;
    pdli->ppv = (void **)pdl;
    pdli->ibDle = pdl->ibDle;
    pdli->pdliNext = s_pdliFirst;
    s_pdliFirst = pdli;
}
static inline void *PvNextDli(struct DLI *pdli)
{
    void *pv = *pdli->ppv;
    pdli->ppv = (void **)((char *)pv + pdli->ibDle);
    return pv;
}
void func_001F77C0(struct P *p)
{
    struct DLI dli;
    struct E *pe;
    InitDli(&dli, &p->dl);
    while ((pe = PvNextDli(&dli)) != 0) {
        if (g_clock.t < pe->t + 0.25f) continue;
        RemoveDlEntry__FP2DLPv(&p->dl, pe);
        func_0011CD98(p->pool, pe);
    }
    s_pdliFirst = dli.pdliNext;
}
