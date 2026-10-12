struct T { char pad[0x80]; int a80; int a84; void *p88; void *p8C; char pad2[0x100 - 0x90]; };
struct S { char pad[0x10]; struct S *next; char pad2[0x50 - 0x14]; int c; struct T *base; };
void func_001F4CA0(struct S *pnew, struct S *pold, struct T **pp)
{
    struct T *t = *pp;
    struct T *n;
    int i;
    if (!t) return;
    n = 0;
    i = t - pold->base;
    if (i >= 0 && i < pnew->c) {
        n = pnew->base + i;
    } else {
        pold = pold->next;
        i = t - pold->base;
        if (i >= 0 && i < pold->c) n = pnew->next->base + i;
    }
    if (n->p88 == &t->a80) n->p88 = &n->a80;
    if (n->p8C == &t->a84) n->p88 = &n->a84;
    *pp = n;
}
