typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
struct LO;
typedef struct { short d; short pad; qword (*pfn)(void *); } VTE;
struct C { char pad[0x88]; float g88; };
struct D { char pad[8]; float x8; };
struct LO { char pad[0xC]; VTE *vt; char pad2[0xE8 - 0x10]; struct C *xe8; char pad3[0x218 - 0xEC]; struct D *x218; char pad4[0x238 - 0x21C]; float x238; };
struct S { struct LO *x0; };
static inline float GMax(float a, float b) { return a > b ? a : b; }
static inline float GClamp(float g, float lo, float hi) { if (g < lo) return lo; if (g > hi) return hi; return g; }
qword func_001A62E8(struct LO *p);
int func_0011D508(float, float, float, float *);
extern float D_002BF738, D_002BF73C, D_002BF8C8, D_002BF8CC, D_002BF8D0, D_002BF8D4, D_002BF8D8, D_002BF8DC;
typedef struct { float g, gFirst, gSecond; } CLQ;
extern CLQ D_002BF8B0;
static inline float GFromClq(CLQ *pclq, float g) { return pclq->g + g * (pclq->gFirst + g * pclq->gSecond); }
typedef struct { float gMin, gMax; } LM;
extern LM D_002BF8C0;
static inline float GLimitLm(LM *plm, float g) { if (g < plm->gMin) return plm->gMin; if (g > plm->gMax) return plm->gMax; return g; }
qword func_0019A750(struct S *p, int k)
{
    U pos, v;
    float g, x;
    pos.q = func_001A62E8(p->x0);
    v.q = p->x0->vt[33].pfn((char *)p->x0 + p->x0->vt[33].d);
    g = p->x0->xe8->g88;
    switch (k) {
    case 2:
        x = D_002BF8C8;
        break;
    case 18:
        x = D_002BF8CC;
        break;
    case 3:
        x = D_002BF8D0;
        break;
    case 1: case 7: case 9: case 13: case 14: case 15: {
        float h, s;
        struct LO *o;
        switch (k) {
        default: h = D_002BF738; break;
        case 9: h = D_002BF8D4; break;
        case 14: h = D_002BF8D8; break;
        case 13: h = D_002BF8DC; break;
        }
        o = p->x0;
        s = (g + g) * (o->x218->x8 - o->x238 - h);
        x = __builtin_sqrtf(GMax(s, 0.0f));
        break;
    }
    case 4: {
        x = GLimitLm(&D_002BF8C0, GFromClq(&D_002BF8B0, v.f[2]));
        break;
    }
    case 6: {
        float v0, tPeak, vz, t1, h, d, T, nv, s2;
        float ag[2];
        v0 = __builtin_sqrtf(g * (D_002BF738 * -2.0f));
        nv = -v0;
        tPeak = nv / g;
        vz = GetZ(p->x0->vt[33].pfn((char *)p->x0 + p->x0->vt[33].d));
        vz = v0 < vz ? v0 : vz;
        t1 = (vz - v0) / g;
        x = t1 * 0.5f;
        h = t1 * (v0 + g * x);
        func_0011D508(g * 0.5f, __builtin_sqrtf(g * ((D_002BF73C - D_002BF738) * -2.0f)), D_002BF738, ag);
        d = ag[1] - tPeak;
        if (0.0f < vz) {
            x = __builtin_sqrtf(g * ((D_002BF73C - h) * -2.0f));
        } else {
            if (vz < nv) h = 0.0f;
            T = tPeak + tPeak + d - t1;
            x = T * 0.5f;
            x = -h / T - g * x;
        }
        break;
    }
    default:
        x = v.f[2];
        break;
    }
    v.f[2] = GMax(v.f[2], x);
    return v.q;
}
