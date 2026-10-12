#include "common.h"
struct S { char pad[0x148]; ulong fl; };
int func_001F7F08(struct S *p) { return (int)((long)(p->fl << 3) >> 32) & 1; }
