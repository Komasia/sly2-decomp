/* class: progress name table (SafeHouse savedata.cpp: "case-insensitive hash, 0x1D8640: h * 33 + toupper"): the
 * hash of a name. */
extern unsigned char D_002AA6A1[];   /* the ctype table (bit 2: lower case) */
static inline int ToUpper(int ch) { return (D_002AA6A1[ch] & 2) ? ch - 0x20 : ch; }

int func_001D8640(unsigned char *pchz)
{
    int h = 0;
    while (*pchz) {
        h = h * 33 + ToUpper(*pchz);
        pchz++;
    }
    return h;
}
