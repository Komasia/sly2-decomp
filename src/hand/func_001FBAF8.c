#include "vtbl.h"
struct S { int a[3]; VTENT *vt; char pad[0x30]; int x40; char pad2[0xE]; short x52; };
void func_001FBAF8(int x, long l) { struct S *p = (struct S *)(int)l; p->x40 = x; p->x52 = 0; ((void (*)(void *))p->vt[2].pfn)(VT_THIS(p, &p->vt[2])); }
