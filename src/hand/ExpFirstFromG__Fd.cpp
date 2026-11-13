extern "C" double log10(double) asm("log10");
int ExpFirstFromG(double g)
{
    int exp;
    if (g > 0.0) {
        double l = log10(g);
        exp = (int)l;
        if (l < 0.0 && l != (double)exp)
            exp--;
    } else {
        exp = 0;
    }
    return exp;
}
