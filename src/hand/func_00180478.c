struct T { char pad[0x60]; void *p60; };
struct S { char pad[0xEC]; struct T *pt; char p1[0xD0]; float t1c0; float g1c4; int n; };
#include "clock.h"
extern char g_sw[];
void RecalcSwOxfFilterForObject__FP2SWP2SO(void *g, struct S *p);
void func_00180478(struct S *p, int n)
{
    if (n != p->n) {
        p->n = n;
        if (p->pt->p60 == p) RecalcSwOxfFilterForObject__FP2SWP2SO(g_sw, p);
    }
    p->t1c0 = (p->g1c4 == 0.0f) ? 3.40282346638528859812e+38f : g_clock.t + p->g1c4;
}
