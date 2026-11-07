typedef int qword __attribute__((mode(TI)));
struct S { char pad[0xE0]; char xE0[4]; };
void *ItriNav__FP9NAVREGIONG9VU_VECTORi(void *p,qword pos,int flags);
int CpolyNear__FP9NAVREGIONP6VECTORG9VU_VECTORT2iPP7NAVPOLY(struct S *p, int a, qword q0, qword q1, int c, void **ap);
int FPolyContains__FP7NAVPOLYG9VU_VECTOR(void *pv, qword q);
int func_001C09A0(struct S *p, qword q,int flags)
{
    void *ap[0x80];
    int n, i;
    if (!ItriNav__FP9NAVREGIONG9VU_VECTORi(p->xE0,q,flags)) return 0;
    n = CpolyNear__FP9NAVREGIONP6VECTORG9VU_VECTORT2iPP7NAVPOLY(p, 0, q, q, 0x80, ap);
    for (i = 0; i < n; i++) {
        if (FPolyContains__FP7NAVPOLYG9VU_VECTOR(ap[i], q)) return 0;
    }
    return 1;
}
