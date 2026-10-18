typedef int TI __attribute__((mode(TI)));
register TI architectural_zero asm("$0");
int func_002401D8(const char *s1, const char *s2)
{
    register unsigned int addresses asm("$8") = (unsigned int)s1 | (unsigned int)s2;
    if ((addresses & 7) == 0) {
        register unsigned int align16 asm("$9") = addresses & 15;
        register unsigned long ones asm("$7") = 0x0101010101010101;
        register unsigned long highs asm("$6") = 0x8080808080808080;
        register unsigned long firstRight asm("$2");
        firstRight=*(const unsigned long *)s2;
        if (align16 == 0) {
            register TI firstX asm("$3"), firstY asm("$2");
            register TI maskOne asm("$8"), maskHigh asm("$10"), difference asm("$7");
            register unsigned long firstHigh asm("$6"), firstDifference asm("$3");
            __asm__("lq %0,%1" : "=r"(firstX) : "m"(*(const TI *)s1));
            __asm__("pcpyld %0,%1,%1" : "=r"(maskOne) : "r"(ones));
            __asm__("lq %0,%1" : "=r"(firstY) : "m"(*(const TI *)s2));
            __asm__("pcpyld %0,%1,%1" : "=r"(maskHigh) : "r"(highs));
            difference = __builtin_psubw(firstY, firstX);
            __asm__("pcpyud %0,%1,$4" : "=r"(firstHigh) : "r"(difference));
            __asm__("or %0,%1,%2" : "=r"(firstDifference) : "r"(firstHigh), "r"(difference));
            if (firstDifference == 0) {
                register TI x asm("$2"), y asm("$3"), complement asm("$3");
                register unsigned long high asm("$3"), zeroMask asm("$6"), compared asm("$9"), comparedHigh asm("$6");
                __asm__("lq %0,%1" : "=r"(x) : "m"(*(const TI *)s1));
                do {
                    complement = __builtin_pnor(architectural_zero, x);
                    __asm__("psubb %0,%1,%2" : "=r"(x) : "r"(x), "r"(maskOne));
                    __asm__("pand %0,%1,%2" : "=r"(x) : "r"(x), "r"(complement));
                    __asm__("pand %0,%1,%2" : "=r"(x) : "r"(x), "r"(maskHigh));
                    __asm__("pcpyud %0,%1,$4" : "=r"(high) : "r"(x));
                    __asm__("or %0,%1,%2" : "=r"(zeroMask) : "r"(high), "r"(x));
                    if (zeroMask != 0) return 0;
                    s1 += 16;
                    s2 += 16;
                    __asm__("lq %0,%1" : "=r"(x) : "m"(*(const TI *)s1));
                    __asm__("lq %0,%1" : "=r"(y) : "m"(*(const TI *)s2));
                    difference = __builtin_psubw(x, y);
                    __asm__("pcpyud %0,%1,$4" : "=r"(comparedHigh) : "r"(difference));
                    __asm__("or %0,%1,%2" : "=r"(compared) : "r"(comparedHigh), "r"(difference));
                } while (compared == 0);
            }
        } else {
            register unsigned long firstLeft asm("$3");
            __asm__("ld %0,%1" : "=r"(firstLeft) : "m"(*(const unsigned long *)s1));
            if (firstLeft == firstRight) {
                register unsigned long value asm("$2");
                do {
                    register unsigned long complement asm("$8");
                    value = *(const unsigned long *)s1;
                    complement = ~value;
                    value = value - ones;
                    s1 += 8;
                    if ((value & complement & highs) != 0) return 0;
                    s2 += 8;
                } while ((value = *(const unsigned long *)s1) == *(const unsigned long *)s2);
            }
        }
    }
    for (;;) {
        register int testByte asm("$2") = *s1;
        register unsigned int rawByte asm("$3") = *(const unsigned char *)s1;
        if (!testByte) break;
        {
            register int signedByte asm("$2") = (char)rawByte;
            register int otherByte asm("$3") = *s2;
            if (signedByte != otherByte) break;
        }
        ++s1; ++s2;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}
