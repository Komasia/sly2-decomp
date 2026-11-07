typedef int qword __attribute__((mode(TI)));
struct S { int pad[5]; void *p14; void *p18; int pad2[3]; void *p28; void *p2C; };
void EvalCrv__FP3CRVfP6VECTORT2(void *p, float t, qword *pq, qword *tangent);
void PosNearestSegment__FG9VU_VECTORN20P6VECTORN23(qword q, qword a, qword b, qword *position, float *projection, float *distance);
void func_001CC1F8(struct S *p, qword q, float *c, float *d, float t)
{
    qword a, b;
    EvalCrv__FP3CRVfP6VECTORT2(p->p18, t, &a, 0);
    EvalCrv__FP3CRVfP6VECTORT2(p->p2C, t, &b, 0);
    PosNearestSegment__FG9VU_VECTORN20P6VECTORN23(q, a, b, 0, c, d);
}
