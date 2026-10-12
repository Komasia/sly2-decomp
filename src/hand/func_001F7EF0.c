#include "common.h"
struct S { char pad[0x148]; ulong a:16; int b:4; ulong c:44; };
int func_001F7EF0(struct S *p) { return p->b; }
