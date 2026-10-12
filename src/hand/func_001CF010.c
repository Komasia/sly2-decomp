typedef int qword __attribute__((mode(TI)));
int func_001CF010(qword v)
{
    float g;
    float lim;
    __asm__ __volatile__("qmtc2.ni %0, $vf3" : : "r"(v));
    lim = 0.0004f;
    __asm__ __volatile__("vmul.xyz $vf1, $vf3, $vf3" : : "f"(lim));
    __asm__ __volatile__("vaddw.x $vf2, $vf0, $vf0w");
    __asm__ __volatile__("vadday.x ACC, $vf1, $vf1y");
    __asm__ __volatile__("vmaddz.x $vf1, $vf2, $vf1z");
    __asm__ __volatile__("qmfc2.ni %0, $vf1" : "=r"(g));
    return g < lim;
}
