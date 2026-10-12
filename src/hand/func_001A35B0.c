struct S { char pad[0xE0]; int xe0; };
void func_001A3B38(struct S *p);
void func_001A3968(struct S *p);
void func_001A35B0(struct S *p, int a) { func_001A3B38(p); p->xe0 = a; func_001A3968(p); }
