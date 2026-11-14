#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct O { int a, b, c; VTENT *vt; };
struct E { int pad[8]; qword q20; };
extern qword D_002A2DD0;
extern char D_002A2D00[];
struct O *PloAcquireProxyObject__FP2SWi(int, int);
void ReparentBooty__FP3ALOii(struct O *, int, int);
void FadeAloIn__FP3ALOf(struct O *, float);
// name: SafeHouse port (PloNewJtAura)
struct O *PloNewJtAura__FP2LOiP5JTENT(void *p, int id, struct E *pe) {
    struct O *po;
    if (!id) return 0;
    po = PloAcquireProxyObject__FP2SWi(id, 0);
    if (po) {
        ReparentBooty__FP3ALOii(po, 0, 0);
        { VTENT *e = &po->vt[9]; ((void (*)(void *))e->pfn)(VT_THIS(po, e)); }
        FadeAloIn__FP3ALOf(po, 0.25f);
        { VTENT *e = &po->vt[29]; ((void (*)(void *, qword))e->pfn)(VT_THIS(po, e), pe->q20); }
        { VTENT *e = &po->vt[30]; ((void (*)(void *, void *))e->pfn)(VT_THIS(po, e), D_002A2D00); }
        { VTENT *e = &po->vt[35]; ((void (*)(void *, qword))e->pfn)(VT_THIS(po, e), D_002A2DD0); }
        { VTENT *e = &po->vt[36]; ((void (*)(void *, qword))e->pfn)(VT_THIS(po, e), D_002A2DD0); }
    }
    return po;
}
