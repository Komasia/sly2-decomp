/* func_001A5D08 (0x1A5D08): a deferred callback (func_001A5D30 queues it): the object's vt slot 9, RemoveLo (option
 * 26's: SafeHouse update.cpp). */
#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
#define VT_REMOVE 9
void func_001A5D08(struct O *plo) { VTENT *e = &plo->vt[VT_REMOVE]; ((void (*)(void *))e->pfn)(VT_THIS(plo, e)); }
