struct S { char pad[0x10]; void *p10; char pad2[0x1C]; int n30; };
void func_001EEF68(struct S *p);
void AddGuardState__FP5GUARDi(void *p, int n);
void func_0017A6F8(struct S *p) { func_001EEF68(p); AddGuardState__FP5GUARDi(p->p10, 0x16); p->n30 = -1; }
