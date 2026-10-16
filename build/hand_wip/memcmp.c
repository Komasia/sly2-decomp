// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef unsigned int size_t;
typedef int TItype __attribute__((mode(TI)));
int memcmp(const void *m1, const void *m2, size_t n)
{
    unsigned char *s1 = (unsigned char *)m1;
    unsigned char *s2 = (unsigned char *)m2;

    if (!(n < sizeof(TItype)) && !(((int)s1 | (int)s2) & (sizeof(TItype) - 1))) {
        int last;
        do {
            long x, hi, t;
            last = n < 32;
            __asm__("pxor %0, %1, %2" : "=r"(x) : "r"(*(TItype *)s2), "r"(*(TItype *)s1));
            s1 += 16;
            __asm__("pcpyud %0, %1, %2" : "=r"(hi) : "r"(x), "r"(last));
            t = hi | x;
            s2 = t ? s2 : s2 + 16;
            if (t) goto differ;
            n -= 16;
        } while (!last);
        goto bytes;
differ:
        s1 -= 16;
    }
bytes:
    while (n--) {
        if (*s1 != *s2)
            return *s1 - *s2;
        s1++;
        s2++;
    }
    return 0;
}
/* WIP (round 8, 0x230000 agent): 40/41 differ only because of a shift; shape is close.
 * gcc cannot do TImode xor/compare ("unsupported wide integer operation"), so pxor and
 * pcpyud must be inline asm; target's pcpyud rt operand is the `last = n < 32` reg ($a3).
 * Remaining: target keeps s1 in $a0 (ours copies it to $a3), movz is before a bnel whose
 * annulled delay slot holds `s1 -= 16` (ours puts movz in the delay slot of bnez). */
