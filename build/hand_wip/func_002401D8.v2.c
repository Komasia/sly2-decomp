// v2 (Claude agent): game compiler/assembler (no SLY2_CC) reproduces the dli expansions; volatile first-check lq loads stop CSE with the loop-top load; `or` as asm avoids TI->DI por copies. Left: a/a&15 regs (t0/t1), bnez vs bnel, inline jr per return 0, byte-loop form.
typedef int TI __attribute__((mode(TI)));

int func_002401D8(const char *s1, const char *s2)
{
    unsigned int a = (unsigned int)s1 | (unsigned int)s2;
    if ((a & 7) == 0) {
        unsigned long ones = 0x0101010101010101;
        unsigned long highs = 0x8080808080808080;
        if ((a & 15) == 0) {
            TI x, y, d, m1, m80, t;
            unsigned long hi, r;
            x = *(volatile TI *)s1;
            __asm__("pcpyld %0, %1, %1" : "=r"(m1) : "r"(ones));
            y = *(volatile TI *)s2;
            __asm__("pcpyld %0, %1, %1" : "=r"(m80) : "r"(highs));
            __asm__("psubw %0, %1, %2" : "=r"(d) : "r"(y), "r"(x));
            __asm__("pcpyud %0, %1, $4" : "=r"(hi) : "r"(d));
            __asm__("or %0, %1, %2" : "=r"(r) : "r"(hi), "r"(d));
            if (r == 0) {
                do {
                    x = *(TI *)s1;
                    __asm__("pnor %0, $0, %1" : "=r"(t) : "r"(x));
                    __asm__("psubb %0, %1, %2" : "=r"(x) : "r"(x), "r"(m1));
                    __asm__("pand %0, %1, %2" : "=r"(x) : "r"(x), "r"(t));
                    __asm__("pand %0, %1, %2" : "=r"(x) : "r"(x), "r"(m80));
                    __asm__("pcpyud %0, %1, $4" : "=r"(hi) : "r"(x));
                    __asm__("or %0, %1, %2" : "=r"(r) : "r"(hi), "r"(x));
                    s1 += 16;
                    if (r != 0)
                        return 0;
                    s2 += 16;
                    x = *(TI *)s1;
                    y = *(TI *)s2;
                    __asm__("psubw %0, %1, %2" : "=r"(d) : "r"(x), "r"(y));
                    __asm__("pcpyud %0, %1, $4" : "=r"(hi) : "r"(d));
                    __asm__("or %0, %1, %2" : "=r"(r) : "r"(hi), "r"(d));
                } while (r == 0);
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
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1) - (*(unsigned char *)s2);
}
