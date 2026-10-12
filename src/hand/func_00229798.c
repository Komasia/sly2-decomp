struct VTE { short d; short pad; void (*pf)(void *, void *); };
struct O { int a[3]; struct VTE *vt; };
struct N { struct O *po; int a; struct N *next; };
struct S { char pad[0x138]; struct N *first; };
void func_00229798(struct S *p)
{
    struct N *n;
    for (n = p->first; n; n = n->next) {
        struct O *po = n->po;
        po->vt[71].pf((char *)po + po->vt[71].d, n);
    }
}
