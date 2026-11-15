// CRichText::SetBaseColor (Sly 1 font.c): the text's base colour, which also becomes the current one.
struct RGBA { unsigned char r, g, b, a; };
class CRichText {
public:
    char pad[0x154];
    RGBA m_rgbaCur;
    RGBA m_rgbaSet;
    RGBA m_rgbaBase;
    void SetBaseColor(RGBA *prgba);
};
void CRichText::SetBaseColor(RGBA *prgba)
{
    m_rgbaBase = *prgba;
    m_rgbaCur = m_rgbaBase;
}
