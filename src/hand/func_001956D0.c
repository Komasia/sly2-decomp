typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a, b, c; struct VTE *vt; };
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
        { struct VTE *e = &po->vt[9]; ((void (*)(void *))e->pfn)((char *)po + e->d); }
        FadeAloIn__FP3ALOf(po, 0.25f);
        { struct VTE *e = &po->vt[29]; ((void (*)(void *, qword))e->pfn)((char *)po + e->d, pe->q20); }
        { struct VTE *e = &po->vt[30]; ((void (*)(void *, void *))e->pfn)((char *)po + e->d, D_002A2D00); }
        { struct VTE *e = &po->vt[35]; ((void (*)(void *, qword))e->pfn)((char *)po + e->d, D_002A2DD0); }
        { struct VTE *e = &po->vt[36]; ((void (*)(void *, qword))e->pfn)((char *)po + e->d, D_002A2DD0); }
    }
    return po;
}
