#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
void func_001C4228(struct O *p, int a, int b)
{
    void *apv[2];
    int n0, n1;
    /*B*/n0 = a; n1 = b; apv[0] = &n0; apv[1] = &n1;/*E*/
    { VTENT *e = &p->vt[3]; ((int (*)(void *, int, int, int, void **, int))e->pfn)(VT_THIS(p, e), 0xC, 0, 2, apv, 0); }
}
