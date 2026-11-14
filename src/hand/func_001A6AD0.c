#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
void func_001A6AD0(struct O *p, int a) { VTENT *e = &p->vt[41]; ((void (*)(void *, int))e->pfn)(VT_THIS(p, e), a); }
