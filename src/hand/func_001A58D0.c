#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
// name: SafeHouse port (ReparentBooty)
void ReparentBooty__FP3ALOii(struct O *p, int a, int b) { VTENT *e = &p->vt[10]; ((void (*)(void *, int, int, int))e->pfn)(VT_THIS(p, e), a, 0, b); }
