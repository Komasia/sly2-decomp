#include "common.h"
struct S { char pad[0x148]; ulong a:20; int b:4; ulong c:40; };
int func_001F2740(struct S *p) { return p->b; }
