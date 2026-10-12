struct K { int a, b; };
struct S { char pad[0x1C]; struct K k; };
void func_001A15B0(struct S *p, struct K k) { p->k = k; }
