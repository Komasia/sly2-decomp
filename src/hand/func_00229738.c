struct N { int a[2]; struct N *next; };
struct S { char pad[0x138]; struct N *first; };
void WakeAlo__FP3ALO(struct S *p, struct N *n);
void func_00229738(struct S *p, struct N *n)
{
    struct N **pp;
    for (pp = &p->first; *pp; pp = &(*pp)->next) {
        if (*pp == n) { *pp = n->next; n->next = 0; break; }
    }
    WakeAlo__FP3ALO(p, n);
}
