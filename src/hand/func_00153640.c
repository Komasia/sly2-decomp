typedef struct LM { float gMin; float gMax; } LM;
extern char D_002DE578[];
extern char g_game[];
extern float D_002BDBE0[3];
extern LM g_lmZeroOne;
struct S { char pad[0x234]; LM lm; int c; float ag[16]; float g280; float g284; };
float func_00154C90(void *p);
float GLimitLm__FP2LMf(LM *plm, float g);
float func_00153760(struct S *p);
void func_001619A0(void *p, int n, void *q);
void *func_002332B8(void *dst, void *src, int cb);
static inline float GClampLm(LM *plm, float g)
{
    if (g < plm->gMin)
        return plm->gMin;
    if (plm->gMax < g)
        return plm->gMax;
    return g;
}
static inline float GLim(LM *plm, float g)
{
    if (g < plm->gMin)
        g = plm->gMin;
    else if (plm->gMax < g)
        g = plm->gMax;
    return g;
}
static inline float GClamp(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
void func_00153640(struct S *p, int a, int b, float g)
{
    float *pg;
    if (g < 0.0f) {
        float t = func_00154C90(D_002DE578);
        g *= GClamp(D_002BDBE0[0] + t * (D_002BDBE0[1] + t * D_002BDBE0[2]), g_lmZeroOne.gMin, g_lmZeroOne.gMax);
    }
    if (p->c == 16) {
        func_002332B8(&p->ag[0], &p->ag[1], 15 * sizeof(float));
        pg = &p->ag[p->c - 1];
    } else {
        pg = &p->ag[p->c++];
    }
    *pg = GLimitLm__FP2LMf(&p->lm, g);
    p->g284 = func_00153760(p);
    func_001619A0(g_game, 0x36, p);
}
