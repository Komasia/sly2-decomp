/* v4 (Claude agent, lane D31): aligned 21 -> 20 (positional 78 -> 29). v3 plus an allocation-only "j"(b) on the vmin vadd (b stays live in vf1, so the D_002BD8F0 reload takes a different VF and both vmin and vmax get a fresh `qmtc2 a1` + in-place vadd like the target) and ONE pin, d = vf4. Left: vmin a in vf3 (target vf5), vmax a/D_002BD900 vf3/vf2 (target vf4/vf3), v stored right after vmulq, Length reload vf4 (target vf5), 2nd clock load v1 (target s0). Order sweep of vmin/qmtc2/vdiv/vmax (24 forms): this order is best. */
/* v3 (Claude agent, lane D5): aligned 23 -> 21. Length() ends in a mtc1-from-qword asm instead of qmfc2 to a float. Left: the target re-qmtc2s a from $a1 for each asm (vsub vf2, vmin vf5, vmax vf4); ours shares one copy (84 vs 85 insns), and the 2nd clock load reuses s0. */
/* v2 (Claude agent): vmin computed before the clock qmtc2/vdiv, and those two asms volatile: aligned 27 -> 23. Left: VU scheduling of the vmax add and s0 reuse for the 2nd clock load. */
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t, dt, x8, xC, x10; };
extern struct CLOCK D_002DDED0;
extern qword D_002BD8F0, D_002BD900;
extern float D_002BD8D8, D_002BD8DC;
extern char D_003DD490[];
void func_001AE478(void *p);
void func_001AE4A0(void *p, int n);
void func_0020FAA0(void *g, qword a, qword b, void *pfn, void *o, int *pi, int *pj);
qword func_0014EDA0(void *p, int i, int j, void *pfn, qword a, qword v, float g, float h);
void func_0014F030(void);
void func_0014F040(void);

static inline float Length(qword a)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=&j"(one) : "j"(a), "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}

qword func_0014F110(void *p, qword a, qword b)
{
    union { qword q; float f[4]; } s;
    int frame;
    int ii, jj;
    register qword d asm("vf4"); /* the one pin */
    qword v, vmin, vmax, r, w;
    struct CLOCK *pclock = &D_002DDED0;

    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(b), "j"(a));
    __asm__ __volatile__("vadd.xyzw %0, %1, %2" : "=j"(vmin) : "j"(a), "j"(D_002BD8F0), "j"(b));
    __asm__ __volatile__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(*(int *)&pclock->x10));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(v) : "j"(s.q), "j"(d));
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(vmax) : "j"(a), "j"(D_002BD900));
    func_001AE478(&frame);
    func_0020FAA0(D_003DD490, vmin, vmax, func_0014F030, 0, &ii, &jj);
    w = func_0014EDA0(p, ii, jj, func_0014F040, a, v, D_002BD8D8, Length(v) + D_002BD8DC);
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(*(int *)&pclock->x10));
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(w), "j"(s.q));
    func_001AE4A0(&frame, 2);
    return r;
}
