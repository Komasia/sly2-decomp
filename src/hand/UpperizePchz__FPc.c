extern unsigned char D_002AA6A1[];
void UpperizePchz__FPc(char *pchz)
{
    unsigned char *pch;
    for (pch = (unsigned char *)pchz; *pch; pch++) {
        int c = *pch;
        int u = c - 0x20;
        if (!(D_002AA6A1[c] & 2))
            u = c;
        *pch = u;
    }
}
