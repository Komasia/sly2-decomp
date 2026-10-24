// v9 (Claude agent, lane D34): v8 + two allocation-only operands, no other change: "r"(pdzJ) on the j-loop AddScaled asm (pdzJ a0 / k a1 like the target) and "r"(pso) on the ProjectPerp vmulx asm (pso a3 like the target): 59 -> 48. Left (greg -da): i (pseudo 118, 23 refs / 64 insns, prio 1.44) outranks the j*0x60 giv (1.25) and the i*16 giv (0.74), and iBest has a hard-reg preference for a2 from the tail mult (set_preference: iBest dies in `mult a2,iBest,s2`). An extra "r"(iBest) on DivF kills that preference (iBest t5, i+1 t3, cso t4 all right) but then pso takes a2: 53. Pin moved from psoBest to i ($10): 75. Swapped pdzA/pdz decls: target tail shape but 67.
// v8 (Claude agent, lane D33): STRUCTURAL LEAD, aligned 59 (v7 56). The i-loop and j-loop code shapes now match the target exactly: `DZ *adz = pdzg->adz` read in an `if (i < pdzg->cso)` guard around the for (so the i-body has no adz mem load and the t7 load lands after the blez like the target, and cso is still hoisted with the daddu t4 copy), plus a j-loop POINTER iterator `pdzJ = pdzg->adz` (fresh lw a0,0x8(s0), lwc1 0xC(pdzJ), +0x28). Left: register allocation only (i-loop vars get a2/a3/t4/t5 where the target has t2..t5; j-loop counter/pointer a0/a1 swapped), plus the old grf&1 FPU regs. No pin: 60; iBest $13: 64; i $10: 76.
// v7 (Claude agent, lane E24): v6 with VU_FLOATV non-volatile (lw 0x60 can move above the qmtc2): 57 -> 56.
// v6 (Claude agent, lane E22): v4 + ONE pin, psoBest in $9 (t1): 58 -> 57. (v5 + same pin 65; psoBest $10 / i $9 / i $10 all worse.)
// DRAFT (Claude agent, lane E5) v4: aligned 58 (v3 73). ProjectPerp: "+j"(d) vmulx then separate "=j" vsub output; Dot with its own asm (r %0, t %1); VU_FLOATV(float) by value (mfc1) for the j loop; DivF VU_FLOAT(const float &) non-volatile. Left: i-loop t-reg priority (iBest gets a2, target t5) and pdzA/pdz add order.
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
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)&f)); } };
struct VU_FLOATV { qword q; VU_FLOATV(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };

static inline qword AddScaled(VU_FLOATV s, VU_VECTOR a, VU_VECTOR b, const void *p)
{
    qword r;
    __asm__ __volatile__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a.q), "j"(b.q), "j"(s.q), "r"(p)); /* "r"(p): allocation-only */
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
    qword r, t;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=j"(t) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}
static inline qword ProjectPerp(qword v, qword n, const void *p)
{
    qword d = DotV(v, n), r;
    __asm__("vmulx.xyzw %0, %1, %0x" : "+j"(d) : "j"(n), "r"(p)); /* "r"(p): allocation-only */
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(v), "j"(d));
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
        register SO *psoBest asm("$9"); // pin: t1, see header
        union { qword q; float f[4]; } vBest;
        func_00158988(pdzg, grf);
        iBest = -1;
        gBest = 0.01f;
        psoBest = 0;
        vBest.f[2] = 0.0f;
        vBest.f[1] = 0.0f;
        vBest.f[0] = 0.0f;
        i = 0;
        if (i < pdzg->cso) {
        DZ *adz = pdzg->adz;
        for (; i < pdzg->cso; i++) {
            DZ *pdz = &adz[i];
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
            DZ *pdzJ;
            for (j = 0, pdzJ = pdzg->adz; j < pdzg->cdz; j++, pdzJ++) {
                if (pdzJ->gC != 0.0f)
                    v.q = AddScaled(VU_FLOATV(pdzJ->gC), v.q, pdzg->af[j].av[i], pdzJ);
            }
            v.q = ProjectPerp(v.q, pso->normal, pso);
            g = Dot(v.q, v.q);
            if (gBest < g) {
                vBest.q = v.q;
                gBest = g;
                iBest = i;
                psoBest = pso;
            }
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
            { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(gBest)); pdz->g10 = -r; }
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
                    float gMax = D_002BDDE8 * pzz->gD0;
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
