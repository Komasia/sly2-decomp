#include "vtbl.h"
struct S { int a[3]; VTENT *vt; char pad[0x140]; int x; };
// name: SafeHouse port (FAcceptCarryContact)
int FAcceptCarryContact__FP3ALO(struct S *p)
{
    switch (p->x) { case 1: case 2: ((void (*)(void *, int))p->vt[76].pfn)(VT_THIS(p, &p->vt[76]), 3); }
    return 1;
}
