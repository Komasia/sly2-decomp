#include "vtbl.h"
struct S { char pad[0xC]; VTENT *vt; char pad2[0xBC]; int a[10]; };
void func_00212880(struct S *p, int n, int *src)
{
    int i;
    for (i = 0; i < n && (unsigned)i < 10; i++)
        p->a[i] = src[i];
    ((void (*)(void *, int))p->vt[49].pfn)(VT_THIS(p, &p->vt[49]), -1);
}
