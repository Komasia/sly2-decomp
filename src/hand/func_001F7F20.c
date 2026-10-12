#include "common.h"
struct S { char pad[0x148]; ulong a:29; int b:1; ulong c:34; };
void func_001F7F20(struct S *p, int n) { p->b = n; }
