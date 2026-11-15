#include "dl.h"
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; } DLI;
extern DLI *s_pdliFirst;
#include "clock.h"
#include "vtbl.h"
struct RIP { char pad[0x14]; float tStart; char p1[0xEC - 0x18]; VTENT *vt; };
struct RIPG { char pad[0xC]; VTENT *vt; char p1[0x15C - 0x10]; DL dl; };
void AddRipRef(struct RIP *prip) asm("AddRipRef__FP3RIP");
void ReleaseRip__FP3RIP(struct RIP *prip);
int FLoActive__FP2LO(struct RIPG *p);
int FIsDlEmpty__FP2DL(DL *pdl);
void BounceRipgRips__FP4RIPG(struct RIPG *p);
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
void FUN_0019e420(struct RIPG *pripg)
{
    DLI dli;
    struct RIP *prip;
    InitDli(&dli, &pripg->dl);
    while ((prip = (struct RIP *)PvNextDli(&dli)) != 0) {
        if (g_clock.t <= prip->tStart) continue;
        AddRipRef(prip);
        ((void (*)(void *))prip->vt[5].pfn)(VT_THIS(prip, &prip->vt[5]));
        ReleaseRip__FP3RIP(prip);
    }
    if (!FLoActive__FP2LO(pripg) || FIsDlEmpty__FP2DL(&pripg->dl))
        ((void (*)(void *))pripg->vt[9].pfn)(VT_THIS(pripg, &pripg->vt[9]));
    else
        BounceRipgRips__FP4RIPG(pripg);
    s_pdliFirst = dli.m_pdliNext;
}
