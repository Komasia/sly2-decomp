#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
void func_001A5D08(struct O *p) { VTENT *e = &p->vt[9]; ((void (*)(void *))e->pfn)(VT_THIS(p, e)); }
