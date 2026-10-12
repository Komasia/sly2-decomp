#include "common.h"
struct S { char pad[0x148]; ulong fl; };
int func_001F7B40(struct S *p) { return (int)((long)(p->fl << 8) >> 32) & 3; }
