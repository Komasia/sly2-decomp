#include "vtbl.h"
struct S { char pad[0xC]; VTENT *vt; char p2[0x1F0]; int a; int b; };
extern char g_sw[];
void ApplyRsmg__FP2LOiP4RSMGii(void *g, int a, int *pb, struct S *p, int n);
void func_00181780(struct S *p)
{
    VTENT *e;
    ApplyRsmg__FP2LOiP4RSMGii(g_sw, p->a, &p->b, p, 1);
    e = &p->vt[3];
    ((void (*)(void *, int, int, int, int, int))e->pfn)(VT_THIS(p, e), 5, 0, 0, 0, 0);
}
