struct S { char pad[0x10]; void *p10; char pad2[0x28]; int n3C; int n40; };
void Enter__5AIJOB(struct S *p);
void AddGuardState__FP5GUARDi(void *p, int n);
int func_00209BC0(void *p);
void SetMoveState__7JOBMOVEi(struct S *p, int n);
// name: SafeHouse port (JOBMOVE::Enter)
void Enter__7JOBMOVE(struct S *p) {
    Enter__5AIJOB(p);
    AddGuardState__FP5GUARDi(p->p10, p->n3C);
    if (!p->n40) {
        p->n40 = func_00209BC0(p->p10);
        if (!p->n40) { SetMoveState__7JOBMOVEi(p, 1); return; }
    }
    SetMoveState__7JOBMOVEi(p, 0);
}
