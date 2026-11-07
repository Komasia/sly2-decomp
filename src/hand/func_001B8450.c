struct P { char pad[0x13D0]; int n13D0; char pad1[0x1430 - 0x13D4]; void *p1430; char pad2[0x1910 - 0x1434]; int a1910[1]; };
int OverlapKindActor__FP3ALOi(struct P *p, void *pv);
int FLoInParentChain__FP2LOT0(void *pv, void *p1);
int func_00134310(int n, int k);
int OverlapKindJtThrow__FP7JTTHROWP3ALOi(int *pn, void *pv, int n);
// name: SafeHouse port (MurrayCarryOverlapKind)
int MurrayCarryOverlapKind__FP3ALOT0(struct P *p, void *pv)
{
    int n = OverlapKindActor__FP3ALOi(p, pv);
    if (p->p1430 && FLoInParentChain__FP2LOT0(pv, p->p1430))
        n = func_00134310(n, 3);
    else if (p->n13D0 == 15)
        n = OverlapKindJtThrow__FP7JTTHROWP3ALOi(p->a1910, pv, n);
    return n;
}
