typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
struct T { char pad[0x70]; qword v; char pad2[0x14]; int n; };
struct S { char pad[0x58]; struct T *pt; };
qword func_0022D348(struct T *, int, qword);
qword func_001F4440(struct S *p) { struct T *pt = p->pt; if (!pt || pt->n != 1) return D_002A2DD0; return func_0022D348(pt, 0, pt->v); }
