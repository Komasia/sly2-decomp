// CRichText::ChNext (Sly 1 font.c): the next character to draw, after applying the markup before it:
//   ~RRGGBB  colour (halved to the PS2's 0x80 = full scale), ~. back to the base colour, ~~ a literal '~'
//   &c       font c (a built-in font, func_0015EFA0, scaled to the base font's line height), &. back to the base font,
//            && a literal '&'
//   ^dd      scale by d.d (PushScaling), ^. undo it (PopScaling), ^^ a literal '^'
// (Claude agent, lane E7) MATCH from v2 (1 diff): ONE register pin, `one` in $19 for the three m_fDirty = 1 stores. Without it,
// the null-font branch's m_fDirty = 1 is CSE'd into fDone's s1 (target keeps the hoisted const-1 in s3).
struct RGBA { unsigned char r, g, b, a; };
class CFont {
public:
    int pad0[3];
    int m_dyUnscaled;
    float m_rxScale;
    float m_ryScale;
    char pad18[0x140 - 0x18];
} __attribute__((aligned(16)));
class CRichText {
public:
    unsigned char *m_achz;
    unsigned char *m_pchCur;
    CFont *m_pfontCur;
    CFont *m_pfontBase;
    CFont m_fontOther;   /* the copy of a selected font */
    int m_fDirty;        /* the font changed since the last glyph: Draw switches the texture */
    RGBA m_rgbaCur;
    RGBA m_rgbaSet;
    RGBA m_rgbaBase;
    RGBA m_rgbaOther;
    unsigned char ChNext();
};
extern "C" {
CFont *func_0015EFA0(int chCode);
void PopScaling(CFont *pfont) asm("PopScaling__5CFont");
void PushScaling(CFont *pfont, float rx, float ry) asm("PushScaling__5CFontff");
}
unsigned char CRichText::ChNext()
{
    int fDone = 0;
    register int one __asm__("$19") = 1; // register pin (the target's hoisted const-1 reg for the m_fDirty stores)
    do {
        unsigned char *pch = m_pchCur;
        switch (*pch) {
        case '~':
            if (pch[1] == '~') {
                m_pchCur = pch + 1;
                fDone = 1;
            } else if (pch[1] == '.') {
                m_rgbaSet = m_rgbaBase;
                m_rgbaCur = m_rgbaSet;
                m_pchCur += 2;
            } else {
                unsigned char *pchT = pch + 1;
                unsigned int rgb = 0;
                while (*pchT && pchT - m_pchCur < 7) {
                    int d;
                    if (*pchT >= '0' && *pchT <= '9')
                        d = *pchT - '0';
                    else if (*pchT >= 'A' && *pchT <= 'F')
                        d = *pchT - 'A' + 10;
                    else if (*pchT >= 'a' && *pchT <= 'f')
                        d = *pchT - 'a' + 10;
                    else
                        break;
                    pchT++;
                    rgb = rgb * 16 + d;
                }
                if (pchT - m_pchCur >= 7) {
                    m_rgbaSet.r = (((rgb >> 16) & 0xFF) + 1) >> 1;
                    m_rgbaSet.g = (((rgb & 0xFF00) >> 8) + 1) >> 1;
                    m_rgbaSet.b = ((rgb & 0xFF) + 1) >> 1;
                    m_rgbaCur = m_rgbaSet;
                    m_pchCur += 7;
                } else {
                    m_pfontCur = m_pfontBase;
                    m_rgbaCur = m_rgbaBase;
                    fDone = 1;
                }
            }
            break;
        case '&':
            if (pch[1] == '&') {
                m_pchCur = pch + 1;
                fDone = 1;
            } else if (pch[1] == '.') {
                m_pfontCur = m_pfontBase;
                m_rgbaCur = m_rgbaSet;
                m_fDirty = one;
                m_pchCur += 2;
            } else {
                CFont *pfont = func_0015EFA0(pch[1]);
                if (pfont) {
                    m_fontOther = *pfont;
                    m_pchCur += 2;
                    CFont *pfontNew = &m_fontOther;
                    float r = ((float)m_pfontBase->m_dyUnscaled * m_pfontBase->m_ryScale) / ((float)pfontNew->m_dyUnscaled * pfontNew->m_ryScale);
                    m_pfontCur = pfontNew;
                    m_fontOther.m_rxScale *= r;
                    m_fontOther.m_ryScale *= r;
                    RGBA rgba = m_rgbaOther;
                    rgba.a = m_rgbaCur.a;
                    m_rgbaCur = rgba;
                    m_fDirty = one;
                } else {
                    m_pfontCur = m_pfontBase;
                    fDone = 1;
                    m_rgbaCur = m_rgbaBase;
                    m_fDirty = one;
                }
            }
            break;
        case '^':
            if (pch[1] == '^') {
                m_pchCur = pch + 1;
                fDone = 1;
            } else if (pch[1] == '.') {
                PopScaling(m_pfontCur);
                m_pchCur += 2;
            } else {
                float rScale = (float)(pch[1] - '0') + (float)(pch[2] - '0') * 0.1f;
                PushScaling(m_pfontCur, rScale * m_pfontCur->m_rxScale, rScale * m_pfontCur->m_ryScale);
                m_pchCur += 3;
            }
            break;
        default:
            fDone = 1;
            break;
        }
    } while (!fDone);
    return *m_pchCur++;
}
