// WIP strcmp (EE qword). Blockers: dli expanded by gas as ori/dsll chain (0x808080808080<<9|0x101), not reproducible with 2.96 gas; TI->DI casts add por copies with 2.95.3-136 builtins; loop-top lq CSEd.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorg
typedef int TI __attribute__((mode(TI)));

int func_002401D8(const char *s1, const char *s2)
{
    unsigned int a = (unsigned int)s1 | (unsigned int)s2;
    if ((a & 7) == 0) {
        unsigned long ones = 0x0101010101010101;
        unsigned long highs = 0x8080808080808080;
        if ((a & 15) == 0) {
            TI x, y, d, m1, m80, t;
            unsigned long hi;
            x = *(TI *)s1;
            __asm__("pcpyld %0, %1, %1" : "=r"(m1) : "r"(ones));
            y = *(TI *)s2;
            __asm__("pcpyld %0, %1, %1" : "=r"(m80) : "r"(highs));
            __asm__("psubw %0, %1, %2" : "=r"(d) : "r"(y), "r"(x));
            __asm__("pcpyud %0, %1, $4" : "=r"(hi) : "r"(d));
            if ((hi | (unsigned long)d) == 0) {
                do {
                    x = *(TI *)s1;
                    __asm__("pnor %0, $0, %1" : "=r"(t) : "r"(x));
                    __asm__("psubb %0, %1, %2" : "=r"(x) : "r"(x), "r"(m1));
                    __asm__("pand %0, %1, %2" : "=r"(x) : "r"(x), "r"(t));
                    __asm__("pand %0, %1, %2" : "=r"(x) : "r"(x), "r"(m80));
                    __asm__("pcpyud %0, %1, $4" : "=r"(hi) : "r"(x));
                    s1 += 16;
                    if ((hi | (unsigned long)x) != 0)
                        return 0;
                    s2 += 16;
                    x = *(TI *)s1;
                    y = *(TI *)s2;
                    __asm__("psubw %0, %1, %2" : "=r"(d) : "r"(x), "r"(y));
                    __asm__("pcpyud %0, %1, $4" : "=r"(hi) : "r"(d));
                } while ((hi | (unsigned long)d) == 0);
            }
        } else if (*(unsigned long *)s1 == *(unsigned long *)s2) {
            do {
                unsigned long v = *(unsigned long *)s1;
                s1 += 8;
                if (((v - ones) & ~v & highs) != 0)
                    return 0;
                s2 += 8;
            } while (*(unsigned long *)s1 == *(unsigned long *)s2);
        }
    }
    while (*s1 != 0) {
        if (*s1 != *s2)
            break;
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}
