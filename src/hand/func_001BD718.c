typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } V;
extern float D_002C0AC4;
extern char D_003DD020[];
float SWrapCrv__FP3CRVf(void *a, float g);
void func_001E6F10(void *a, float t, V *pv, int n);
void *PpolyOnSegment__FP9NAVREGIONP6VECTORG9VU_VECTORT2(void *a, void *b, qword q2, qword q3);
int NPathLeavesPoly__FP7NAVPOLYP3CRViP6VECTORPff(void *x, void *a, float t, int dir, V *pv, int n);
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(void *x, qword q, void *g, int a, int b, int c, float *pf);
int NPolyWay__FP7NAVPOLYP9NAVREGIONPfif(void *x, void *a, float *pf, int n, float f);
// name: SafeHouse port (NNavWay)
int NNavWay__FG9VU_VECTORP6VECTORP9NAVREGIONP3CRViPP7NAVPOLYPff(qword q, void *a1, void *a2, void *obj, int dir, void **pp, float *pf, float g)
{
    float t;
    V v, v2;
    float f0, f1;
    void *x;
    int r;
    if (dir) t = SWrapCrv__FP3CRVf(obj, g + D_002C0AC4);
    else t = SWrapCrv__FP3CRVf(obj, g - D_002C0AC4);
    func_001E6F10(obj, t, &v, 0);
    x = PpolyOnSegment__FP9NAVREGIONP6VECTORG9VU_VECTORT2(a1, a2, q, v.q);
    if (pp) *pp = x;
    if (!x) return 0;
    r = NPathLeavesPoly__FP7NAVPOLYP3CRViP6VECTORPff(x, obj, t, dir, &v2, 0);
    if (r != -1) return r;
    NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(x, q, D_003DD020, 0, 0, 0, &f0);
    NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(x, v2.q, D_003DD020, 0, 0, 0, &f1);
    if (pf) *pf = f1;
    else pf = &f1;
    return NPolyWay__FP7NAVPOLYP9NAVREGIONPfif(x, a1, pf, -1, f0);
}
