typedef int qword __attribute__((mode(TI)));
void *PregionAt__FG9VU_VECTORi(qword q, int n);
int CpolyNear__FP9NAVREGIONP6VECTORG9VU_VECTORT2iPP7NAVPOLY(void *p, int n, qword q, qword q2, int c, void **ap);
int FPolyContains__FP7NAVPOLYG9VU_VECTOR(void *p, qword q);
// name: SafeHouse port (PpolyAtPoint)
void *PpolyAtPoint__FG9VU_VECTOR(qword q)
{
    void *ap[0x40];
    void *p = PregionAt__FG9VU_VECTORi(q, 0);
    int c, i;
    if (!p) return 0;
    c = CpolyNear__FP9NAVREGIONP6VECTORG9VU_VECTORT2iPP7NAVPOLY(p, 0, q, q, 0x40, ap);
    for (i = 0; i < c; i++) {
        void *pT = ap[i];
        if (FPolyContains__FP7NAVPOLYG9VU_VECTOR(pT, q)) return pT;
    }
    return 0;
}
