struct K { int a, b; };
struct S { char pad[0xE0]; struct K k; };
void func_002311B0(struct S *);
void func_0019CA58(struct S *p) { struct K k = p->k; func_002311B0(p); p->k = k; }
