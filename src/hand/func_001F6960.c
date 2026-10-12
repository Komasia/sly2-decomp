#include "common.h"
struct S { char pad[0x148]; ulong fl; };
int func_001F6960(struct S *p) { return (int)((long)(p->fl << 6) >> 32) & 1; }
