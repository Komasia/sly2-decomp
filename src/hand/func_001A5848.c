#include "vtbl.h"
struct VT { VTENT e[8]; };
struct S { int x0, x4, x8; struct VT *vt; char pad[0x18]; unsigned long x28; };
extern char g_sw[];
void func_001A00D0(void *g, struct S *s, int n);
void OnLoRemove__FP2LO(struct S *s)
{
    s->x28 &= ~0x1000000000000000UL;
    if (s->x28 & 0x0800000000000000UL)
        func_001A00D0(g_sw, s, 0);
    ((void (*)(void *, int, void *))s->vt->e[4].pfn)(VT_THIS(s, &s->vt->e[4]), 1, s);
}
