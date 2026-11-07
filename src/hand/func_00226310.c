struct T { char pad[0x3C]; int k; };
struct S { char pad[0x1C0]; struct T *t; };
void *OverlapKindAlo__FP3ALOT0(struct S *p);
void *func_00134310(void *v, int a);
// name: SafeHouse port (OverlapKindTurret)
void *OverlapKindTurret__FP3ALOT0(struct S *p, struct T *q)
{
    void *v = OverlapKindAlo__FP3ALOT0(p);
    if (p->t && q->k == p->t->k) v = func_00134310(v, 1);
    return v;
}
