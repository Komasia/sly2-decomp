// (Claude agent, T1553) C exploration, aligned 63: ee-gcc 136, __builtin_pnor + global $zero reg var (pnor needs a builtin to sit in the beql slot; asm never fills delay slots), other MMI ops as asm with long outputs (no por copies). Superseded by the asm MATCH in src/lib/func_002401D8.c.
/* strcmp (newlib r5900) */
typedef int TI __attribute__((mode(TI)));
register TI zero asm("$0"); /* pnor's $zero operand */
#define PCPYLD(x, a) __asm__("pcpyld %0,%1,%1" : "=r"(x) : "r"(a))
#define PSUBW(x, a, b) __asm__("psubw %0,%1,%2" : "=r"(x) : "r"(a), "r"(b))
#define PSUBB(x, a, b) __asm__("psubb %0,%1,%2" : "=r"(x) : "r"(a), "r"(b))
#define PAND(x, a, b) __asm__("pand %0,%1,%2" : "=r"(x) : "r"(a), "r"(b))
#define PCPYUD(x, a, b) __asm__("pcpyud %0,%1,%2" : "=r"(x) : "r"(a), "r"(b))

int func_002401D8(const char *s1, const char *s2)
{
    if ((((unsigned int)s1 | (unsigned int)s2) & 7) == 0) {
        unsigned long ones = 0x0101010101010101;
        unsigned long highs = 0x8080808080808080;
        if ((((unsigned int)s1 | (unsigned int)s2) & 15) == 0) {
            TI x, y, n, qones, qhighs;
            unsigned long d, h, z;
            x = *(const TI *)s1;
            PCPYLD(qones, ones);
            y = *(const TI *)s2;
            PCPYLD(qhighs, highs);
            PSUBW(d, y, x);
            PCPYUD(h, d, s1);
            if ((h | d) == 0) {
                x = *(const TI *)s1;
                do {
                    n = __builtin_pnor(zero, x);
                    PSUBB(x, x, qones);
                    PAND(x, x, n);
                    PAND(z, x, qhighs);
                    PCPYUD(h, z, s1);
                    if ((h | z) != 0)
                        return 0;
                    s1 += 16;
                    s2 += 16;
                    x = *(const TI *)s1;
                    y = *(const TI *)s2;
                    PSUBW(d, x, y);
                    PCPYUD(h, d, s1);
                } while ((h | d) == 0);
            }
        } else {
            const unsigned long *a1 = (const unsigned long *)s1;
            const unsigned long *a2 = (const unsigned long *)s2;
            while (*a1 == *a2) {
                if (((*a1 - ones) & ~*a1 & highs) != 0)
                    return 0;
                a1++;
                a2++;
            }
            s1 = (const char *)a1;
            s2 = (const char *)a2;
        }
    }
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}
