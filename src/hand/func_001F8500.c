#include "common.h"
struct S { char pad[0x148]; ulong fl; };
int func_001F8500(struct S *p) { return (int)(p->fl >> 33) & 1; }
