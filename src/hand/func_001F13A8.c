#include "vtbl.h"
struct VT { VTENT a[5]; };
struct P { char pad[0xC]; struct VT *pvt; char pad2[0x24 - 0x10]; void *p24; };
struct L { struct P *p; int a; int b; };
int OidFromSmIsms__FP2SMi(void *, int);
// name: SafeHouse port (NotifySmaState)
void NotifySmaState__FP3SMAii(struct P *p, int a, int b)
{
    struct L l;
    int *ap[2];
    l.p = p;
    l.a = OidFromSmIsms__FP2SMi(p->p24, a);
    l.b = OidFromSmIsms__FP2SMi(p->p24, b);
    ((void (*)(void *, int, struct L *))p->pvt->a[4].pfn)(VT_THIS(p, &p->pvt->a[4]), 10, &l);
    ap[0] = &l.a;
    ap[1] = &l.b;
    ((void (*)(void *, int, int, int, int **, int))p->pvt->a[3].pfn)(VT_THIS(p, &p->pvt->a[3]), 8, 0, 2, ap, 0);
}
