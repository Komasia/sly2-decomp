#include "vtbl.h"
struct S { char pad[0xC]; VTENT *vt; };
void func_001F36A8(struct S *p);
// name: SafeHouse port (PostLoadHackSoBase)
void PostLoadHackSoBase__FP2LO(struct S *p) { VTENT *e; func_001F36A8(p); e = &p->vt[0x53]; ((void (*)(void *))e->pfn)(VT_THIS(p, e)); }
