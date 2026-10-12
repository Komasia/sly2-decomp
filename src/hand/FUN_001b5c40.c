int func_0021ED28(char *s);
unsigned short FUN_001b5b58(unsigned char ch);
void FUN_001b5c40(char *s, unsigned short *pw)
{
    int i;
    int c = func_0021ED28(s);
    for (i = 0; i < c; i++) {
        unsigned short w = FUN_001b5b58(s[i]);
        unsigned short lo = w & 0xFF;
        unsigned short hi = (w >> 8) & 0xFF;
        pw[i] = (lo << 8) | hi;
    }
    pw[i] = 0;
}
