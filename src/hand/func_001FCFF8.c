struct T { char pad[0x40]; int n; struct T *pnext; };
struct S { char pad[0xF0]; struct T *pt; };
// name: SafeHouse port (PstreamFindMusic)
struct T *PstreamFindMusic__FP8SOUNDMGRi(struct S *p, int n) { struct T *pt; for (pt = p->pt; pt; pt = pt->pnext) if (pt->n == n) return pt; return 0; }
