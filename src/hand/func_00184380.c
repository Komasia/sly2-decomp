struct T { char pad[0xF4]; int n; };
struct S { char pad[0x180]; int x; char pad2[0x18]; int n; };
int FLoInParentChain__FP2LOT0(struct T *q, int x);
int func_00184380(struct S *p, struct T *q)
{
    if (q->n != p->n) return 1;
    return FLoInParentChain__FP2LOT0(q, p->x);
}
