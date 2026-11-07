typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
struct T { char pad[0xF64]; void *pF64; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x48]; int n5C; };
void Enter__7JOBMOVE(struct S *p);
void SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct T *t, int a, int b, qword q);
void DetachGuardMove__FP5GUARD(struct T *t);
void SetState__5JOBB1i(struct S *p, int n);
void LockJob__FP5AIJOB(struct S *p);
void func_00154038(void *p, int a, int b);
// name: SafeHouse port (JOBB1::Enter)
void Enter__5JOBB1(struct S *p) { Enter__7JOBMOVE(p); SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(p->pt, 0, 0, D_002A2DD0); DetachGuardMove__FP5GUARD(p->pt); SetState__5JOBB1i(p, 0); LockJob__FP5AIJOB(p); func_00154038(p->pt->pF64, p->n5C, 2); }
