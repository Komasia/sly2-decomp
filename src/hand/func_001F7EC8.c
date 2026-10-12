#include "common.h"
struct S { char pad[0x148]; ulong a:16; int b:4; ulong c:44; };
void func_001F7EC8(struct S *p, int n) { p->b = n; }
