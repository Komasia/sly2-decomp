#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct S { struct O *po; };
int func_001A2358(struct S *p, int a) { struct O *o = p->po; VTENT *e = &o->vt[86]; return ((int (*)(void *, int))e->pfn)(VT_THIS(o, e), a); }
