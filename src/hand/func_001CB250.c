struct T { int n; int *ap; };
struct S { char pad[0xE0]; struct T *pt; };
void *func_001CAEC8(struct S *p, int n);
int func_001CA930(struct S *p, void *q);
// name: SafeHouse port (PloAcquireProxyObject)
int PloAcquireProxyObject__FP2SWi(struct S *p, int f)
{
    /*B*/void *q; if (p->pt->n != 1) return 0; q = func_001CAEC8(p, f ? 1 : 2); if (!q) return 0; return p->pt->ap[func_001CA930(p, q)];/*E*/
}
