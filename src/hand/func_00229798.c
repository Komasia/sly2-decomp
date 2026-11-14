#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
struct N { struct O *po; int a; struct N *next; };
struct S { char pad[0x138]; struct N *first; };
// name: SafeHouse port (ApplyAloWater)
void ApplyAloWater__FP3ALO(struct S *p)
{
    struct N *n;
    for (n = p->first; n; n = n->next) {
        struct O *po = n->po;
        ((void (*)(void *, void *))po->vt[71].pfn)(VT_THIS(po, &po->vt[71]), n);
    }
}
