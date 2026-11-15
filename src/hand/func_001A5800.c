/* OnLoAdd (0x1A5800): LO vt slot 11: the LO is in the world (bit 60 of +0x28), then the BASIC notification (vtable
 * slot 4) with 0 (added). SafeHouse activate.cpp OnAdd. */
#include "vtbl.h"
typedef unsigned long ulong;
struct O { char pad[0xC]; VTENT *vt; char pad2[0x18]; ulong fl; };
#define VT_NOTIFY 4
void OnLoAdd__FP2LO(struct O *plo)
{
    VTENT *e;
    plo->fl |= (ulong)1 << 60;
    e = &plo->vt[VT_NOTIFY];
    ((void (*)(void *, int, void *))e->pfn)(VT_THIS(plo, e), 0, plo);
}
