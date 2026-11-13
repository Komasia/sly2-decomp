extern "C" char D_002C40C8[];
extern "C" void *CopyAb(void *dst, const void *src, int cb) asm("CopyAb__FPvT0Ui");
int CchAchFromUl(char *ach, int cch, unsigned long ul, unsigned int radix)
{
    char *pchEnd = ach + cch;
    char *pch = pchEnd;
    do {
        *--pch = D_002C40C8[(int)(ul % radix)];
        ul /= radix;
    } while (ul != 0 && pch >= ach);
    int c = pchEnd - pch;
    if (c != 0 && ach < pch)
        CopyAb(ach, pch, c);
    return c;
}
