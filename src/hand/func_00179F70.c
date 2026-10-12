struct S { char pad[0x3C]; int n3C; };
void func_00174920(struct S *p);
void func_00179F70(struct S *p) { func_00174920(p); p->n3C = 0xF; }
