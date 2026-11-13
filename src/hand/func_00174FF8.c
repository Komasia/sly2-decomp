typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
struct T { char pad[0x58]; int n58; int n5C; char pad2[0xF64 - 0x60]; void *pF64; char pad3[0xFCC - 0xF68]; int nFCC; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x24]; int n38; };
void Enter__7JOBMOVE(struct S *p);
int FGuardState(struct T *t, int n) asm("FGuardState__FP5GUARDi");
void SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct T *t, int a, int b, qword q);
void func_00153FF8(void *p);
void SetXfMode__FP3ALOP2XFi(struct T *t, int a, int b);
// name: SafeHouse port (JOBSTAND::Enter)
void Enter__8JOBSTAND(struct S *p) {
    Enter__7JOBMOVE(p);
    if (FGuardState(p->pt, 1)) {
        SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(p->pt, 0, 0, D_002A2DD0);
        func_00153FF8(p->pt->pF64);
        if (p->pt->nFCC) p->n38 = p->pt->nFCC;
    }
    SetXfMode__FP3ALOP2XFi(p->pt, p->pt->n58, 1);
    if (!p->n38) SetXfMode__FP3ALOP2XFi(p->pt, p->pt->n5C, 1);
}
