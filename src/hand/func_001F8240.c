struct T { int a[3]; int n; char pad[0x10]; struct T *pnext; };
extern struct T *D_003E145C;
struct T *func_001F8240(int n) { struct T *pt; for (pt = D_003E145C; pt; pt = pt->pnext) if (pt->n == n) return pt; return 0; }
