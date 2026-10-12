extern "C" char D_002C40C8[];
extern "C" void *func_001AE5A0(void *dst, const void *src, int cb);
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
        func_001AE5A0(ach, pch, c);
    return c;
}
