#include "common.h"
struct T { char pad[0x10]; ulong fl; };
struct S { char pad[0x28]; ulong fl; };
void RemoveSoeFromOxa__FP3ALOP3SOE(struct S *, struct T *);
// name: SafeHouse port (SetSoeOff)
void SetSoeOff__FP3ALOP3SOE(struct S *p, struct T *pt)
{
    if (!(pt->fl & (1UL << 50))) {
        pt->fl |= 1UL << 50;
        if ((int)(p->fl >> 60) & 1) RemoveSoeFromOxa__FP3ALOP3SOE(p, pt);
    }
}
