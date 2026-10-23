typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
void *func_0023320C(void *pvDst, void *pvSrc, int cb);
static inline M3 MulM3(M3 *pa, M3 *pb)
{
    M3 m;
    register qword v4 __asm__("vf4");
    register qword v7 __asm__("vf7");
    register qword v8 __asm__("vf8");
    __asm__ __volatile__(
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
        : "r"(pa), "r"(pb) : "vf1", "vf2", "vf3", "vf5", "vf6");
    m.r[0] = v7;
    m.r[1] = v4;
    m.r[2] = v8;
    return m;
}
M3 *func_0011BC00(M3 *pm, M3 *pa, M3 *pb)
{
    M3 m;
    M3 *pmm;
    __asm__("" : "=r"(pmm) : "0"(&m));
    m = MulM3(pa, pb);
    func_0023320C(pm, pmm, sizeof(M3));
    return pm;
}
