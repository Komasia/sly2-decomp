typedef unsigned long ulong;

union DBL {
    double d;
    struct {
        ulong frac : 52;
        ulong exp : 11;
        ulong sign : 1;
    } bits;
};

double GTrunc(double g)
{
    DBL *pconv = (DBL *)&g;
    int exp = pconv->bits.exp - 0x3FF;
    if (exp < 0) {
        return 0.0;
    }
    if (exp < 52) {
        ulong mask = (1UL << (52 - exp)) - 1;
        ulong frac = pconv->bits.frac;
        if ((frac & mask) == mask) {
            pconv->bits.frac = frac & ~mask;
            g += 1.0;
        } else {
            pconv->bits.frac = frac & ~mask;
        }
    }
    return g;
}
