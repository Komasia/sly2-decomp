typedef unsigned long ulong;
struct E { char pad[0x18]; ulong a; ulong b; };
struct S { int x0, x4; int n8; struct E **apeC; struct E **ape10; };
int func_001EA688(int n, struct E **ape);
ulong func_001EA6C8(struct S *p, int i, int j)
{
    ulong fl = p->apeC[i]->b;
    int c = func_001EA688(p->n8, p->apeC);
    struct E *pe = p->ape10[i * c + j];
    if (!pe)
        return fl;
    return fl | pe->a;
}
