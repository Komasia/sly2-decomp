#include "common.h"
struct S { char pad[0x148]; ulong a:20; int b:4; ulong c:40; };
void func_001F2718(struct S *p, int n) { p->b = n; }
