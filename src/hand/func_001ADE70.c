/* func_001ADE70 (0x1ADE70): a HUD widget hides its screen object (+0x24; its vtable entry 50). */
#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct S { char pad[0x24]; struct O *po; };
void func_001ADE70(struct S *p) { struct O *o = p->po; if (o) { VTENT *e = &o->vt[50]; ((void (*)(void *))e->pfn)(VT_THIS(o, e)); } }
