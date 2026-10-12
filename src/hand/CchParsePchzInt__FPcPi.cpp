static inline int FDigit(unsigned char ch) { return ch >= '0' && ch <= '9'; }
int CchParsePchzInt(char *pchz, int *pn)
{
    unsigned char *pch = (unsigned char *)pchz;
    int sign = (*pch == '-') ? -1 : 1;
    int n = 0;
    int cch = 0;
    if (sign == -1) {
        pch++;
        cch = 1;
    }
    for (; FDigit(*pch); pch++) { n = n * 10 + (*pch - '0'); cch++; }
    *pn = n * sign;
    return cch;
}
