struct S { char pad[0x30]; int n30; char pad2[0xC]; void *p40; };
void Update__5AIJOB(struct S *p);
int FKindeDone__FP5KINDE(void *p);
void SetMoveState__7JOBMOVEi(struct S *p, int n);
// name: SafeHouse port (JOBMOVE::Update)
void Update__7JOBMOVE(struct S *p) {
    int s;
    Update__5AIJOB(p);
    do {
        s = p->n30;
        if (s == 0 && FKindeDone__FP5KINDE(p->p40)) SetMoveState__7JOBMOVEi(p, 1);
    } while (s != p->n30);
}
