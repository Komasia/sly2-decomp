unsigned int func_0021ED28(char *s);
void func_001AE5A0(void *dst, void *src, int cb);
char *strcpy1(char *pchzDst, char *pchzSrc)
{
    unsigned int dstLength = func_0021ED28(pchzDst);
    unsigned int srcLength = func_0021ED28(pchzSrc);
    func_001AE5A0(pchzDst + dstLength, pchzSrc, srcLength + 1);
    return pchzDst;
}
