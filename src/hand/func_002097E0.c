#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; };
void func_002097E0(struct O **pp) { struct O *o = *pp; if (o) { VTENT *e = &o->vt[11]; ((void (*)(void *))e->pfn)(VT_THIS(o, e)); } }
