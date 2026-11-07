struct O { char pad[0xE4]; int nE4; };
struct S { char pad[0x30]; struct O *p30; int n34; float g38; };
extern float D_002BE7B8;
float SMaxCrv__FP3CRV(struct O *p);
float SMinCrv__FP3CRV(struct O *p);
// name: SafeHouse port (JOBPATHSTEP::FAtEnd)
int FAtEnd__11JOBPATHSTEP(struct S *p) {
    float g;
    if (p->p30->nE4) return 0;
    if (p->n34) g = SMaxCrv__FP3CRV(p->p30); else g = SMinCrv__FP3CRV(p->p30);
    if (D_002BE7B8 < __builtin_fabsf(p->g38 - g)) return 0;
    return 1;
}
