/* The dart fired (SafeHouse gang.cpp, orig 0x1357C0): aimed (FireBentleyDart), an instance of the dart proxy
 * (+0x16DC when +0x16D8 is 0, +0x16E0 when 1) with contact kind grf (its +0xE4 +0x18); the launcher +0x16E4 aimed at
 * the point (+0x60 none, +0x50 the point) throws it (0x1D6B00), no spin (vt slot 36), its flight over within 4 s; the
 * second state machine 1 (the reload), +0x1700 the time. */
#include "vtbl.h"
typedef int ti128 __attribute__((mode(TI)));
struct SOE { char pad[0x18]; int grf; };
struct LO { int pad[3]; VTENT *vt; char pad2[0xe4 - 0x10]; struct SOE *psoe; };
struct LAUNCHER { char pad[0x50]; ti128 posTarget; int ploTarget; };
struct BENTLEY { char pad[0x16d8]; int kDart; void *pproxyDart0; void *pproxyDart1; struct LAUNCHER *plauncher; ti128 posDartAim; float tDart; };
extern ti128 D_002A2DD0;   /* the zero vector */
extern float g_clock;      /* g_clock.t */
void FireBentleyDart__FP7BENTLEY(struct BENTLEY *pbentley);
struct LO *PloAcquireProxyObject__FP2SWi(void *pproxy, int n);
void func_001D6B00(struct LAUNCHER *plauncher, struct LO *plo);
void ExpireIn__FP3ALOf(struct LO *plo, float dt);
void SetBentleyState2__FP7BENTLEYi(struct BENTLEY *pbentley, int state);
void func_001357C0(struct BENTLEY *pbentley, int grf)
{
    void *pproxy;
    struct LO *plo;
    struct LAUNCHER *plauncher;
    FireBentleyDart__FP7BENTLEY(pbentley);
    switch (pbentley->kDart) {
    case 0: pproxy = pbentley->pproxyDart0; break;
    case 1: pproxy = pbentley->pproxyDart1; break;
    default: return;
    }
    if (!pproxy) return;
    plo = PloAcquireProxyObject__FP2SWi(pproxy, 0);
    if (!plo) return;
    plo->psoe->grf = grf;
    plauncher = pbentley->plauncher;
    plauncher->ploTarget = 0;
    plauncher->posTarget = pbentley->posDartAim;
    func_001D6B00(plauncher, plo);
    ((void (*)(void *, ti128))plo->vt[36].pfn)(VT_THIS(plo, &plo->vt[36]), D_002A2DD0);
    ExpireIn__FP3ALOf(plo, 4.0f);
    SetBentleyState2__FP7BENTLEYi(pbentley, 1);
    pbentley->tDart = g_clock;
}
