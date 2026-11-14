#include "vtbl.h"
struct S { int pad[3]; VTENT *vt; };
void func_00133340(struct S *p) { VTENT *vt = p->vt; ((void (*)(void *, int, int, int, int, int))vt[3].pfn)(VT_THIS(p, &vt[3]), 5, 0, 0, 0, 0); }
