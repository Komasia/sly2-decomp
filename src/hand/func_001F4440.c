typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
struct T { char pad[0x70]; qword v; char pad2[0x14]; int n; };
struct S { char pad[0x58]; struct T *pt; };
qword VelXfPoint__FP2XFT0G9VU_VECTOR(struct T *, int, qword);
// name: SafeHouse port (VelAloPos)
qword VelAloPos__FP3ALO(struct S *p) { struct T *pt = p->pt; if (!pt || pt->n != 1) return D_002A2DD0; return VelXfPoint__FP2XFT0G9VU_VECTOR(pt, 0, pt->v); }
