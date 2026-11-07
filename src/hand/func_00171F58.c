struct S { char pad[0x10]; void *p10; char pad2[0x1C]; int n30; int pad3; float g38; int pad4; float g40; };
void Init__5AIJOB(struct S *p);
void AddGuardState__FP5GUARDi(void *p, int n);
// name: SafeHouse port (JOBINVESTIGATE::Init)
void Init__14JOBINVESTIGATE(struct S *p) { Init__5AIJOB(p); AddGuardState__FP5GUARDi(p->p10, 0x1F); p->n30 = -1; p->g40 = p->g38 = 3.40282346638528859812e+38f; }
