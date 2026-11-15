/* func_001ADE38 (0x1ADE38): a HUD widget shows its screen object (+0x24; its vtable entry 49 with -1). */
#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct S { char pad[0x24]; struct O *po; };
void func_001ADE38(struct S *p) { struct O *o = p->po; if (o) { VTENT *e = &o->vt[49]; ((void (*)(void *, int))e->pfn)(VT_THIS(o, e), -1); } }
