#include "common.h"
struct T { char pad[0x70]; ulong fl; };
struct S { char pad[0xEC]; struct T *pt; };
// name: SafeHouse port (FAloOutOfSweep)
int FAloOutOfSweep__FP3ALO(struct S *p) { if (!p->pt) return 1; return (int)((long)(p->pt->fl << 30) >> 32) & 1; }
