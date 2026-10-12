struct S { char pad[0x3C]; int n3C; };
void func_00174920(struct S *p);
void func_00179868(struct S *p) { func_00174920(p); p->n3C = 7; }
