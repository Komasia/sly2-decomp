struct R { int n0; void *p4; void *p8; int nC; };
struct S { char pad[0x194]; void *p194; int a198[1]; };
void ClearSmaHandle__FPP3SMA(void *p);
void RetractAsegaPp__FPP5ASEGA(void *pp);
void ApplyAsegCur(void *paseg, struct S *p, float t, float svt, int grf, void *pp) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
void ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(void *a, struct S *p, int b, int c, void *d);
// name: SafeHouse port (PlayHackSeg)
void PlayHackSeg__FP2LOP6HACKSO(struct S *p, struct R *r) {
    ClearSmaHandle__FPP3SMA(p->a198);
    RetractAsegaPp__FPP5ASEGA(&p->p194);
    if (r) {
        ApplyAsegCur(r->p4, p, 0.0f, 1.0f, r->nC, &p->p194);
        ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(r->p8, p, -1, r->nC, p->a198);
    }
}
