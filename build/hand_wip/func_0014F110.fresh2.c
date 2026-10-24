/* fresh2 (Claude agent, lane D38): fresh1 (27) -> aligned 24, no pins, no volatile. vdiv helper QwDivXUse with ONE allocation-only "j"(posMin) operand: posMin's vadd then feeds the vdiv in sched1, so its priority rises and the VU asms issue in the target's source order (vsub, lo lqc2, clock lw, posMin vadd, qmtc2, vdiv, hi lqc2, posMax vadd). Left: posMin now has 3 refs, so local-alloc gives it vf1 with a caller-save (sqc2 vf1,0x60 / lqc2 / qmfc2 a1) instead of the target's unallocated pseudo (sqc2 vf5,0x40; lq a1,0x40); vsub and posMin share one qmtc2 a1 copy. "X"/"j" same 24, "r" 25, "m" 24, on D_002BD8F0 instead 32, v before posMin 24. */
/* fresh1 (Claude agent, lane D36): Lilly-style rewrite, NO pins, no volatile: aligned 27 (v5 is 16 but uses a pin + volatile + allocation operands). Key: a function-scope union VU_FLOAT u written twice from a plain-qword QwOfG (one sqc2 to 0(sp) each, like the target; a by-value VuFloat returning the union = two stores, 0xC0 frame); *(const int *)&pclock->x10 gives the lw. Left: posMin vadd is scheduled after vdiv (target: source order), v/posMin spill slots swapped, pos shares one VF copy, 2nd clock load v1 (target s0). All-volatile 47; volatile QwAdd 29, +QwDivX 26, +QwOfG 40. */
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t, dt, x8, xC, x10; };
extern struct CLOCK D_002DDED0;
extern qword D_002BD8F0, D_002BD900;
extern float D_002BD8D8, D_002BD8DC;
extern char D_003DD490[];
struct FRAME { int n; };
void *func_001AE478(struct FRAME *p);
void func_001AE4A0(struct FRAME *p, int n);
void func_0020FAA0(void *g, qword a, qword b, void *pfn, void *o, int *pi, int *pj);
qword func_0014EDA0(void *p, int i, int j, void *pfn, qword a, qword v, float g, float h);
void func_0014F030(void);
void func_0014F040(void);

typedef union { qword qw; float ag[4]; } VU_FLOAT;
static inline qword QwOfG(const float *pg)
{
    qword qw;
    __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(*(const int *)pg));
    return qw;
}
static inline qword QwSub(qword a, qword b)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(a), "j"(b));
    return qw;
}
static inline qword QwAdd(qword a, qword b)
{
    qword qw;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(qw) : "j"(a), "j"(b));
    return qw;
}
static inline qword QwDivX(qword a, qword g)
{
    qword qw;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(qw) : "j"(a), "j"(g));
    return qw;
}
static inline qword QwAddScaled(qword qwBase, qword qwD, qword g)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(qwBase), "j"(qwD), "j"(g));
    return qw;
}
static inline qword QwDot(qword a, qword b)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(a), "j"(b));
    return qw;
}
static inline qword QwLengthDot(qword v)
{
    qword qw = QwDot(v, v);
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline float GFromVf(qword qw)
{
    float g;
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(qw));
    return g;
}

static inline qword QwDivXUse(qword a, qword g, qword qwUse)
{
    qword qw;
    /* qwUse is an allocation-only operand */
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(qw) : "j"(a), "j"(g), "j"(qwUse));
    return qw;
}

qword func_0014F110(void *p, qword pos, qword posTarget)
{
    struct CLOCK *pclock = &D_002DDED0;
    VU_FLOAT u;
    struct FRAME frame;
    int ii, jj;
    qword dpos, posMin, v, posMax, w, r;
    dpos = QwSub(posTarget, pos);
    posMin = QwAdd(pos, D_002BD8F0);
    u.qw = QwOfG(&pclock->x10);
    v = QwDivXUse(dpos, u.qw, posMin);
    posMax = QwAdd(pos, D_002BD900);
    func_001AE478(&frame);
    func_0020FAA0(D_003DD490, posMin, posMax, func_0014F030, 0, &ii, &jj);
    w = func_0014EDA0(p, ii, jj, func_0014F040, pos, v, D_002BD8D8, GFromVf(QwLengthDot(v)) + D_002BD8DC);
    u.qw = QwOfG(&pclock->x10);
    r = QwAddScaled(pos, w, u.qw);
    func_001AE4A0(&frame, 2);
    return r;
}
