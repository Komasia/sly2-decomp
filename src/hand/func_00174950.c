struct S { char pad[0x10]; void *p10; char pad2[0x28]; int n3C; int n40; };
void func_001EEF70(struct S *p);
void func_00209890(void *p, int n);
int func_00209BC0(void *p);
void SetMoveState__7JOBMOVEi(struct S *p, int n);
// name: SafeHouse port (JOBMOVE::Enter)
void Enter__7JOBMOVE(struct S *p) {
    func_001EEF70(p);
    func_00209890(p->p10, p->n3C);
    if (!p->n40) {
        p->n40 = func_00209BC0(p->p10);
        if (!p->n40) { SetMoveState__7JOBMOVEi(p, 1); return; }
    }
    SetMoveState__7JOBMOVEi(p, 0);
}
