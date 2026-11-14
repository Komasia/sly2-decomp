#include "vtbl.h"
struct O { int a[3]; VTENT *vt; char pad[0x140]; int k; };
struct Q { int a; struct O *o; };
void func_00133590(struct O *p, int k, struct Q *q);
// name: SafeHouse port (OnCarryMessage)
void OnCarryMessage__FP2LO5MSGIDPv(struct O *p, int k, struct Q *q)
{
    func_00133590(p, k, q);
    if (k == 4) {
        struct O *o = q->o;
        if (o == p && (unsigned)(o->k - 1) < 2) ((void (*)())o->vt[76].pfn)(VT_THIS(o, &o->vt[76]), 3);
    }
}
