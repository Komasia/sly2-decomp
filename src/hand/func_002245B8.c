#include "vtbl.h"
struct S { int a[3]; VTENT *vt; char pad[0x14C]; int k; };
void func_002245B8(struct S *p)
{
    if (p->k == 11) ((void (*)(void *, int))p->vt[76].pfn)(VT_THIS(p, &p->vt[76]), 5);
    else ((void (*)(void *, int))p->vt[76].pfn)(VT_THIS(p, &p->vt[76]), 3);
}
