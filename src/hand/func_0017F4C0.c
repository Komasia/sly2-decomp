struct R { int n0; void *p4; void *p8; int nC; };
struct S { char pad[0x194]; void *p194; int a198[1]; };
void func_001F15B8(void *p);
void RetractAsegaPp__FPP5ASEGA(void *pp);
void func_001305B8(void *paseg, struct S *p, float t, float svt, int grf, void *pp);
void func_001F1448(void *a, struct S *p, int b, int c, void *d);
// name: SafeHouse port (PlayHackSeg)
void PlayHackSeg__FP2LOP6HACKSO(struct S *p, struct R *r) {
    func_001F15B8(p->a198);
    RetractAsegaPp__FPP5ASEGA(&p->p194);
    if (r) {
        func_001305B8(r->p4, p, 0.0f, 1.0f, r->nC, &p->p194);
        func_001F1448(r->p8, p, -1, r->nC, p->a198);
    }
}
