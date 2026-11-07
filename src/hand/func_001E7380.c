typedef int qword __attribute__((mode(TI)));
float GFromCrvS__FP3CRVf(void *p, float seed);
void NearestCrv__FP3CRV(void *p, qword q, void *a, qword *b, qword *c, float *d, float *e, float g);
// name: SafeHouse port (NearestCrvS)
void NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(void *p, qword q, void *a, qword *b, qword *c, float *d, float *e, float seed)
{
    NearestCrv__FP3CRV(p, q, a, b, c, d, e, GFromCrvS__FP3CRVf(p, seed));
}
