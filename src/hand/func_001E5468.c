#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct S { char pad[0x64]; struct O *po; };
void func_001E5468(struct S *p)
{
    struct O *po = p->po;
    if (po) {
        ((void (*)(void *))po->vt[50].pfn)(VT_THIS(po, &po->vt[50]));
        p->po = 0;
    }
}
