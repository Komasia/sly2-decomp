/* CFontBrx::PglyffFromCh (Sly 1 font.c): the glyph of a character: its code (D_002BE338 maps the byte to the font's
 * character code) binary-searched in the font's sorted glyph table; 0 if the font lacks it. */
typedef struct GLYFF { unsigned short wch; short u; short v; unsigned short dx; } GLYFF;
struct CFontBrx { char pad[0x138]; int m_cglyff; GLYFF *m_aglyff; };
extern unsigned short D_002BE338[];
GLYFF *func_0015F8A8(struct CFontBrx *pfont, unsigned char ch)
{
    int wch = D_002BE338[ch];
    int lo = 0;
    int hi = pfont->m_cglyff - 1;
    while (lo <= hi) {
        int mid = (hi + lo) / 2;
        int d = wch - pfont->m_aglyff[mid].wch;
        if (d == 0)
            return &pfont->m_aglyff[mid];
        if (d > 0)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return 0;
}
