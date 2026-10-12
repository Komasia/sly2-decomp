typedef int qword __attribute__((mode(TI)));
struct X { char pad[0xE4]; int fWrap; int c; float *ag; };
struct CTX { struct X *p; int n; int pad[2]; qword q; };
extern float D_002A8130;
extern float D_002A8134;
float func_001E69A0(float g, void *pv);
void func_0011D9E0(float (*pfn)(float, void *), float g, float dg, float gMin, float gMax, void *pv, float *pg, int n);
float func_001E6660(struct X *p, float g);
void func_001E67B8(struct X *p, float g, int a, int b);
float func_001E63C0(struct X *p, float g);
void func_001E6DB8(struct X *p, qword q, int n, int a, int b, float *pg, float *pgOut, float g)
{
    struct CTX ctx;
    float gRes;
    float gMin, gMax, dg;
    ctx.n = n; ctx.q = q; ctx.p = p;
    func_0011D9E0(func_001E69A0, g, (p->ag[1] - p->ag[0]) * 0.1f, p->fWrap ? D_002A8130 : p->ag[0], p->fWrap ? D_002A8134 : p->ag[p->c - 1], &ctx, &gRes, 0);
    gRes = func_001E6660(p, gRes);
    if (a || b) func_001E67B8(p, gRes, a, b);
    if (pg) *pg = gRes;
    if (pgOut) *pgOut = func_001E63C0(p, gRes);
}
