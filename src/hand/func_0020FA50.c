#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; };
struct S { int a; struct O *po; };
int func_0020FA10(void *pv, struct S *p);
int func_0020FA50(void *pv, struct S *p) { struct O *o; VTENT *e; if (!func_0020FA10(pv, p)) return 0; o = p->po; e = &o->vt[62]; return ((int (*)(void *))e->pfn)(VT_THIS(o, e)); }
