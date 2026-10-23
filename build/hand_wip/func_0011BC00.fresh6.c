// fresh6 (Claude agent, lane A17, 2026-10-23): aligned 7 -> 2. A commented `register M3 *pt asm("$5") = &m` pin plus a commented empty volatile asm right after it keep `a1 = sp` ahead of the MulM3 asm, so pa is copied to v0 like the target. Left: s0=a0 / sd ra swap and addiu a2 after the first sqc2 (sched2 priority: the barrier adds deps). NOTE: still has fresh5's three VF output pins.
// fresh5 (Claude agent, lane A12): aligned 7 like .c, alternative base: NON-volatile asm with "m"(*pa)/"m"(*pb) inputs keeps pm in a0 across the asm like the target (no daddu a0,s0). Left: target sets a1=sp before the asm and copies pa to v0.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
void *func_0023320C(void *pvDst, void *pvSrc, int cb);
static inline M3 MulM3(M3 *pa, M3 *pb)
{
    M3 m;
    register qword v4 __asm__("vf4");
    register qword v7 __asm__("vf7");
    register qword v8 __asm__("vf8");
    __asm__(
        "lqc2 $vf6, 0x20(%4)\n\t"
        "lqc2 $vf5, 0x20(%3)\n\t"
        "lqc2 $vf3, 0x10(%4)\n\t"
        "lqc2 $vf2, 0x0(%3)\n\t"
        "lqc2 $vf1, 0x10(%3)\n\t"
        "lqc2 $vf4, 0x0(%4)\n\t"
        "vmulaz.xyzw $ACC, $vf4, $vf2z\n\t"
        "vmaddaz.xyzw $ACC, $vf3, $vf1z\n\t"
        "vmaddz.xyzw $vf8, $vf6, $vf5z\n\t"
        "vmulax.xyzw $ACC, $vf4, $vf2x\n\t"
        "vmaddax.xyzw $ACC, $vf3, $vf1x\n\t"
        "vmaddx.xyzw $vf7, $vf6, $vf5x\n\t"
        "vmulay.xyzw $ACC, $vf4, $vf2y\n\t"
        "vmadday.xyzw $ACC, $vf3, $vf1y\n\t"
        "vmaddy.xyzw $vf4, $vf6, $vf5y"
        : "=j"(v7), "=j"(v8), "=j"(v4)
        : "r"(pa), "r"(pb), "m"(*pa), "m"(*pb) : "vf1", "vf2", "vf3", "vf5", "vf6");
    m.r[0] = v7;
    m.r[1] = v4;
    m.r[2] = v8;
    return m;
}
M3 *func_0011BC00(M3 *pm, M3 *pa, M3 *pb)
{
    M3 m;
    register M3 *pt __asm__("$5") = &m; /* pin */
    __asm__ volatile(""); /* empty asm: emulates the toolchain's schedule */
    m = MulM3(pa, pb);
    func_0023320C(pm, pt, sizeof(M3));
    return pm;
}
