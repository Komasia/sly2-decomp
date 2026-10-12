struct GLYPH { short a; short b; short c; unsigned short dx; };
class CFontBrx {
public:
    int pad[2];
    int m_dxSpace;
    int pad2;
    float m_rxScale;
    float DxFromCh(char ch);
    GLYPH *PglyphFromCh(unsigned char ch);
};
float CFontBrx::DxFromCh(char ch)
{
    GLYPH *pglyph = PglyphFromCh(ch);
    if (pglyph)
        return (float)(pglyph->dx + 1) * m_rxScale;
    return (float)m_dxSpace * m_rxScale;
}
