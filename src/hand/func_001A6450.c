#include "vtbl.h"
struct O { int x0, x4, x8; VTENT *vt; };
void func_001A6450(struct O *o, void *arg)
{
    struct O **list;
    int n, i;
    VTENT *e = &o->vt[0xE0 / 8];
    n = ((int (*)(void *, struct O ***))e->pfn)(VT_THIS(o, e), &list);
    for (i = 0; i < n; i++) {
        struct O *p = list[i];
        VTENT *f = &p->vt[0x128 / 8];
        ((void (*)(void *, void *))f->pfn)(VT_THIS(p, f), arg);
    }
}
