// T1753 (Claude agent for Lilly, 2026-10-26): lilly7 with the vf28/vf25 prologue loads fused into ONE asm (the target issues them back to back right after `lw v0,0xC0(sp)`): aligned 9 -> 7 with the team matchtool. Left: the same sched2 unit/cost diff as lilly7 (sw t3 before the s-reg saves, lui/lwc1 f21 among the lqc2s, epilogue sqc2 vf26 after `lq s0` and sqc2 vf25 last), which only real compiler moves (vf register vars) produce. lilly1.c is the real MATCH.
// T1746 (Claude agent for Lilly, 2026-10-26): one-pin form (vf24, fills the bc1fl delay slot). aligned 9 with the team matchtool. GPR allocation, spills and the qmtc2.ni a1,vf27 now match: each named-vf asm has a dummy "=j"(vu) output chained into the next one (order + no "+m" memory writes, so reload keeps a2/t3) and cDead/j are set before the asms, t after them. Left: only sched2 order of the asm lqc2/sqc2 in the prologue/epilogue (asm insns get unit "none", cost 1; the compiler movti in lilly1 is "[memory vu0]", cost 3). The dummy outputs name a vf register the template never writes, so this is not a faithful form; lilly1.c (11 vf register vars) is the real MATCH.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
typedef struct { float x, y, z, w; } V;
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
float func_0011CF60(float);

int func_00139950(M4 *pm, qword dt, qword *pa, qword *pb, qword *pc, int c, int k, qword *pvMin, qword *pvMax)
{
    register qword v24 __asm__("vf24"); /* microprogram input */
    qword vu;
    float t;
    float g;
    int cDead;
    int j;
    int i;
    int sync;

    cDead = 0;
    j = -1;
    __asm__("qmtc2.ni %1, $vf27" : "=j"(vu) : "r"(dt));
    __asm__("lqc2 $vf28, %1\n\tlqc2 $vf25, %2" : "=j"(vu) : "m"(pm->r[3]), "m"(*pvMax), "j"(vu));
    __asm__("lqc2 $vf31, %1" : "=j"(vu) : "m"(pm->r[0]), "j"(vu));
    __asm__("lqc2 $vf30, %1" : "=j"(vu) : "m"(pm->r[1]), "j"(vu));
    __asm__("lqc2 $vf29, %1" : "=j"(vu) : "m"(pm->r[2]), "j"(vu));
    __asm__("lqc2 $vf26, %0" : "+m"(*pvMin) : "j"(vu));
    t = D_002DDED0.t;
    for (i = 0; i < c; i++) {
        if (((V *)&pb[i])->w <= t) {
            cDead++;
            continue;
        }
        v24 = pb[i];
        __asm__("lqc2 $vf23, %1" : "=j"(vu) : "m"(pa[i]));
        __asm__ __volatile__("vcallms 0x10" : : "j"(v24), "j"(vu));
        j++;
        pc[j] = pc[i];
        if (k == 2) {
            __asm__("mtc1 %1, %0" : "=f"(g) : "r"(dt));
            ((V *)&pc[j])->w = func_0011CF60(((V *)&pc[i])->w + ((V *)&pc[i])->z * g);
        }
        __asm__ __volatile__("cfc2.i %0, $vi0" : "=r"(sync));
        __asm__("sqc2 $vf22, %0" : "=m"(pb[j]));
        __asm__("sqc2 $vf21, %0" : "=m"(pa[j]));
    }
    __asm__("sqc2 $vf26, %0" : "=m"(*pvMin));
    __asm__("sqc2 $vf25, %0" : "=m"(*pvMax));
    return cDead;
}
