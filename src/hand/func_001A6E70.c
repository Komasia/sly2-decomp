typedef unsigned long ulong;
struct S { char pad[0x28]; ulong fl; };
int func_001A6E70(struct S *p) { return (int)(p->fl >> 58) & 1; }
