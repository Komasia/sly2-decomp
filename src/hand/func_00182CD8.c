#include "vtbl.h"
struct S { char pad[0x20]; VTENT *vt; };
void func_00182CD8(struct S *p, int a, float *pg, int b, int c)
{
    float g;
    VTENT *e;
    e = &p->vt[2];
    ((void (*)(void *, int, float *))e->pfn)(VT_THIS(p, e), a, &g);
    e = &p->vt[3];
    ((void (*)(void *, int, int, int, float))e->pfn)(VT_THIS(p, e), a, b, c, g);
    if (pg) *pg = g;
}
