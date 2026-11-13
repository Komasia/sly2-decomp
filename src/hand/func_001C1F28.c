typedef int qword __attribute__((mode(TI)));
struct S { void *p0; void *p4; int pad[2]; qword q10; };
float SMaxCrv__FP3CRV(void *p);
void EvalCrvS(void *p, qword *pq, int n, float g) asm("EvalCrvS__FP3CRVfP6VECTORT2");
qword PosOfLo__FP2LO(void *p);
// name: SafeHouse port (PosRecord)
qword PosRecord__FP4GOAL(struct S *p)
{
    qword q;
    if (p->p0) {
        EvalCrvS(p->p0, &q, 0, SMaxCrv__FP3CRV(p->p0) * 0.5f);
    } else if (p->p4) {
        q = PosOfLo__FP2LO(p->p4);
    } else {
        q = p->q10;
    }
    return q;
}
