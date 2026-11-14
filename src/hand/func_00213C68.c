#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct M { qword a, b; };
struct A { VTENT *vt; };
struct S { char pad[0xC4]; struct A *pa; char pad2[0x30]; struct M *pm; };
void func_00213C68(struct S *p, struct M *src)
{
    if (!p->pm) {
        struct A *a = p->pa;
        p->pm = ((struct M * (*)(void *, int, int))a->vt[1].pfn)(VT_THIS(a, &a->vt[1]), 0x20, 0x1F);
    }
    *p->pm = *src;
}
