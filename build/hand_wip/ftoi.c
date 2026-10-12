// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
int ftoi(unsigned long d)
{
    long e;
    unsigned long m;

    m = d;
    e = (long)((m << 1) >> 53) - 0x433;

    if (e < -53)
        return 0;
    if (e >= 13)
        return 9999;
    m = ((m << 12) >> 12) | (1UL << 52);
    if (e < 0)
    {
        e = -e;
        m >>= (int)(e - 2);
        if ((m & 3) == 3)
            m = (m >> 2) + 1;
        else
            m >>= 2;
    }
    else
    {
        m <<= (int)e;
    }
    return (long)(m << 32) >> 32;
}
