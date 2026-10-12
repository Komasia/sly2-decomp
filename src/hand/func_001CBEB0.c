struct S { char pad[0x4A4]; int f; };
void func_00205EB8(struct S *p);
void func_001CBEB0(struct S *p) { func_00205EB8(p); p->f = 1; }
