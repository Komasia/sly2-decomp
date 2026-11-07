typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x40]; qword q50; char pad3[8]; int n68; char pad4[0x240 - 0x6C]; qword pos; char pad5[0xFE8 - 0x250]; int nFE8; };
struct S { char pad[0x10]; struct O *p10; int pad2; char a18[0x18]; char a30[0x10]; };
void EndChildJob__FPP5AIJOB(void *p);
qword func_001A62E8(struct O *p);
qword PosGoal__FP4GOALG9VU_VECTOR(void *p, qword q);
int FDropOnGround__FP6VECTORffiPv(qword *pq, float a, float b, int n, void *pfn);
void FSnapPosToSurfaceAbove__FP6VECTOR(qword *pq);
struct O *func_00205438(struct O *p, int n);
void DetachGuardMove__FP5GUARD(struct O *p);
// name: SafeHouse port (JOBNAVPOINT::Start)
void Start__11JOBNAVPOINT(struct S *p) {
    union { qword q; float a[4]; } u;
    EndChildJob__FPP5AIJOB(p->a18);
    u.q = PosGoal__FP4GOALG9VU_VECTOR(p->a30, func_001A62E8(p->p10));
    if (!FDropOnGround__FP6VECTORffiPv(&u.q, 150.0f, -250.0f, 1, 0)) FSnapPosToSurfaceAbove__FP6VECTOR(&u.q);
    if (p->p10->nFE8 & 1) {
        struct O *o = func_00205438(p->p10, 0xAC);
        struct VTE *e;
        o->q50 = u.q;
        o->n68 = 1;
        e = &o->vt[8];
        e->pfn((char *)o + e->d);
    } else {
        DetachGuardMove__FP5GUARD(p->p10);
        {
            struct O *o = p->p10;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(u.q) : "j"(u.q), "j"(o->pos));
            o->vt[29].pfn((char *)o + o->vt[29].d, u.q);
        }
        { struct O *o = p->p10; o->vt[35].pfn((char *)o + o->vt[35].d, D_002A2DD0); }
        { struct O *o = p->p10; o->vt[36].pfn((char *)o + o->vt[36].d, D_002A2DD0); }
    }
}
