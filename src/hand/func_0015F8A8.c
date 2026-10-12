typedef struct GLYPH { unsigned short ch; short a; short b; unsigned short dx; } GLYPH;
struct FONTBRX { char pad[0x138]; int cglyph; GLYPH *aglyph; };
extern unsigned short D_002BE338[];
GLYPH *func_0015F8A8(struct FONTBRX *p, unsigned char ch)
{
    int key = D_002BE338[ch];
    int lo = 0;
    int hi = p->cglyph - 1;
    while (lo <= hi) {
        int mid = (hi + lo) / 2;
        int d = key - p->aglyph[mid].ch;
        if (d == 0)
            return &p->aglyph[mid];
        if (d > 0)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return 0;
}
