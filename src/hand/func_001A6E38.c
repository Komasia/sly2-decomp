/* func_001A6E38 (0x1A6E38): sets or clears bit 58 of the LO's +0x28 flags (func_001A6DC8 skips children with it). */
typedef unsigned long ulong;
struct S { char pad[0x28]; ulong fl; };
void func_001A6E38(struct S *plo, int f) { plo->fl = (plo->fl & ~((ulong)1 << 58)) | ((ulong)(f & 1) << 58); }
