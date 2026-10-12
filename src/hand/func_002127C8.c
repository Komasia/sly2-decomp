struct Q { char pad[0x58]; int k; int pad2; int a; int b; };
struct S { char pad[0x40]; struct Q *q; char pad2[8]; struct S *next; };
extern struct S *D_003E106C;
extern int D_002BE538;
int func_002127C8(void)
{
    struct S *p;
    for (p = D_003E106C; p; p = p->next) {
        struct Q *q = p->q;
        int v;
        if (q->k == 0)
            continue;
        if (q->k == 1)
            v = D_002BE538 - q->a;
        else
            v = q->b;
        if (v < 2)
            return 0;
    }
    return 1;
}
