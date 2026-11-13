// CRichText::CRichText(char *achz, CFont *pfont): the text and its base font; every color starts as opaque
// mid-grey (0xFF808080: the PS2's 0x80 = full intensity). Layout as in Reset__9CRichText.cpp / Sly 1 font.h.
struct RGBA { unsigned char r, g, b, a; };
struct CFont;
class CRichText {
public:
    /* 0x000 */ char *m_achz;
    /* 0x004 */ char *m_pchCur;
    /* 0x008 */ CFont *m_pfontCur;
    /* 0x00c */ CFont *m_pfontBase;
    /* 0x010 */ char m_fontOther[0x150 - 0x10];   /* CFontBrx */
    /* 0x150 */ int m_unknown;
    /* 0x154 */ unsigned int m_rgbaCur;
    /* 0x158 */ unsigned int m_rgbaSet;
    /* 0x15c */ unsigned int m_rgbaBase;
    /* 0x160 */ unsigned int m_rgbaOther;
    CRichText(char *achz, CFont *pfont);
    void Reset();
};

CRichText::CRichText(char *achz, CFont *pfont)
{
    m_achz = achz;
    m_pfontBase = pfont;
    m_rgbaOther = 0xFF808080;
    m_rgbaBase = 0xFF808080;
    m_rgbaSet = 0xFF808080;
    m_rgbaCur = 0xFF808080;
    Reset();
}
