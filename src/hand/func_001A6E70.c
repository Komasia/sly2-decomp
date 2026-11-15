/* func_001A6E70 (0x1A6E70): bit 58 of the LO's +0x28 flags (see func_001A6E38). */
typedef unsigned long ulong;
struct S { char pad[0x28]; ulong fl; };
int func_001A6E70(struct S *plo) { return (int)(plo->fl >> 58) & 1; }
