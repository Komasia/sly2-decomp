/* Case-folded string hash: n = n * 33 + toupper(ch) over the string (0: the empty string at 0x2A4150). */
extern unsigned char D_002A4150[];
extern unsigned char D_002AA6A1[];

#define toupper(c) ({ int __x = (c); (D_002AA6A1[__x] & 2) ? __x - 'a' + 'A' : __x; })

int func_0011AFE0(unsigned char *pchz)
{
    int n;

    if (!pchz) {
        pchz = D_002A4150;
    }
    n = 0;
    while (*pchz) {
        n = n * 33 + toupper(*pchz++);
    }
    return n;
}
