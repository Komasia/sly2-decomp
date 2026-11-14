#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct T { char pad[0xFEC]; struct O *pFEC; };
struct S { char pad[0x10]; struct T *pt; };
void Exit__6JOBHIT(struct S *p);
void func_00179820(struct S *p) { struct O *o; Exit__6JOBHIT(p); o = p->pt->pFEC; if (o) { VTENT *e = &o->vt[9]; ((void (*)(void *))e->pfn)(VT_THIS(o, e)); } }
