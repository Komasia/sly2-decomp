typedef int qword __attribute__((mode(TI)));
struct Q { int pad0; int n4; int pad8; void *pC; int pad10; int n14; int pad18; void *p1C; };
struct S { char pad[0x38]; struct Q *pq; char pad2[0x10]; void *p4C; };
qword PosOfLo__FP2LO(void *p);
int FPointInShape__FP2LOG9VU_VECTOR(void *p, qword q);
// name: SafeHouse port (JOBB5::PloEnd)
int PloEnd__5JOBB5(struct S *p)
{
    if (FPointInShape__FP2LOG9VU_VECTOR(p->pq->pC, PosOfLo__FP2LO(p->p4C)))
        return p->pq->n4;
    if (FPointInShape__FP2LOG9VU_VECTOR(p->pq->p1C, PosOfLo__FP2LO(p->p4C)))
        return p->pq->n14;
    return p->pq->n4;
}
