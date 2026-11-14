unsigned int s1_strlen(char *s) asm("strlen");
void CopyAb(void *dst, void *src, int cb) asm("CopyAb__FPvT0Ui");
char *strcpy1(char *pchzDst, char *pchzSrc)
{
    unsigned int dstLength = s1_strlen(pchzDst);
    unsigned int srcLength = s1_strlen(pchzSrc);
    CopyAb(pchzDst + dstLength, pchzSrc, srcLength + 1);
    return pchzDst;
}
