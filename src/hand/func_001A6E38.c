typedef unsigned long ulong;
struct S { char pad[0x28]; ulong fl; };
void func_001A6E38(struct S *p, int f) { p->fl = (p->fl & ~((ulong)1 << 58)) | ((ulong)(f & 1) << 58); }
