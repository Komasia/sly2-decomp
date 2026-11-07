struct T { char pad[0xF64]; void *pF64; };
struct S { char pad[0x10]; struct T *pt; };
void Exit__5AIJOB(struct S *p);
void SetState__5JOBBDi(struct S *p, int n);
void func_00153FF8(void *p);
void SetGuardPursued__FP5GUARDP2LO(struct T *t, int n);
void RemoveGuardState__FP5GUARDi(struct T *t, int n);
// name: SafeHouse port (JOBBD::Exit)
void Exit__5JOBBD(struct S *p) { Exit__5AIJOB(p); SetState__5JOBBDi(p, -1); func_00153FF8(p->pt->pF64); SetGuardPursued__FP5GUARDP2LO(p->pt, 0); RemoveGuardState__FP5GUARDi(p->pt, 0x2B); }
