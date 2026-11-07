struct S { char pad[0x10]; void *p10; char pad2[0x1C]; int n30; int pad3; float g38; };
void Init__5AIJOB(struct S *p);
void AddGuardState__FP5GUARDi(void *p, int n);
// name: SafeHouse port (JOBRAIL::Init)
void Init__7JOBRAIL(struct S *p) { Init__5AIJOB(p); p->n30 = -1; p->g38 = 1.0f; AddGuardState__FP5GUARDi(p->p10, 0x1B); }
