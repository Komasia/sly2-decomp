// fresh5 (Claude agent, laneC28 2026-10-24): aligned 19 -> 18. The dead t copy moved out of MulG into an inline FromTo(pvFrom, pvTo, pm, const M3 &mk) wrapper around the first func_0022FD38 call (`M3 t = mk;` in its body), so the dead stores now come after the p->pq/p60 argument loads like the target; MulG a rows in operand order 1,0,2 (other orders 20-22). b0/b1 and r0/r1 VF numbers now match. Left: a rows/b2/r2 VF numbers, m-row store group order (0x60 before 0x0), t lands in the dead a slot 0x90 (target 0xF0), s3 = &m0 lost. t at function scope: frame +0x30.
// fresh4 (Claude agent, laneC24 2026-10-23): aligned 20 -> 19. MulG asms take the a rows in reverse operand order ("j"(a.r[1]), "j"(a.r[0]), "j"(a.r[2]), "j"(b.r[N]); template %3,%2,%1,%4): reload now gives a.r[2] vf1 like the target (a.r[0]/a.r[1] still vf2/vf6, target vf3/vf4). Operand orders with b first: 24.
// fresh3 (Claude agent, laneC23 2026-10-23): aligned 25 -> 20. A commented empty asm clobbering the dead a0 ("$4") at the top of the c4678/nBest<3 block, so the &D_003DD490 base (live to the ps4690 load) gets a1 like the target and reorg makes the beql with daddu a1,s1 in its slot. Left: MulG VF numbering (reload regs) and the dead t-row stores (0xF0..) scheduled before the p->pq/p60 loads. g_clock rename: no change.
// fresh2 (Claude agent, laneC11 2026-10-23): aligned 27 -> 25. The first Mul (m0) uses its own MulG helper that does all three asms first, then the m rows, then the dead t rows (store groups 0x0/0x60 like the target). Left: Mul VF numbering (target a rows vf3/vf4/vf1), the t-row stores are scheduled before the lw p->pq loads (target after), and the &D_003DD490 base a0/a1 (a pinned GS* in $5 gives the beql but costs elsewhere: 27).
// fresh1 (Claude agent, laneC9 2026-10-23): aligned 104 -> 27. Logic fixes: f = (pan.min < pan.max || tilt.min < tilt.max); GFrac written in the caller (pan loaded only in the else path, compare max == min); g1 > ps->gE8. M3 block: m0, m1 declared first (0x0, 0x30), m2 declared after the m1 Mul (reuses temp 0x60), Mul as NRV `return m` + dead copy t (t row stored before m row): stmt temps = return 0x60/0x90, call temps, t. Left: Mul1 VF numbering/store order, &D_003DD490 base in a0 (target a1) + beql.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct CLOCK { float t; float dt; };
struct LM { float gMin; float gMax; };
struct R { char pad[0x40]; M3 m40; char pad1[0xA0 - 0x70]; void *pA0; };
struct Q { char pad[8]; R *p8; };
struct S {
    char pad[0xE0]; S *pNext; int pad1; float gE8; char rng[8]; int nF4;
};
struct P {
    char pad[0x60]; void *p60; char pad1[0xF04 - 0x64]; int nF04; char pad2[0x10DC - 0xF08];
    S *ps10DC; int pad3; int n10E4; char pad4[0x10F4 - 0x10E8]; Q *pq; void *p10F8; int pad5;
    int n1100; int n1104; int pad6[2]; float g1110; float g1114; float g1118; int pad7;
    LM lmPan; LM lmTilt; float g1130; float g1134; char pad8[0x1148 - 0x1138]; int n1148; float g114C;
    M3 m1150;
};
struct GS { char pad[0x4678]; int c4678; char pad1[0x4690 - 0x467C]; S *ps4690; };
extern "C" {
extern CLOCK D_002DDED0;
extern int D_002DD640;
extern float D_002A4D68;
extern qword D_002A2DA0;
extern S *D_003E1474;
extern GS D_003DD490;
void func_00142880(P *p);
void func_001427C8(P *p, int n, S *ps);
void func_001428D8(P *p, S *ps, void **ppv, float *pg, float *pg2);
int func_0011D910(void *p, float g);
void func_0012CFE0(Q *pq);
void func_0012D020(Q *pq);
qword func_001A62E8(void *p);
qword func_001A6F00(int n, P *p, qword q);
void func_0011E958(qword v, float *pa, float *pb);
float func_0011D978(LM *plm, float g);
M3 func_0011B720(float a, float b);
M3 func_0011B500(qword v, float g);
M3 func_0022FD38(void *pvFrom, void *pvTo, M3 *pm);
M3 func_0011B340(const M3 *pm);
qword func_0011BFF0(M3 *pm);
void func_0012D108(Q *pq, qword q);
void func_00142AF8(P *p);
}
static inline M3 Mul(const M3 &a, const M3 &b) return m
{
    M3 t;
    qword r0, r1, r2;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r0) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[0]));
    t.r[0] = r0; m.r[0] = r0;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r1) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[1]));
    t.r[1] = r1; m.r[1] = r1;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r2) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[2]));
    t.r[2] = r2; m.r[2] = r2;
}
static inline M3 MulG(const M3 &a, const M3 &b) return m
{
    M3 t;
    qword r0, r1, r2;
    __asm__("vmulax.xyz ACC,%2,%4x\n\tvmadday.xyz ACC,%1,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r0) : "j"(a.r[1]), "j"(a.r[0]), "j"(a.r[2]), "j"(b.r[0]));
    __asm__("vmulax.xyz ACC,%2,%4x\n\tvmadday.xyz ACC,%1,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r1) : "j"(a.r[1]), "j"(a.r[0]), "j"(a.r[2]), "j"(b.r[1]));
    __asm__("vmulax.xyz ACC,%2,%4x\n\tvmadday.xyz ACC,%1,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r2) : "j"(a.r[1]), "j"(a.r[0]), "j"(a.r[2]), "j"(b.r[2]));
    m.r[0] = r0; m.r[1] = r1; m.r[2] = r2;
}
static inline M3 FromTo(void *pvFrom, void *pvTo, M3 *pm, const M3 &mk)
{
    M3 t = mk; /* dead copy made after the argument loads (Claude agent) */
    return func_0022FD38(pvFrom, pvTo, pm);
}
static inline float GFrac(float g, float a, float b)
{
    if (b == a)
        return 0.5f;
    return (g - a) / (b - a);
}
static inline float X(const M3 &m, int i) { return ((float *)&m.r[0])[i]; }

void func_00142AF8(P *p)
{
    int f;
    float pan, tilt;
    float g;
    if (p->pq == 0)
        return;
    f = 0;
    if (p->lmPan.gMin < p->lmPan.gMax || p->lmTilt.gMin < p->lmTilt.gMax)
        f = 1;
    if (p->nF04 != -1)
        f = 0;
    if (p->g114C < D_002DDED0.t && (p->n1148 != 0 || f)) {
        p->n1148 = !p->n1148;
        func_00142880(p);
    }
    if (p->n1100 == 0) {
        if (D_002DD640 != 0) {
            func_001427C8(p, -1, 0);
        } else {
            S *psBest = p->ps10DC;
            int nBest = p->n10E4;
            float gBest, g1, g2;
            S *ps;
            if (psBest)
                func_001428D8(p, psBest, &p->p10F8, &gBest, 0);
            else
                gBest = D_002A4D68;
            for (ps = D_003E1474; ps; ps = ps->pNext) {
                if (ps->nF4 < nBest)
                    continue;
                func_001428D8(p, ps, &p->p10F8, &g1, &g2);
                if (g1 > ps->gE8)
                    continue;
                if (!func_0011D910(ps->rng, g2))
                    continue;
                if (nBest < ps->nF4 || (ps->nF4 == nBest && g1 < gBest)) {
                    psBest = ps;
                    gBest = g1;
                    nBest = psBest->nF4;
                }
            }
            if (D_003DD490.c4678 > 0 && nBest < 3) {
                __asm__("" : : : "$4"); /* clobber of dead a0 (Claude agent): target keeps &D_003DD490 in a1 */
                ps = D_003DD490.ps4690;
                if (ps) {
                    float g3, g4;
                    func_001428D8(p, ps, &p->p10F8, &g3, &g4);
                    if (nBest < 2 || (nBest == 2 && g3 < gBest)) {
                        psBest = ps;
                        nBest = 2;
                        gBest = g3;
                    }
                }
            }
            func_001427C8(p, nBest, psBest);
        }
    }
    if (p->n1104 != 0) {
        func_0012CFE0(p->pq);
        pan = p->g1110;
        tilt = p->g1114;
        g = p->g1118;
    } else {
        if (p->p10F8 == 0 || p->n1148 == 0 || !f) {
            func_0012D020(p->pq);
            return;
        }
        func_0012CFE0(p->pq);
        func_0011E958(func_001A6F00(0, p, func_001A62E8(p->p10F8)), &pan, &tilt);
        pan = func_0011D978(&p->lmPan, pan);
        tilt = func_0011D978(&p->lmTilt, tilt);
        {
            float t;
            if (p->lmPan.gMax == p->lmPan.gMin)
                t = 0.5f;
            else
                t = (pan - p->lmPan.gMin) / (p->lmPan.gMax - p->lmPan.gMin);
            float u = t * __builtin_fabsf(t);
            g = (1.0f - u) * p->g1130 + u * p->g1134;
        }
    }
    M3 m0, m1;
    m0 = MulG(func_0011B720(pan, tilt), func_0011B500(D_002A2DA0, g));
    m1 = FromTo(0, p->p60, &p->pq->p8->m40, m0);
    m1 = Mul(m1, func_0011B340(&p->m1150));
    M3 m2;
    if (X(m0, 0) + X(m1, 0) < 0.0f && X(m0, 1) * X(m1, 1) < 0.0f)
        m2 = p->m1150;
    else
        m2 = Mul(m0, p->m1150);
    m2 = func_0022FD38(p->p60, p->pq->p8->pA0, &m2);
    func_0012D108(p->pq, func_0011BFF0(&m2));
}
