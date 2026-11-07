typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
struct T { char pad[0xF64]; void *pF64; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x28]; int n3C; };
void Enter__5AIJOB(struct S *p);
void SetState__5JOBB0i(struct S *p, int n);
void DetachGuardMove__FP5GUARD(struct T *t);
void SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct T *t, int a, int b, qword q);
void DetachAloContacts__FP3ALO(struct T *t);
void LockJob__FP5AIJOB(struct S *p);
void func_00153FF8(void *p);
void func_00154038(void *p, int a, int b);
// name: SafeHouse port (JOBB0::Enter)
void Enter__5JOBB0(struct S *p) {
    Enter__5AIJOB(p); SetState__5JOBB0i(p, 0); DetachGuardMove__FP5GUARD(p->pt); SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(p->pt, 0, 0, D_002A2DD0);
    DetachAloContacts__FP3ALO(p->pt); LockJob__FP5AIJOB(p); func_00153FF8(p->pt->pF64);
    if (p->n3C) func_00154038(p->pt->pF64, p->n3C, 2);
}
