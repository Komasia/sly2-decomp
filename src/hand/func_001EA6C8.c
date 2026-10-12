typedef unsigned long ulong;
struct E { char pad[0x18]; ulong a; ulong b; };
struct S { int x0, x4; void *p8; struct E **apeC; struct E **ape10; };
int func_001EA688(void *p);
ulong func_001EA6C8(struct S *p, int i, int j)
{
    ulong fl = p->apeC[i]->b;
    struct E *pe = p->ape10[i * func_001EA688(p->p8) + j];
    if (pe)
        fl |= pe->a;
    return fl;
}
