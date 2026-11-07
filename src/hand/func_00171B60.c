typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
struct VTE { short d; short pad; void (*pfn)(); };
struct T { char pad[0xC]; struct VTE *vt; char pad2[0x1A0]; char a1B0[0x10]; };
struct S { char pad[0x10]; struct T *pt; };
void DetachGuardMove__FP5GUARD(struct T *t);
void SetStepPhysHeading__FP3ALOf(struct T *t, float g);
// name: SafeHouse port (PlaceGuard)
void PlaceGuard__FP5GUARDG9VU_VECTORf(struct S *p, qword q, float g) {
    struct T *t = p->pt;
    struct VTE *e;
    DetachGuardMove__FP5GUARD(t);
    e = &t->vt[0x1D]; ((void (*)(void *, qword))e->pfn)((char *)t + e->d, q);
    SetStepPhysHeading__FP3ALOf(t, g);
    e = &t->vt[0x1E]; ((void (*)(void *, void *))e->pfn)((char *)t + e->d, t->a1B0);
    e = &t->vt[0x23]; ((void (*)(void *, qword))e->pfn)((char *)t + e->d, D_002A2DD0);
    e = &t->vt[0x24]; ((void (*)(void *, qword))e->pfn)((char *)t + e->d, D_002A2DD0);
}
