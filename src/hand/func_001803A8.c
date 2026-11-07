struct T { char pad[0xEC]; int n; };
struct S { char pad[0x1C8]; struct T *pt; };
int func_001F4FC8(struct S *p, struct T *q);
// name: SafeHouse port (OverlapKindPiece)
int OverlapKindPiece__FP3ALOT0(struct S *p, struct T *q)
{
    if (p->pt && q->n == p->pt->n)
        return 3;
    return func_001F4FC8(p, q);
}
