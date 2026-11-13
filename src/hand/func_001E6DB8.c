typedef int qword __attribute__((mode(TI)));
struct X { char pad[0xE4]; int fWrap; int c; float *ag; };
struct SPACE;
struct CTX { struct X *p; struct SPACE *space; int pad[2]; qword q; };
extern float D_002A8130;
extern float D_002A8134;
float func_001E69A0(void *pv, float g);
void MinimizeRange(float (*pfn)(void *, float), void *pv, float g, float dg, float gMin, float gMax, float *pg, float *pgOut) asm("MinimizeRange__FPFPvf_fPvffffPfT6");
float GWrapCrv__FP3CRVf(struct X *p, float g);
void EvalCrv__FP3CRVfP6VECTORT2(struct X *p, float g, qword *a, qword *b);
float SFromCrvG__FP3CRV(struct X *p, float g);
void func_001E6DB8(struct X *p, qword q, struct SPACE *space, qword *a, qword *b, float *pg, float *pgOut, float g)
{
    struct CTX ctx;
    float gRes;
    ctx.space = space; ctx.q = q; ctx.p = p;
    MinimizeRange(func_001E69A0, &ctx, g, (p->ag[1] - p->ag[0]) * 0.1f, p->fWrap ? D_002A8130 : p->ag[0], p->fWrap ? D_002A8134 : p->ag[p->c - 1], &gRes, 0);
    gRes = GWrapCrv__FP3CRVf(p, gRes);
    if (a || b) EvalCrv__FP3CRVfP6VECTORT2(p, gRes, a, b);
    if (pg) *pg = gRes;
    if (pgOut) *pgOut = SFromCrvG__FP3CRV(p, gRes);
}
