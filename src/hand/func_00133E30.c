#include "vtbl.h"
struct O { int pad[3]; VTENT *vt; };
struct Q { char pad[0x60]; struct O *po; };
struct S { char pad[0x3d28]; struct Q *pq; };
// name: SafeHouse port (FlushSwOxaDirty1)
void FlushSwOxaDirty1__FP2SW(struct S *p) {
    struct Q *pq;
    while ((pq = p->pq) != 0) {
        struct O *po = pq->po; VTENT *vt = po->vt;
        ((void (*)(void *))vt[49].pfn)(VT_THIS(po, &vt[49]));
    }
}
