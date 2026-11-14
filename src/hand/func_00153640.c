typedef struct LM { float gMin; float gMax; } LM;
extern char D_002DE578[];
extern char g_game[];
extern float D_002BDBE0[3];
extern LM g_lmZeroOne;
struct S { char pad[0x234]; LM lm; int c; float ag[16]; float g280; float g284; };
float GSuck__FPv(void *p);
float GLimitLm__FP2LMf(LM *plm, float g);
float GScoreMean__FP5DANCE(struct S *p);
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, void *q);
void *s1_memmove(void *dst, void *src, int cb) asm("memmove");
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
// name: SafeHouse port (AddDanceScore)
void AddDanceScore__FP2LOiif(struct S *p, int a, int b, float g)
{
    float *pg;
    if (g < 0.0f) {
        float t = GSuck__FPv(D_002DE578);
        g *= GClamp(D_002BDBE0[0] + t * (D_002BDBE0[1] + t * D_002BDBE0[2]), g_lmZeroOne.gMin, g_lmZeroOne.gMax);
    }
    if (p->c == 16) {
        s1_memmove(&p->ag[0], &p->ag[1], 15 * sizeof(float));
        pg = &p->ag[p->c - 1];
    } else {
        pg = &p->ag[p->c++];
    }
    *pg = GLimitLm__FP2LMf(&p->lm, g);
    p->g284 = GScoreMean__FP5DANCE(p);
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x36, p);
}
