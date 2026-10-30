struct N { int a; void *o; int b; struct N *next; };
struct S { char pad[0x150]; struct N *first; };
extern char D_003DD490[];
void OnSoRemove__FP2SO(struct S *p);
void func_00229738(void *o, struct N *n);
void func_002296C0(void *g, struct N *n);
void func_00229308(struct S *p)
{
    struct N *n;
    OnSoRemove__FP2SO(p);
    for (n = p->first; n; n = n->next) func_00229738(n->o, n);
    func_002296C0(D_003DD490, p->first);
    p->first = 0;
}
