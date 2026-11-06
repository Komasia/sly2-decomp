struct T { char pad[0xF64]; void *pF64; };
struct S { char pad[0x10]; struct T *pt; };
void func_001EEF78(struct S *p);
void SetState__5JOBBDi(struct S *p, int n);
void func_00153FF8(void *p);
void SetGuardPursued__FP5GUARDP2LO(struct T *t, int n);
void func_00209970(struct T *t, int n);
// name: SafeHouse port (JOBBD::Exit)
void Exit__5JOBBD(struct S *p) { func_001EEF78(p); SetState__5JOBBDi(p, -1); func_00153FF8(p->pt->pF64); SetGuardPursued__FP5GUARDP2LO(p->pt, 0); func_00209970(p->pt, 0x2B); }
