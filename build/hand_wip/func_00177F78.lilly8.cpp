// laneF25v3 (Claude agent): aligned 57 (laneF24v8 74). No pins. (1) hit block: GXOfQwJ (allocation-only "j") on the gClose dot, so the dot result prefers VF and the normal reload/addscaled get the target vf3/vf2 (65). (2) hit-block length mtc1 clobbers dead a2 AND a0 (GPR reload round robin: v1 qmfc2, 63). (3) loop: `float sGap = GXOfQwJ(qwLen); sGap = GMax(0.0f, sGap - rO - rS);` (57).
// laneF24v8 (Claude agent): aligned 74 (laneF23v4 118). No pins. (1) top QwNormalizeEps: "+r"(fb) output on the mtc1 asm (qmtc2 lands in the bc1t delay slot) and a dead-v0 clobber on its vsqrt (fb in v1). (2) hit block: fallback pointer set before the projection, GXOfQwJ (allocation-only "j") so qwLen stays in VF, dead-a2 clobber on the first mtc1 and dead a0/a1 on the second (reload round robin). (3) loop: `qword dposCopy = dpos;` used by QwLength(dirNow) (target vmove + 0xC0 save); normal normalize uses QW_LENGTH_COPY (allocation-only tied VF copy output + two "r" operands: lq/qmtc2 through a GPR, vdiv reads the VF copy), local fallback pointer set before it, GXOfQwJ for sGap. (4) round robin: accel VU_FLOAT clobbers dead a0/a1, side compare mtc1 clobbers dead a2.
// laneF23v4 (Claude agent): aligned 118 (laneF22v2 141). No pins. (1) loop fallbacks go through one function-scope `const qword *pqwZero` assigned at both loop sites (set twice, so loop.c no longer combines/hoists lo(D_002A2DA0); hi stays in fp as in the target). (2) top QwNormalizeEps: fallback held in a GPR via allocation-only "r"(fb) on the mtc1 asm, eps parameter with allocation-only "f"(eps) on the projection vsub. (3) commented dead-GPR clobbers ($4 / $2) on three VU_FLOAT qmtc2 asms advance reload's round robin. (4) empty-asm GPR copy of vGoal for p->v plus a commented empty "memory" barrier after dv.
// laneF22v2 (Claude agent): aligned 141. v1 + accel written as dv, `qword pos = p->pos;`, dp, then QwBlend(dv, .., dp, ..).
// laneF22v1 (Claude agent): aligned 142 (laneF21v2 154). `float gNear = 1.0f; gNear -= sGap / D_002BE670;`: gNear is set twice, so its 1.0f is not a loop movable and the two 1.0f loads no longer combine; both stay in the loop as in the target. No pins, no new asm.
// laneF21v2 (Claude agent): aligned 154 (laneF20v3 163). posNext (QwIntegrate) computed before vNew (target stores the VU_FLOAT temps dt, dt*dt*.5, dt in that order), and `float half = 0.5f;` declared before the dt load (target loads 0.5 into f1 first). No pins.
// laneF20v3 (Claude agent): aligned 163. v2 + GEvaluateClqLm reads gMin and gMax into locals before the clamp (target loads gMax in the bc1f delay slot).
// laneF20v2 (Claude agent): aligned 183. v1 + QwDot takes const-ref params.
// laneF20v1 (Claude agent): aligned 188. QwLength writes the sqrt result to a new pseudo (`"=j"(r) : "j"(d)`, as in func_001856C0) instead of the tied in-place qw, so the length is allocated vf1 and the dead vfOne vf2 as in the target.
// laneF19v2 (Claude agent): aligned 200. v1 + QwNormalize writes the fallback first and overwrites it: `r = D_002A2DA0; if (len < eps) ; else r = div;` (target branch is bc1t over the vdiv).
// laneF19v1 (Claude agent): aligned 201. func_001E66C8 results in their own statements before the func_001E7380 calls (the curve address is then expanded after the call, so gcse/sched give the s0/s6 hi copies and the s3/s4 order).
// laneF18v1 (Claude agent): aligned 215, frame 0x1C0 matches. From laneI5v1: unused block VECs in the loop and the hit block (target slot 0x50), qword vNext, separate vNew/vNext (vNext is the target 0xB0 spill), VU_FLOAT(dt) temps, normal stored before normalize.
// laneI5v1 (Claude agent): aligned 225 (laneI4v3 221), structure experiment: plain qword posActor plus an empty-asm copy into qwActor gives the target spill pattern (sq v0 / lq s2 from the spill slot), but the spill area starts at 0x80 instead of 0x90 and the frame is 0x190 instead of 0x1C0.
// func_00177F78 (Claude agent, lane I4): fresh rewrite in the style of Lilly's matched files (src/hand/func_00178EE0.cpp).
// laneI4v3 (Claude agent): aligned 221. v2 + vadda operand order.
typedef int qword __attribute__((mode(TI)));
union VEC
{
    qword qw;
    float f[4];
};
struct VTENT
{
    short delta, pad;
    void *pfn;
};
struct CURVE
{
    char pad[0xE4];
    int fWrap;
};
struct BODY;
struct CONTEXT
{
    char pad[0x118];
    BODY *pbodyFirst;
};
struct BODY
{
    void *pobj;
    float dz;
    float sRadius;
    float gMass;
    CONTEXT *pctx;
    char pad14[0x4C];
    BODY *pbodyNext;
};
struct GROUP
{
    char pad[0xDC];
    BODY *pbody;
};
struct OBJECT
{
    char pad[0xC];
    VTENT *pvt;
    char pad10[0xD8];
    GROUP *pgroup;
    char padEC[0xC4];
    qword axis;
    char pad1C0[0xD4];
    CURVE *pcrvPrimary;
};
struct S
{
    char pad[0x10];
    OBJECT *pactor;
    char pad14[0x1C];
    CURVE *pcrv;
    float s;
    int fReverse;
    int fHold;
    int fNoCollide;
    char pad44[8];
    int mode;
    char pad50[4];
    CURVE *pcrvExtra;
    int modeExtra;
    float sExtra;
    char pad60[0x10];
    float sSeparation;
    char pad74[0xC];
    qword pos;
    qword v;
    int fInit;
};
struct CLQ
{
    float g0, g1, g2;
};
struct LM
{
    float gMin, gMax;
};
struct CLOCK
{
    float t, dt;
};
extern "C" {
extern char D_003DD020[];
extern CLOCK D_002DDED0;
extern qword D_002A2DA0, D_002A2DC0, D_002A2DD0;
extern float D_002BE630, D_002BE634, D_002BE658, D_002BE65C, D_002BE660, D_002BE664, D_002BE668, D_002BE66C, D_002BE670, D_002BE674, D_002BE690;
extern CLQ D_002BE640, D_002BE680;
extern LM D_002BE650, D_002BBB60;
qword func_001A62E8(void *pobj);
float func_001E66C8(CURVE *pcrv, float s);
float func_001E6648(CURVE *pcrv);
void func_001E7380(CURVE *pcrv, qword pos, float s, void *pv, VEC *ppos, VEC *pdir, float *pg, float *ps);
void func_001E6F10(CURVE *pcrv, float s, VEC *ppos, VEC *pdir);
int func_00178D00(S *p);
void func_0011EE08(qword a, qword b, qword c, VEC *pv, float *pg0, float *pg1);
int func_001C0B50(CONTEXT *pctx, qword pos, VEC *pv);
}
struct VU_FLOAT
{
    qword qw;
    VU_FLOAT(float g) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(g)); }
    VU_FLOAT(float g, int) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(g) : "$4"); } /* clobber of the dead a0 */
    VU_FLOAT(float g, char) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(g) : "$4", "$5"); } /* clobbers of the dead a0/a1 */
    VU_FLOAT(const float *pg) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "rV"(*(const int *)pg)); }

};
static inline float GXOfQw(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw));
    return x;
}
static inline float GXOfQwJ(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw), "j"(qw)); /* allocation-only "j"(qw): the vector stays in a VF register */
    return x;
}
static inline float GXOfQwA2(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw) : "$6"); /* clobber of the dead a2 */
    return x;
}
static inline float GXOfQwA0A1(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw), "j"(qw) : "$4", "$5"); /* allocation-only "j"(qw); clobbers of the dead a0/a1 */
    return x;
}
static inline float GXOfQwT(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw) : "$6", "$4"); /* clobbers of the dead a2/a0 */
    return x;
}
static inline float GXOfQwSkip(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw) : "$6"); /* clobbers of dead registers */
    return x;
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwDot(const qword &a, const qword &b)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(a), "j"(b));
    return qw;
}
static inline qword QwProjectOut(qword v, qword n)
{
    qword d = QwDot(v, n);
    qword al, ac;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(al) : "j"(d), "j"(n));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(ac) : "j"(v), "j"(al));
    return ac;
}
static inline qword QwProjectOutJ(qword v, qword n)
{
    qword d = QwDot(v, n);
    qword al, ac;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(al) : "j"(d), "j"(n), "j"(n)); /* allocation-only repeat of n */
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(ac) : "j"(v), "j"(al));
    return ac;
}
static inline qword QwLength(qword v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    qword r;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(qw));
    return r;
}
static inline qword QwLengthV0(qword v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    qword r;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(qw) : "$2"); /* clobber of the dead v0 */
    return r;
}
static inline qword QwLengthR(qword v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v), "r"(v), "r"(v)); /* allocation-only "r"(v) operands: the input is loaded through a GPR */
    qword r;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(qw));
    return r;
}
/* length of v; copy receives v itself (allocation-only tied output, never written); the "r"(v) operands load v through a GPR */
#define QW_LENGTH_COPY(len, copy, v) \
    { \
        qword qwSq_, vfOne_; \
        __asm__("vmul.xyz %0, %3, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" \
                : "=j"(qwSq_), "=j"(vfOne_), "=j"(copy) : "2"(v), "r"(v), "r"(v)); \
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(len) : "j"(qwSq_)); \
    }
static inline qword QwLengthXY(qword v)
{
    qword qw;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(qw) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline qword QwDivLength(qword v, qword qwLen)
{
    qword qw;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(qw) : "j"(qwLen), "j"(v));
    return qw;
}
static inline qword QwNormalize(qword v)
{
    qword qwLen = QwLength(v);
    qword fb = D_002A2DA0;
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qwLen), "r"(fb)); /* allocation-only "r"(fb): the fallback is held in a GPR */
    qword r = fb;
    if (x < 0.0001f)
        ;
    else
        r = QwDivLength(v, qwLen);
    return r;
}
static inline qword QwNormalizeEps(qword v, float eps)
{
    qword qwLen = QwLengthV0(v);
    qword fb = D_002A2DA0;
    float x;
    __asm__("mtc1 %2, %0" : "=f"(x), "+r"(fb) : "r"(qwLen)); /* allocation-only "+r"(fb): the fallback is held in a GPR */
    qword r;
    if (x < eps)
        r = fb;
    else
        r = QwDivLength(v, qwLen);
    return r;
}
static inline qword QwProjectOutEps(qword v, qword n, float eps)
{
    qword d = QwDot(v, n);
    qword al, ac;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(al) : "j"(d), "j"(n));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(ac) : "j"(v), "j"(al), "f"(eps)); /* allocation-only "f"(eps): the epsilon is loaded first */
    return ac;
}
struct VV
{
    qword q;
    VV() {}
    VV(const qword &v) { q = v; }
    operator qword() const { return q; }
};
static inline VV NormalizeSafe(VV v, VV fallback)
{
    qword len = QwLengthV0(v);
    if (GXOfQw(len) < 0.0001f)
        return fallback;
    return QwDivLength(v, len);
}
static inline VV NormalizeSafeN(VV v, VV fallback)
{
    qword len = QwLength(v);
    if (GXOfQw(len) < 0.0001f)
        return fallback;
    return QwDivLength(v, len);
}
static inline VV DivSafe(VV v, VV len, VV fallback)
{
    if (GXOfQw(len) < 0.0001f)
        return fallback;
    return QwDivLength(v, len);
}
static inline void NormalizeVec(VEC &vec)

{
    qword qwLen = QwLength(vec.qw);
    if (GXOfQw(qwLen) < 0.0001f)
        vec.qw = D_002A2DA0;
    else
        vec.qw = QwDivLength(vec.qw, qwLen);
}
static inline qword QwScaleX(qword v, const VU_FLOAT &g)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qw) : "j"(v), "j"(g.qw));
    return qw;
}
static inline qword QwAddScaled(qword a, qword b, const VU_FLOAT &g)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(a), "j"(b), "j"(g.qw));
    return qw;
}
static inline qword QwBlend(qword a, const VU_FLOAT &ga, qword b, const VU_FLOAT &gb)
{
    qword qw;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(qw) : "j"(a), "j"(ga.qw), "j"(b), "j"(gb.qw));
    return qw;
}
static inline qword QwIntegrate(qword pos, qword v, const VU_FLOAT &g1, qword a, const VU_FLOAT &g2)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x"
            : "=j"(qw) : "j"(pos), "j"(v), "j"(g1.qw), "j"(a), "j"(g2.qw));
    return qw;
}
static inline qword QwCross(qword a, qword b)
{
    qword qw;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(qw) : "j"(a), "j"(b));
    return qw;
}
static inline float GZOfQw(qword qw)
{
    float z;
    __asm__("pextuw %0, $zero, %1" : "=r"(z) : "r"(qw));
    return z;
}
static inline float GEvaluateClqLm(CLQ *pclq, LM *plm, float x)
{
    float g = pclq->g0 + x * (pclq->g1 + x * pclq->g2);
    float gMin = plm->gMin;
    float gMax = plm->gMax;
    if (g < gMin)
        g = gMin;
    else if (gMax < g)
        g = gMax;
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
static inline float GMax(float a, float b)
{
    float g;
    __asm__("max.s %0, %1, %2" : "=f"(g) : "f"(a), "f"(b));
    return g;
}
static inline qword QwVelocity(void *pv)
{
    OBJECT *pobj = (OBJECT *)pv;
    VTENT *pvte = &pobj->pvt[33];
    return ((qword (*)(void *))pvte->pfn)((char *)pobj + pvte->delta);
}

extern "C" void func_00177F78(S *p)
{
    VEC point, dir, next, nextDir;
    const qword *pqwZero;
    qword posActor = func_001A62E8(p->pactor);
    register qword qwActor asm("$18") = posActor;

    BODY *pbody = 0;
    if (p->pactor->pgroup)
        pbody = p->pactor->pgroup->pbody;
    CONTEXT *pctx = 0;
    if (pbody)
        pctx = pbody->pctx;
    int fReverse = p->fReverse;
    float s;
    if (fReverse)
        s = p->s - D_002BE634;
    else
        s = p->s + D_002BE634;
    float sCurve = func_001E66C8(p->pcrv, s);
    func_001E7380(p->pcrv, qwActor, sCurve, D_003DD020, &point, &dir, 0, &p->s);
    if (p->mode == 1 || p->mode == 4)
    {
        fReverse = p->modeExtra != 2;
        if (fReverse)
            s = p->sExtra - D_002BE634;
        else
            s = p->sExtra + D_002BE634;
        float sCurve = func_001E66C8(p->pcrvExtra, s);
        func_001E7380(p->pcrvExtra, qwActor, sCurve, D_003DD020, &point, &dir, 0, &p->sExtra);

    }
    {
        float eps = 0.0001f;
        dir.qw = NormalizeSafeN(QwProjectOutEps(dir.qw, D_002A2DC0, eps), D_002A2DA0);

    }
    p->sSeparation = GXOfQw(QwLengthXY(QwSub(point.qw, posActor)));
    float ds = GEvaluateClqLm(&D_002BE640, &D_002BE650, p->sSeparation);
    if (fReverse)
        ds = -ds;
    float gSpeed;
    if (func_00178D00(p))
    {
        gSpeed = 0.0f;
        nextDir.qw = D_002A2DA0;
        next.qw = posActor;
    }
    else
    {
        gSpeed = D_002BE630;
        switch (p->mode)
        {
        case 0:
        case 2:
        case 3:
            if (p->pcrv == p->pactor->pcrvPrimary)
            {
                float sMin = -p->s;
                float sMax = func_001E6648(p->pcrv) - p->s;
                float dsClamp = GClamp(ds, sMin, sMax);
                if (ds != dsClamp)
                    gSpeed = 0.0f;
                next.qw = QwAddScaled(point.qw, dir.qw, VU_FLOAT(dsClamp, 0));
                nextDir.qw = dir.qw;
            }
            else
            {
                float sNext;
                if (p->pcrv->fWrap)
                {
                    sNext = func_001E66C8(p->pcrv, p->s + ds);
                }
                else
                {
                    float sMin = -p->s;
                    float sMax = func_001E6648(p->pcrv) - p->s;
                    float dsClamp = GClamp(ds, sMin, sMax);
                    if (ds != dsClamp)
                        gSpeed = 0.0f;
                    sNext = p->s + dsClamp;
                }
                func_001E6F10(p->pcrv, sNext, &next, &nextDir);
            }
            break;
        case 1:
        case 4:
            next.qw = QwAddScaled(point.qw, dir.qw, VU_FLOAT(ds));
            nextDir.qw = dir.qw;
            break;
        }
    }
    if (fReverse)
        nextDir.qw = QwScaleX(nextDir.qw, VU_FLOAT(-1.0f));
    qword vGoal = QwScaleX(nextDir.qw, VU_FLOAT(gSpeed, 0));
    qword vGoalCopy;
    __asm__("qmfc2.ni %0, %1" : "=r"(vGoalCopy) : "j"(vGoal)); /* GPR copy of vGoal */

    if (p->fInit)
    {
        p->v = vGoalCopy;
        p->pos = next.qw;
        p->fInit = 0;
    }
    qword dv = QwSub(vGoal, p->v);
    __asm__ volatile("" : : : "memory"); /* empty asm: barrier */
    qword pos = p->pos;
    qword dp = QwSub(next.qw, pos);
    qword accel = QwBlend(dv, VU_FLOAT(&D_002BE658), dp, VU_FLOAT(&D_002BE65C));
    if (!p->fNoCollide)
    {
        BODY *pbodySelf = p->pactor->pgroup->pbody;
        for (BODY *pbodyOther = pctx->pbodyFirst; pbodyOther; pbodyOther = pbodyOther->pbodyNext)
        {
            if (pbodyOther->sRadius == 0.0f)
                continue;
            if (pbodyOther->gMass == 0.0f)
                continue;
            void *pobj = pbodyOther->pobj;
            if (pobj == p->pactor)
                continue;
            VEC posOther;
            VEC vecUnused;
            posOther.qw = func_001A62E8(pobj);
            posOther.f[2] += pbodyOther->dz;
            qword dpos = QwSub(posActor, posOther.qw);
            if (__builtin_fabsf(GZOfQw(dpos)) > D_002BE660)
                continue;
            qword vOther = QwVelocity(pobj);
            qword posPredict = QwAddScaled(posOther.qw, vOther, VU_FLOAT(&D_002BE664));
            dpos = QwProjectOutJ(dpos, D_002A2DC0);
            qword dposCopy = dpos;
            qword dposLater = QwProjectOut(QwSub(p->pos, posPredict), D_002A2DC0);

            VEC normal;
            func_0011EE08(D_002A2DD0, dpos, dposLater, &normal, 0, 0);
            const qword *pqwZeroHere = &D_002A2DA0;
            qword normalCopy;
            qword qwLen;
            QW_LENGTH_COPY(qwLen, normalCopy, normal.qw);
            if (GXOfQw(qwLen) < 0.0001f)
                normal.qw = *pqwZeroHere;
            else
                normal.qw = QwDivLength(normalCopy, qwLen);
            float sGap = GXOfQwJ(qwLen);
            sGap = GMax(0.0f, sGap - pbodyOther->sRadius - pbodySelf->sRadius);
            float gMass = pbodyOther->gMass / (pbodyOther->gMass + pbodySelf->gMass);
            if (sGap < D_002BE668)
                accel = QwAddScaled(accel, normal.qw, VU_FLOAT(gMass * (1.0f - sGap / D_002BE668) * D_002BE66C, (char)0));
            if (sGap < D_002BE670)
            {
                float gNear = 1.0f;
                gNear -= sGap / D_002BE670;
                pqwZero = &D_002A2DA0;
                qword dirNow = DivSafe(dpos, QwLength(dposCopy), *pqwZero);

                float gSteer = gNear * GEvaluateClqLm(&D_002BE680, &D_002BBB60, GXOfQw(QwDot(dirNow, p->pactor->axis)));
                if (gSteer == 0.0f)
                    continue;
                VEC side;
                side.qw = QwCross(D_002A2DC0, nextDir.qw);
                if (p->pcrv != p->pactor->pcrvPrimary && GXOfQwSkip(QwDot(normal.qw, side.qw)) < 0.0f)
                    gSteer = -gSteer;
                accel = QwAddScaled(accel, QwCross(normal.qw, D_002A2DC0), VU_FLOAT(gMass * gSteer * D_002BE674));
            }
        }
    }
    float half = 0.5f;
    float dt = D_002DDED0.dt;
    accel = QwProjectOut(accel, D_002A2DC0);
    qword posNext = QwIntegrate(p->pos, p->v, VU_FLOAT(dt), accel, VU_FLOAT(dt * (dt * half)));
    qword vNew = QwAddScaled(p->v, accel, VU_FLOAT(dt));
    qword vNext = vNew;
    if (!p->fNoCollide)
    {
        VEC posHit;
        VEC vecUnused2;
        if (func_001C0B50(pctx, posNext, &posHit))
        {
            VEC normal;
            pqwZero = &D_002A2DA0;
            normal.qw = QwProjectOut(QwSub(posHit.qw, posNext), D_002A2DC0);
            qword qwLen = QwLength(normal.qw);
            if (GXOfQwT(qwLen) < 0.0001f)
                normal.qw = *pqwZero;
            else
                normal.qw = QwDivLength(normal.qw, qwLen);
            if (D_002BE690 < GXOfQwA0A1(qwLen))
            {
                float gClose = GXOfQwJ(QwDot(vNew, normal.qw));
                posNext = posHit.qw;
                if (gClose < 0.0f)
                    vNext = QwAddScaled(vNew, normal.qw, VU_FLOAT(-gClose));
            }
        }
    }
    p->pos = posNext;
    p->v = vNext;
}
