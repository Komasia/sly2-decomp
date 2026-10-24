// func_0014F110 laneK3v1 (Claude agent, lane K3, 2026-10-24): FRESH rewrite in the func_0014C748 style, no pins, VU helper asms only + ONE allocation-only "j"(posMin) on the vdiv. aligned 22 (policy-compliant fresh2 24; v5 16 uses a pin + instruction asm). Left: posMin gets vf1 with a caller-save (sqc2 0x60/lqc2) instead of an unallocated pseudo (0x40); pos shares one qmtc2 a1; spill slots pos 0x40 (target 0x20).
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } VU_FLOAT(const float *pg) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)pg)); } };
struct CLOCK { float t, dt, x8, xC, dtPrev; };
struct FRAME { int n; };
extern "C" {
extern CLOCK D_002DDED0;
extern qword D_002BD8F0, D_002BD900;
extern float D_002BD8D8, D_002BD8DC;
extern char D_003DD490[];
void *func_001AE478(FRAME *p);
void func_001AE4A0(FRAME *p, int n);
void func_0020FAA0(void *g, qword a, qword b, void *pfn, void *o, int *pi, int *pj);
qword func_0014EDA0(void *p, int i, int j, void *pfn, qword a, qword v, float g, float h);
void func_0014F030(void);
void func_0014F040(void);
qword func_0014F110(void *p, qword pos, qword posTarget);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword DivideBy(const qword &v, const VU_FLOAT &g, const qword &use) { qword r; __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(g.q), "j"(use)); return r; } /* "j"(use): allocation-only operand */
static inline qword AddScaled(const qword &base, const qword &vec, const VU_FLOAT &s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(base), "j"(vec), "j"(s.q));
    return r;
}
static inline qword QwDot(const qword &a, const qword &b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword QwSqrt(const qword &a) { qword r; __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(a)); return r; }
static inline float GXOfQw(const qword &q) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(q)); return x; }
static inline float Length(const qword &v) { return GXOfQw(QwSqrt(QwDot(v, v))); }

qword func_0014F110(void *p, qword pos, qword posTarget)
{
    CLOCK *pclock = &D_002DDED0;
    FRAME frame;
    int ii, jj;
    qword dpos = Sub(posTarget, pos);
    qword posMin = Add(pos, D_002BD8F0);
    qword v = DivideBy(dpos, VU_FLOAT(&pclock->dtPrev), posMin);
    qword posMax = Add(pos, D_002BD900);
    func_001AE478(&frame);
    func_0020FAA0(D_003DD490, posMin, posMax, (void *)func_0014F030, 0, &ii, &jj);
    qword w = func_0014EDA0(p, ii, jj, (void *)func_0014F040, pos, v, D_002BD8D8, Length(v) + D_002BD8DC);
    qword r = AddScaled(pos, w, VU_FLOAT(&pclock->dtPrev));
    func_001AE4A0(&frame, 2);
    return r;
}
