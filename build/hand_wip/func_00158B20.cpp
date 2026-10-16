// NEAR MISS (Claude agent): structure/logic complete (DZG constraint add loop, Sly1 SolveDzg family). Remaining: our loop.c hoists %hi(D_002BDDE8) into s3 (+s4, frame 0x90 vs 0x80); offsets then shift.
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
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(int *)&f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };

static inline qword AddScaled(VU_VECTOR a, VU_VECTOR b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a.q), "j"(b.q), "j"(s.q));
    return r;
}
static inline qword DotV(qword a, qword b)
{
    qword r, t;
    __asm__("vmul.xyz %1, %2, %3\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z"
            : "=j"(t), "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float Dot(qword a, qword b)
{
    float g;
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(DotV(a, b)));
    return g;
}
static inline qword ProjectPerp(qword v, qword n)
{
    qword r = DotV(v, n);
    __asm__("vmulx.xyzw %0, %1, %0x" : "+j"(r) : "j"(n));
    __asm__("vsub.xyzw %0, %1, %0" : "+j"(r) : "j"(v));
    return r;
}
static inline qword DivF(qword v, VU_FLOAT s)
{
    qword r;
    __asm__("vdiv Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, Q" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}

void func_00158B20(DZG *pdzg, int grf)
{
    for (;;) {
        int i, iBest;
        float gBest;
        SO *psoBest;
        union { qword q; float f[4]; } vBest;
        func_00158988(pdzg, grf);
        iBest = -1;
        gBest = 0.01f;
        psoBest = 0;
        vBest.f[2] = 0.0f;
        vBest.f[1] = 0.0f;
        vBest.f[0] = 0.0f;
        for (i = 0; i < pdzg->cso; i++) {
            DZ *pdz = &pdzg->adz[i];
            SO *pso;
            union { qword q; float f[4]; } v;
            int j;
            float g;
            if (pdz->pdzOther)
                continue;
            if (pdz->gC < 0.0001f)
                continue;
            pso = pdzg->apso[i];
            if (pso->g94 < 0.0001f)
                continue;
            v.q = pso->vB0;
            for (j = 0; j < pdzg->cdz; j++) {
                float gj = pdzg->adz[j].gC;
                if (gj != 0.0f)
                    v.q = AddScaled(v.q, pdzg->af[j].av[i], VU_FLOAT(gj));
            }
            v.q = ProjectPerp(v.q, pso->normal);
            g = Dot(v.q, v.q);
            if (gBest < g) {
                vBest.q = v.q;
                gBest = g;
                iBest = i;
                psoBest = pso;
            }
        }
        if (!psoBest)
            break;
        {
            DZ *pdzA = &pdzg->adz[iBest];
            DZ *pdz = &pdzg->adz[pdzg->cdz];
            F *pf = &pdzg->af[pdzg->cdz];
            pdz->pdzOther = pdzA;
            pdzA->pdzOther = pdz;
            pdz->g10 = -__builtin_sqrtf(gBest);
            pf->pso = psoBest;
            pf->v = DivF(vBest.q, VU_FLOAT(pdz->g10));
            pdz->x0 = 1;
            if (psoBest->k9C == 14) {
                ZZ *pzz = psoBest->palo->pzz;
                if (grf & 1) {
                    float gMin = -pzz->g88 * pzz->gD0 * D_002DDED0.dt;
                    float g = __builtin_fabsf(pdz->pdzOther->gC);
                    pdz->g8 = psoBest->g94 * (g < gMin ? gMin : g);
                } else {
                    float gMax = pzz->gD0 * D_002BDDE8;
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
}
