#include "vtbl.h"
struct O { int pad[3]; VTENT *vt; };
struct A { int f0; int f4; };
extern char g_sw[];
struct O *PloFindSwNearest__FP2LO3OIDii(void *, int, int, void *);
void func_00130010(void *p, void *q, struct A *pa, struct O **ppo, int *pn) {
    if (q) *ppo = PloFindSwNearest__FP2LO3OIDii(g_sw, 1, pa->f4, q);
    else *ppo = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, pa->f4, p);
    if (!*ppo) *pn = 0;
    else { struct O *po = *ppo; *pn = ((int (*)(void *, int))po->vt[43].pfn)(VT_THIS(po, &po->vt[43]), pa->f0); }
}
