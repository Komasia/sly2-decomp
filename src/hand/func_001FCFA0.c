struct T { char pad[0x40]; int n; struct T *pnext; };
struct S { char pad[0xEC]; struct T *pt; };
struct T *func_001FCFA0(struct S *p, int n) { struct T *pt; for (pt = p->pt; pt; pt = pt->pnext) if (pt->n == n) return pt; return 0; }
