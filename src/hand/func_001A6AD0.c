/* func_001A6AD0 (0x1A6AD0): calls the object's vtable entry 41 with an int. */
#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
void func_001A6AD0(struct O *plo, int n) { VTENT *e = &plo->vt[41]; ((void (*)(void *, int))e->pfn)(VT_THIS(plo, e), n); }
