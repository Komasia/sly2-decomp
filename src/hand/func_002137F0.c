struct S { char pad[0xA4]; int a; char pad2[0xC]; struct S *next; };
extern struct S *D_003E1060;
int func_002137F0(struct S *p)
{
    struct S *q;
    int unused[4];
    for (q = D_003E1060; q; q = q->next) {
        if (p->a < q->a)
            return 1;
    }
    return 0;
}
