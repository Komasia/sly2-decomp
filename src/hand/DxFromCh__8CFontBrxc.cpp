// CFontBrx::DxFromCh (Sly 1 font.c): the scaled advance of a character: its glyph's width plus one, or the space's.
struct GLYPH { short wch; short u; short v; unsigned short dx; };   /* Sly 1 GLYFF */
class CFontBrx {
public:
    int pad[2];
    int m_dxSpaceUnscaled;
    int m_dyUnscaled;
    float m_rxScale;
    float DxFromCh(char ch);
    GLYPH *PglyphFromCh(unsigned char ch);
};
float CFontBrx::DxFromCh(char ch)
{
    GLYPH *pglyph = PglyphFromCh(ch);
    if (pglyph)
        return (float)(pglyph->dx + 1) * m_rxScale;
    return (float)m_dxSpaceUnscaled * m_rxScale;
}
