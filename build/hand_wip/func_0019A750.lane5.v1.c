/* func_0019A750 (lane 5): matched. Picks the vertical speed (z) an actor should have for jump/ballistic state k:
   returns the actor's velocity (virtual slot 33) with z = max(z, wanted). Cases 1/7/9/13/14/15 use a table of heights,
   case 4 is a quadratic (CLQ) clamped by an LM, case 6 solves the apex/landing timing with func_0011D508.
   Notes on what it took to match (see also notes/190000.md):
   - sqrtf in the case-6 chain is the SDK's volatile earlyclobber `sqrt.s` asm (same as func_001C4330 / func_00196928):
     as a volatile asm it is a scheduler barrier, which is what keeps the target's neg/div before the vcall and the
     `g * 0.5f` argument after the second sqrt. The sqrt in cases 1/7/... is the plain builtin (matches that way).
   - `-2.0f * g * (a - b)` (or `g * ((a - b) * -2.0f)` through a temp) keeps fast-math from reassociating the factors.
   - The `d`/`T` branch uses its own tH2 instead of reusing tHalf: sharing one user variable changed local-alloc's
     quantity priorities and swapped f0/f1 in the case-6 temporaries.
   - q = -h / T is a statement before tH2 so the divide has the lower LUID and the scheduler prefers the multiply. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
static inline float SqrtV(float x) { float r; __asm__ __volatile__("sqrt.s %0,%1" : "=&f"(r) : "f"(x)); return r; }
struct LO;
typedef struct { short d; short pad; qword (*pfn)(void *); } VTE;
struct C { char pad[0x88]; float g88; };   /* g88 = gravity */
struct D { char pad[8]; float x8; };       /* x8 = ceiling height */
struct LO { char pad[0xC]; VTE *vt; char pad2[0xE8 - 0x10]; struct C *xe8; char pad3[0x218 - 0xEC]; struct D *x218; char pad4[0x238 - 0x21C]; float x238; };
struct S { struct LO *x0; };
static inline float GMax(float a, float b) { return a > b ? a : b; }
qword func_001A62E8(struct LO *p);
int func_0011D508(float, float, float, float *);
extern float D_002BF738, D_002BF73C, D_002BF8C8, D_002BF8CC, D_002BF8D0, D_002BF8D4, D_002BF8D8, D_002BF8DC;
typedef struct { float g, gFirst, gSecond; } CLQ;
extern CLQ D_002BF8B0;
static inline float GFromClq(CLQ *pclq, float g) { return pclq->g + g * (pclq->gFirst + g * pclq->gSecond); }
typedef struct { float gMin, gMax; } LM;
extern LM D_002BF8C0;
static inline float GLimitLm(LM *plm, float g)
{
    float gm = plm->gMin;
    float gx = plm->gMax;
    float r;
    if (g < gm)
        r = gm;
    else if (g > gx)
        r = gx;
    else
        r = g;
    return r;
}
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
        LM *plm = &D_002BF8C0;
        CLQ *pclq = &D_002BF8B0;
        float gq = GFromClq(pclq, v.f[2]);
        x = GLimitLm(plm, gq);
        break;
    }
    case 6: {
        float v0, tPeak, vz, t1, h, d, T, nv, s2, tHalf, tH2, c2, q;
        float ag[2];
        v0 = SqrtV(-2.0f * g * D_002BF738);
        nv = -v0;
        tPeak = nv / g;
        vz = GetZ(p->x0->vt[33].pfn((char *)p->x0 + p->x0->vt[33].d));
        vz = vz < v0 ? vz : v0;
        t1 = (vz - v0) / g;
        tHalf = t1 * 0.5f;
        h = t1 * (v0 + g * tHalf);
        c2 = (D_002BF73C - D_002BF738) * -2.0f;
        s2 = SqrtV(g * c2);
        func_0011D508(g * 0.5f, s2, D_002BF738, ag);
        d = ag[1] - tPeak;
        if (0.0f < vz) {
            x = SqrtV(-2.0f * g * (D_002BF73C - h));
        } else {
            if (vz < nv) h = 0.0f;
            T = tPeak + tPeak + d - t1;
            q = -h / T;
            tH2 = T * 0.5f;
            x = q - g * tH2;
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
