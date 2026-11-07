struct S { char pad[0x10]; void *p10; char pad2[0x1C]; float g30; float g34; int n38; };
void func_001EEF68(struct S *p);
void AddGuardState__FP5GUARDi(void *p, int n);
// name: SafeHouse port (JOBWAIT::Init)
void Init__7JOBWAIT(struct S *p) { func_001EEF68(p); p->n38 = -1; p->g30 = p->g34 = 3.40282346638528859812e+38f; AddGuardState__FP5GUARDi(p->p10, 0x1E); }
