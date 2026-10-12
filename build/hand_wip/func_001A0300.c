/* WIP 6/83: VF alloc of the vdiv/vmulq asm output (target vf2 = d's reg; ours vf1) + lw v0/v1 for e->x4. */
typedef int qword __attribute__((mode(TI)));
struct A;
typedef struct { short d; short pad; void (*pfn)(struct A *, float, float, qword *, int); } VT;
struct A { VT *vt; };
struct O { int x0; struct A *x4; };
struct K { char pad[0x74]; float x74; };
struct E { int x0; struct K *x4; int pad[2]; qword x10; };
struct O *func_0012FF10(struct K *k, void *p, int a, int b);
void func_00137A30(void *p, int cb, int c, struct E *ae, int a, int b, int d, int *pn);
void func_001A0300(void *p, struct E *ae, int *pn)
{
    struct E *e = ae;
    int i;
    union { qword q; float f; } v0, v1, t;
    int n;
    for (i = 0; i < 8; i++, e++) {
        if (e->x4) {
            struct O *o = func_0012FF10(e->x4, p, 1, 1);
            if (o) {
                qword d;
                o->x4->vt[3].pfn((struct A *)((char *)o->x4 + o->x4->vt[3].d), 0.0f, 1.0f, &v0.q, 0);
                o->x4->vt[3].pfn((struct A *)((char *)o->x4 + o->x4->vt[3].d), e->x4->x74, 1.0f, &v1.q, 0);
                __asm__("qmtc2.ni %1, %0" : "=j"(t.q) : "r"(*(int *)&e->x4->x74));
                __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(v0.q), "j"(v1.q));
                __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(e->x10) : "j"(t.q), "j"(d));
            }
        }
    }
    func_00137A30(p, 0x20, 8, ae, 0, 0, 0, &n);
    *pn = n;
}
