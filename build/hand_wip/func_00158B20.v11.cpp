// v11 (Claude agent, lane D40): FRESH Lilly-style rewrite, aligned 30 (v10 44), NO register pin. Helpers as in Lilly's files (VU_FLOAT {qword} + by-value VuFloat, QwAddScaled, QwProjectOut, QwDot/GFromVf, VuFloatFromMemWord, QwDivX), volatile SqrtF, plain i-loop over pdzg->adz[i] (mult kept like the target). Keys: (1) j-loop body `DZ *pdzJ = &pdzg->adz[j];` used as an allocation-only "r"(pdzJ) on the AddScaled asm, so the strength-reduced giv is the DZ base (target lw a0,0x8(s0) after blez, lwc1 0xC(a0)); (2) allocation-only "r"(iBest), "r"(i) on the tail vdiv with i at loop-function scope (i/psoBest/iBest t-regs now match); (3) `float gD0 = pzz->gD0; gMax = gD0 * D_002BDDE8` (no &D hoist into s4). Left: j-loop mfc1/lw af order, Dot qmfc2 temp t0 (target v0), tail pdzA/pdz order + regs, grf&1 / else FPU regs.
typedef int qword __attribute__((mode(TI)));
struct DZ { int x0; float g4; float g8; float gC; float g10; int pad[2]; DZ *pdzOther; int pad2[2]; };
struct ZZ { char pad[0x88]; float g88; char pad2[0xD0 - 0x8C]; float gD0; };
struct ALO { char pad[0xE8]; ZZ *pzz; };
struct SO { char pad[8]; ALO *palo; char pad2[0x80 - 0xC]; qword normal; char pad3[0x94 - 0x90]; float g94; char pad4[0x9C - 0x98]; int k9C; int padA0[4]; qword vB0; };
struct F { char pad[0x40]; qword v; SO *pso; qword *av; char pad2[0x60 - 0x58]; };
struct DZG { int x0; int cdz; DZ *adz; char pad[0x50 - 0xC]; int cso; SO **apso; int pad58[2]; F *af; };
struct CLOCK { float t; float dt; };
extern "C" {
extern CLOCK D_002DDED0;
extern float D_002BDDE8;
void func_00158988(DZG *pdzg, int grf);
void func_00158668(DZG *pdzg, DZ *pdz);
void func_00158B20(DZG *pdzg, int grf);
}
struct VU_FLOAT { qword qw; };
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline float GFromVf(qword qw)
{
    float g;
    __asm__("qmfc2 %0, %1" : "=r"(g) : "j"(qw));
    return g;
}
static inline qword QwDot(qword a, qword b)
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
static inline qword QwAddScaled(qword qwBase, qword qwVec, VU_FLOAT gScale)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(qwBase), "j"(qwVec), "j"(gScale.qw));
    return qw;
}
static inline qword QwAddScaledUse(qword qwBase, qword qwVec, VU_FLOAT gScale, const void *p)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(qwBase), "j"(qwVec), "j"(gScale.qw), "r"(p)); /* "r"(p): allocation-only */
    return qw;
}
static inline VU_FLOAT VuFloatFromMemWord(int n)
{
    VU_FLOAT v;
    __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "r"(n));
    return v;
}
static inline qword QwDivX(qword v, VU_FLOAT g)
{
    qword qw;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(qw) : "j"(v), "j"(g.qw));
    return qw;
}
static inline qword QwDivXUse(qword v, VU_FLOAT g, int n, int m)
{
    qword qw;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(qw) : "j"(v), "j"(g.qw), "r"(n), "r"(m)); /* "r"(n), "r"(m): allocation-only */
    return qw;
}
static inline float SqrtF(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(g)); return r; }
union VEC4 { qword q; float f[4]; };

void func_00158B20(DZG *pdzg, int grf)
{
    for (;;) {
        func_00158988(pdzg, grf);
        int iBest = -1;
        float gBest = 0.01f;
        SO *psoBest = 0;
        VEC4 vBest;
        vBest.f[2] = 0.0f;
        vBest.f[1] = 0.0f;
        vBest.f[0] = 0.0f;
        int i;
        for (i = 0; i < pdzg->cso; i++) {
            DZ *pdz = &pdzg->adz[i];
            if (pdz->pdzOther)
                continue;
            if (pdz->gC < 0.0001f)
                continue;
            SO *pso = pdzg->apso[i];
            if (pso->g94 < 0.0001f)
                continue;
            VEC4 v;
            v.q = pso->vB0;
            for (int j = 0; j < pdzg->cdz; j++) {
                DZ *pdzJ = &pdzg->adz[j];
                if (pdzJ->gC != 0.0f)
                    v.q = QwAddScaledUse(v.q, pdzg->af[j].av[i], VuFloat(pdzJ->gC), pdzJ);
            }
            v.q = QwProjectOut(v.q, pso->normal);
            float g = GFromVf(QwDot(v.q, v.q));
            if (gBest < g) {
                vBest.q = v.q;
                gBest = g;
                iBest = i;
                psoBest = pso;
            }
        }
        if (!psoBest)
            break;
        DZ *pdzA = &pdzg->adz[iBest];
        DZ *pdz = &pdzg->adz[pdzg->cdz];
        F *pf = &pdzg->af[pdzg->cdz];
        pdz->pdzOther = pdzA;
        pdzA->pdzOther = pdz;
        pdz->g10 = -SqrtF(gBest);
        pf->pso = psoBest;
        pf->v = QwDivXUse(vBest.q, VuFloatFromMemWord(*(int *)&pdz->g10), iBest, i);
        pdz->x0 = 1;
        if (psoBest->k9C == 14) {
            ZZ *pzz = psoBest->palo->pzz;
            if (grf & 1) {
                float gMin = -pzz->g88 * pzz->gD0 * D_002DDED0.dt;
                float g = __builtin_fabsf(pdz->pdzOther->gC);
                pdz->g8 = psoBest->g94 * (g < gMin ? gMin : g);
            } else {
                float gD0 = pzz->gD0;
                float gMax = gD0 * D_002BDDE8;
                float g = psoBest->g94 * __builtin_fabsf(pdz->pdzOther->gC);
                pdz->g8 = gMax < g ? gMax : g;
            }
        } else {
            pdz->g8 = __builtin_fabsf(pdz->pdzOther->gC) * psoBest->g94;
        }
        pdz->g4 = -pdz->g8;
        func_00158668(pdzg, pdz);
    }
}
