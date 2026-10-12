struct EC { char pad[0x70]; unsigned long fl; };
struct O { int pad[4]; struct O *pNext; int n14; char pad2[0xEC - 0x18]; struct EC *pec; };
struct A { int pad[5]; int n14; };
struct B { int pad; struct O *po; int pad2[2]; unsigned long fl; };
int func_00132B10(struct O *po, int n);
int func_00154568(struct A *a, struct B *b)
{
    struct O *po;
    if (b->fl & 0x1000000000000L)
        return 0;
    po = b->po;
    if (po->pec->fl & 4)
        return 0;
    if (po->n14 == a->n14)
        return 0;
    {
        struct O *p = po;
        while (p && !func_00132B10(p, 0x33))
            p = p->pNext;
        return p == 0;
    }
}
