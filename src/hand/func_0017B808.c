struct S { char pad[0x10]; void *p10; char pad2[0x1C]; int n30; };
void Init__5AIJOB(struct S *p);
void AddGuardState__FP5GUARDi(void *p, int n);
// name: SafeHouse port (JOBB2::Init)
void Init__5JOBB2(struct S *p) { Init__5AIJOB(p); AddGuardState__FP5GUARDi(p->p10, 0x20); p->n30 = -1; }
