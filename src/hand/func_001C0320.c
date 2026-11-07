typedef int qword __attribute__((mode(TI)));
struct S { int a[5]; int n14; };
void *ItriNavFrom__FP9NAVREGIONP4NODEG9VU_VECTORi(struct S *p, int n, qword q);
qword PosNearestTri__FP9NAVREGIONG9VU_VECTOR(void *p, qword q);
// name: SafeHouse port (FNavPoint)
int FNavPoint__FP9NAVREGIONG9VU_VECTORP6VECTOR(struct S *p, qword q, qword *pq)
{
    void *pv = ItriNavFrom__FP9NAVREGIONP4NODEG9VU_VECTORi(p, p->n14, q);
    if (!pv) return 0;
    *pq = PosNearestTri__FP9NAVREGIONG9VU_VECTOR(pv, q);
    return 1;
}
