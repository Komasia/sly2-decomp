#include "so.h"
struct LO;
struct P;
struct E { int x0; void *x4; int x8; struct LO *xC; qword x10; qword x20; qword x30; };
struct P { struct E e[2]; char pad[0x30]; qword xB0; };
qword VelXfPoint__FP2XFT0G9VU_VECTOR(void *p, int n, qword q);
void RecalcSwXpMovement__FP2SWiPP2XP(void *unused, int n, struct P **ap)
{
    int i;
    for (i = 0; i < n; i++) {
        struct P *p = ap[i];
        struct E *e;
        int j;
        e = p->e;
        for (j = 0; j < 2; j++, e++) {
            if (e->x4) {
                struct LO *o;
                e->x30 = VelXfPoint__FP2XFT0G9VU_VECTOR(e->x4, 0, e->x10);
                o = e->xC;
                ((void (*)(struct LO *, struct P *, int))o->pvt[56].pfn)((struct LO *)VT_THIS(o, &o->pvt[56]), p, j);
            }
        }
        for (j = 0; j < 2; j++) {
            struct LO *o = p->e[j].xC;
            if (o)
                ((void (*)(struct LO *, struct P *, int))o->pvt[57].pfn)((struct LO *)VT_THIS(o, &o->pvt[57]), p, j);
        }
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(p->xB0) : "j"(p->e[0].x30), "j"(p->e[1].x30));
    }
}
