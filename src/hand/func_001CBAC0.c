typedef int qword __attribute__((mode(TI)));
struct T { char pad[0x218]; qword *pq; };
struct S { char pad[0xE4]; int fE4; };
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(struct S *p, qword q, int a, void *pv, int b, int c, float *pf);
float SMaxCrv__FP3CRV(struct S *p);
void func_001CBAC0(struct S *p, struct T *q, float *pf)
{
    qword buf;
    float g, v;
    NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(p, *q->pq, 0, &buf, 0, 0, pf);
    if (p->fE4 == 0) {
        g = SMaxCrv__FP3CRV(p) - 50.0f;
        v = *pf;
        if (v < 50.0f) v = 50.0f;
        else if (g < v) v = g;
        *pf = v;
    }
}
