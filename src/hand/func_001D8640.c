extern unsigned char D_002AA6A1[];
static inline int ToUpper(int c) { return (D_002AA6A1[c] & 2) ? c - 0x20 : c; }
int func_001D8640(unsigned char *pch) {
    int h = 0;
    while (*pch) {
        h = h * 33 + ToUpper(*pch);
        pch++;
    }
    return h;
}
