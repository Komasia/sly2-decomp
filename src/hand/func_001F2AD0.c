#include "common.h"
struct T { char pad[0x10]; ulong fl; };
struct S { char pad[0x28]; ulong fl; };
void func_001F2930(struct S *, struct T *);
void func_001F2AD0(struct S *p, struct T *pt)
{
    if (!(pt->fl & (1UL << 50))) {
        pt->fl |= 1UL << 50;
        if ((int)(p->fl >> 60) & 1) func_001F2930(p, pt);
    }
}
