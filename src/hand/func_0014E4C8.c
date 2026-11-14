/* Matched by Claude agent (2026-10-17): compare against the parameters directly (no local E copy) and `for (i = 0, pe = p->ae; ...)`. */
#include "vtbl.h"
struct O { int pad[3]; VTENT *vt; };
struct E { int prio; struct O *po; int a; int b; };
struct P { char pad[0x30C]; int c; struct E ae[8]; char pad2[0x390 - 0x390]; float t; };
#include "clock.h"
// name: SafeHouse port (RevokeCmPolicy)
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(struct P *p, int grf, int prio, struct O *po, int a, int b)
{
    struct E *peOut;
    struct E *pe;
    int i;
    struct O *poTop;
    int aTop;
    int bTop;
    poTop = 0;
    aTop = 0;
    bTop = 0;
    peOut = p->ae;
    for (i = 0, pe = p->ae; i < p->c; i++, pe++) {
        if ((((grf ^ 1) & 1) || prio == pe->prio) &&
            (!(grf & 2) || po == pe->po) &&
            (!(grf & 4) || a == pe->a) &&
            (!(grf & 8) || b == pe->b)) {
            if (i == 0) {
                poTop = pe->po;
                aTop = pe->a;
                bTop = pe->b;
            }
            {
                struct O *o = pe->po;
                VTENT *v = &o->vt[5];
                ((void (*)(void *, int))v->pfn)(VT_THIS(o, v), pe->b);
            }
        } else {
            *peOut++ = *pe;
        }
    }
    p->c = peOut - p->ae;
    if (poTop) {
        VTENT *v = &poTop->vt[3];
        ((void (*)(void *, int, int))v->pfn)(VT_THIS(poTop, v), aTop, bTop);
    if (p->c > 0) {
        struct O *o;
        VTENT *v;
        p->t = g_clock.t;
        o = p->ae[0].po;
        v = &o->vt[2];
        ((void (*)(void *, int, int))v->pfn)(VT_THIS(o, v), p->ae[0].a, p->ae[0].b);
    }
    }
}
