struct S { char pad[0x10]; void *p10; char pad2[0x20]; int n34; };
void Init__5AIJOB(struct S *p);
void AddGuardState__FP5GUARDi(void *p, int n);
// name: SafeHouse port (JOBPURSUE::Init)
void Init__9JOBPURSUE(struct S *p) { Init__5AIJOB(p); AddGuardState__FP5GUARDi(p->p10, 0x1D); p->n34 = -1; }
