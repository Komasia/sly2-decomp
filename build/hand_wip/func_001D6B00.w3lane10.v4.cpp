typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
union MATRIX4 { qword r[4]; float m[4][4]; };
struct MATRIX3 { qword r[3]; };
struct XF { MATRIX4 mat; MATRIX4 matWorld; };
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
struct SO;
struct VECTOR4 { qword q; VECTOR4(const qword &v) { q = v; } VECTOR4(const VECTOR4 &v) { q = v.q; } };
struct BASIC {
    void *pframe, *psidebag, *prefnodeFirst;
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04(); virtual void V05(); virtual void V06();
};
struct LO : BASIC {
    virtual void Init(); virtual void Add(); virtual void V09(); virtual void V10(); virtual void V11(); virtual void V12();
    virtual void V13(); virtual void V14(); virtual void V15(); virtual void V16(); virtual void V17(); virtual void V18();
    virtual void V19(); virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23(); virtual void V24();
    virtual void V25(); virtual void V26(); virtual void V27(); virtual void V28(); virtual void V29();
    virtual void RotateToMat(MATRIX3 *pmat);                    // 30
    virtual void V31();
    virtual XF *PxfLocal(MATRIX4 *pmatLocal);                   // 32
    virtual void V33(); virtual void V34();
    virtual void SetVelocity(qword v);                           // 35
    virtual void SetAngularVelocity(qword w);                    // 36
    virtual void V37(); virtual void V38(); virtual void V39(); virtual void V40(); virtual void V41(); virtual void V42();
    virtual void V43(); virtual void V44(); virtual void V45(); virtual void V46(); virtual void V47(); virtual void V48();
};
struct SO : LO {
    char pad10[0x250];
    float svLaunch;                                              // 0x260
    virtual void V49(); virtual void V50(); virtual void V51(); virtual void V52(); virtual void V53(); virtual void V54();
    virtual void V55(); virtual void V56(); virtual void V57(); virtual void V58(); virtual void V59(); virtual void V60();
    virtual void V61(); virtual void V62(); virtual void V63(); virtual void V64(); virtual void V65(); virtual void V66();
    virtual void V67(); virtual void V68(); virtual void V69(); virtual void V70(); virtual void V71(); virtual void V72();
    virtual void V73(); virtual void V74(); virtual void V75(); virtual void V76(); virtual void V77();
    virtual void SetTarget(SO *pso, const VECTOR4 &pos);         // 78
};
struct LAUNCH {
    char pad0[0x50];
    qword posTarget;            // 0x50
    SO *psoSource;              // 0x60
    char pad64[0xC];
    CLQ clqPredict;             // 0x70
    LM lmPredict;               // 0x80
    char pad88[8];
    CLQ clqOffset;              // 0x90
    LM lmOffset;                // 0xA0
    LM lmSpin;                  // 0xA8
    float pitch;                // 0xB0
};
extern XF D_002C44F0;
extern qword D_002A2DA0;
extern char D_003DD490[];
extern "C" {
qword func_001A62E8(SO *);
MATRIX4 *func_0011C168(MATRIX4 *, MATRIX4 *, MATRIX4 *);
void *func_002333B4(void *, int, int);
void func_002309E8(XF *, int, MATRIX4 *, MATRIX4 *, float);
int func_00132B10(SO *, int);
void func_0013BC60(SO *, LAUNCH *);
void func_00134320(void *, SO *);
void func_001F5720(SO *, void *);
void func_001F57C0(SO *, void *);
void func_001A58D0(SO *, int, int);
void func_001F4898(SO *, qword);
qword func_001F5860(SO *);
qword func_001D6848(float, qword, qword, qword);
void func_0011B7E0(MATRIX3 *, qword);
float func_0011D448(float, float);
}
static inline float GRandInRange(const LM &lm) { return func_0011D448(lm.gMin, lm.gMax); }
extern "C" {
}
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
struct VU_FLOAT {
    qword q;
    VU_FLOAT() {}
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
};
// a VU float straight from a float in memory (loaded as an integer word)
static inline VU_FLOAT VuFloatFromWord(const float &f) { VU_FLOAT g; __asm__("qmtc2.ni %1,%0" : "=j"(g.q) : "r"(*(const int *)&f)); return g; }
struct VECTOR { qword q; VECTOR(float x, float y, float z) {
    qword t; __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z)); } };
// a GPR vector moved into a VU register
static inline qword ToVf(qword v) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(v)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub2(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b), "j"(a)); return r; }
static inline qword Point(const MATRIX4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
static inline qword Length(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline float X(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline qword Div(qword v, qword l) { qword r; __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(l)); return r; }
// unit vector along v (in place of its length), or the default axis when v is too short
static inline qword Normalize(qword v)
{
    qword l = Length(v);
    qword fallback = D_002A2DA0;
    if (X(l) < 0.0001f)
        l = fallback;
    else
        l = Div(v, l);
    return l;
}
static inline qword Length2(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0,%1,%1" : "=j"(d) : "j"(v));
    __asm__("vaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(d), "=&j"(one));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Normalize2(qword v)
{
    qword l = Length2(v);
    qword fallback = D_002A2DA0;
    if (X(l) < 0.0001f)
        l = fallback;
    else
        l = Div(v, l);
    return l;
}
static inline qword NormalizeTo(qword v)
{
    qword fallback = D_002A2DA0;
    qword l = Length(v);
    if (X(l) < 0.0001f)
        goto tiny;
    return Div(v, l);
tiny:
    return fallback;
}
static inline qword AddScaled(VV base, VU_FLOAT g, qword v)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base.q), "j"(v), "j"(g.q));
    return r;
}
static inline qword Scale(qword v, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(g.q)); return r; }
static inline qword Scale(VU_FLOAT g, qword v) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(g.q)); return r; }
static inline qword ToGpr(qword v) { qword r; __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(v)); return r; }
static inline float GFromClq(const CLQ &clq, float g) { return clq.g0 + g * (clq.g1 + g * clq.g2); }
static inline float GClamp(float g, float gMin, float gMax) { if (g < gMin) g = gMin; else if (gMax < g) g = gMax; return g; }
static inline float GClampR(float g, float gMin, float gMax) { if (g < gMin) return gMin; if (gMax < g) return gMax; return g; }
static inline void LoadIdentity(MATRIX4 *pm) { func_002333B4(pm, 0, sizeof(*pm)); pm->m[0][0] = pm->m[1][1] = pm->m[2][2] = pm->m[3][3] = 1.0f; }

extern "C" void func_001D6B00(LAUNCH *plaunch, SO *pso)
{
    MATRIX4 matParent;
    qword posStart = func_001A62E8(pso);
    VV posOrigin(posStart);
    SO *psoSource = plaunch->psoSource;
    XF *pxf;
    if (psoSource)
        pxf = psoSource->PxfLocal(&matParent);
    else {
        pxf = &D_002C44F0;
        LoadIdentity(&matParent);
    }
    qword dpos;
    float dist;
    {
        MATRIX4 mat;
        func_0011C168(&mat, &pxf->matWorld, &matParent);
        dpos = Sub(Point(mat, plaunch->posTarget), posStart);
        dist = X(Length(dpos));
        float t = GClamp(GFromClq(plaunch->clqPredict, dist), plaunch->lmPredict.gMin, plaunch->lmPredict.gMax);
        if (t != 0.0f) {
            MATRIX4 matPredict;
            func_002309E8(pxf, 0, &mat, 0, t);
            func_0011C168(&matPredict, &mat, &matParent);
            dpos = Sub(Point(matPredict, plaunch->posTarget), posStart);
        }
    }
    dist = X(Length(dpos));
    float offset = GClampR(GFromClq(plaunch->clqOffset, dist), plaunch->lmOffset.gMin, plaunch->lmOffset.gMax);
    qword posAim;
    qword posLaunch = AddScaled(posOrigin, VU_FLOAT(offset), Normalize(dpos));
    posAim = ToGpr(posLaunch);
    if (func_00132B10(pso, 0x4F)) {
        func_0013BC60(pso, plaunch);
        func_00134320(D_003DD490, pso);
    }
    pso->Add();
    func_001F5720(pso, 0);
    func_001F57C0(pso, 0);
    func_001A58D0(pso, 0, 3);
    if (func_00132B10(pso, 0x52)) {
        func_001F4898(pso, VECTOR(pso->svLaunch, 0.0f, 0.0f).q);
    } else if (func_00132B10(pso, 0x51)) {
        qword v = Scale(VuFloatFromWord(pso->svLaunch), Normalize2(Sub2(posAim, posStart)));
        pso->SetVelocity(v);
        MATRIX3 mat;
        func_0011B7E0(&mat, v);
        pso->RotateToMat(&mat);
    } else {
        qword vAccel = func_001F5860(pso);
        qword v = func_001D6848(plaunch->pitch, posStart, posLaunch, vAccel);
        pso->SetVelocity(v);
    }
    if (plaunch->lmSpin.gMax > 0.0f) {
        float g = GRandInRange(plaunch->lmSpin);
        float x = func_0011D448(-1.0f, 1.0f);
        float y = func_0011D448(-1.0f, 1.0f);
        float z = func_0011D448(-1.0f, 1.0f);
        qword w = Scale(NormalizeTo(ToVf(VECTOR(x, y, z).q)), VU_FLOAT(g));
        pso->SetAngularVelocity(w);
    }
    if (func_00132B10(pso, 0x50)) {
        pso->SetTarget(plaunch->psoSource, VECTOR4(plaunch->posTarget));
    }
}
