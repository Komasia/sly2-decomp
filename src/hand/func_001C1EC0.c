typedef int qword __attribute__((mode(TI)));
struct S { void *p0; void *p4; int pad[2]; qword q10; };
extern char D_003DD020[];
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(void *p, qword a, void *b, qword *pq, int c, int d, int e);
qword PosOfLo__FP2LO(void *p);
// name: SafeHouse port (PosGoal)
qword PosGoal__FP4GOALG9VU_VECTOR(struct S *p, qword a)
{
    qword q;
    if (p->p0) {
        NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(p->p0, a, D_003DD020, &q, 0, 0, 0);
    } else if (p->p4) {
        q = PosOfLo__FP2LO(p->p4);
    } else {
        q = p->q10;
    }
    return q;
}
