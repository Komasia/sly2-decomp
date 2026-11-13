typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } V;
extern float D_002C0ABC;
float SWrapCrv__FP3CRVf(void *a, float g);
void EvalCrvS(void *a, float t, V *pv, int n) asm("EvalCrvS__FP3CRVfP6VECTORT2");
int func_001C0920(void *b, qword v, void *c);
// name: SafeHouse port (FPolyPointOnRegion)
int FPolyPointOnRegion__FP7NAVPOLYP9NAVREGIONffPfPv(void *a, void *b, float g, float range, float *pf, void *c)
{
    float d, t;
    V v0, v1;
    for (d = 0.0f; d < range; d += D_002C0ABC) {
        t = SWrapCrv__FP3CRVf(a, g - d);
        EvalCrvS(a, t, &v0, 0);
        if (func_001C0920(b, v0.q, c)) {
            if (pf) *pf = t;
            return 1;
        }
        t = SWrapCrv__FP3CRVf(a, g + d);
        EvalCrvS(a, t, &v1, 0);
        if (func_001C0920(b, v1.q, c)) {
            if (pf) *pf = t;
            return 1;
        }
    }
    return 0;
}
