struct K { int a, b; };
struct S { char pad[0x164]; struct K k; };
void func_001A3968(struct S *p);
void func_001A3650(struct S *p, struct K *pk) { p->k = *pk; func_001A3968(p); }
