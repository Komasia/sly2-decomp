#include "common.h"
struct S { char pad[0xD0]; ulong fl; };
int func_001F2758(struct S *p) { return (int)(p->fl >> 34) & 1; }
