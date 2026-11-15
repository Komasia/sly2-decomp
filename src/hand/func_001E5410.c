
#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct S { char pad[0x58]; struct O *po; int n5C; };
void RemoveLoListener__FP2LOi(struct O *po, struct S *p);
// name: SafeHouse port (RUN::ReleaseSmaWatch)
void ReleaseSmaWatch__3RUN(struct S *p)
{
    if (p->po) {
        RemoveLoListener__FP2LOi(p->po, p);
        { struct O *po = p->po; ((void (*)(void *))po->vt[2].pfn)(VT_THIS(po, &po->vt[2])); }
        p->po = 0;
        p->n5C = 0;
    }
}
