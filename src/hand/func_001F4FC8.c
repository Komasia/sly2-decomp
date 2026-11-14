#include "vtbl.h"
typedef unsigned long ulong;
struct VT { VTENT a[63]; };
struct X { char pad[0xC]; struct VT *pvt; char pad2[0x148 - 0x10]; ulong fl; };
#define VF(p) ((int (*)(void *))(p)->pvt->a[62].pfn)(VT_THIS((p), &(p)->pvt->a[62]))
// name: SafeHouse port (OverlapKindAlo)
int OverlapKindAlo__FP3ALOT0(struct X *pa, struct X *pb)
{
    if (((pa->fl & 0x4000000) || VF(pa)) && VF(pb)) return 1;
    return 0;
}
