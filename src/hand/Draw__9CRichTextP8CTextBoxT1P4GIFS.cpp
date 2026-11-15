struct RGBA { unsigned char r, g, b, a; };
struct GIFS;
struct CFontM { char pad[0xC]; int m_dyUnscaled; char pad10[4]; float m_ryScale; };   /* CFont's metrics */
struct CFont;
class CTextBox {
public:
    float x, y, dx, dy;
    RGBA rgba;
    int jh;     /* 0 left, 1 centre, 2 right */
    int jv;     /* 0 top, 1 centre, 2 bottom */
};
class CRichText {
public:
    unsigned char *m_achz;
    unsigned char *m_pchCur;
    CFont *m_pfontCur;
    CFontM *m_pfontBase;
    char pad[0x150 - 0x10];
    int m_fDirty;
    unsigned int m_rgbaCur;
    void Draw(CTextBox *ptbx, CTextBox *ptbxClip, GIFS *pgifs);
};
extern "C" {
void *s1_memset(void *, int, unsigned int) asm("memset");
void Reset(CRichText *p) asm("Reset__9CRichText");
int ChNext(CRichText *p) asm("ChNext__9CRichText");
float DxFromCh(CFont *pfont, int ch) asm("DxFromCh__8CFontBrxc");
void SetBaseColor(CRichText *p, RGBA *prgba) asm("SetBaseColor__9CRichTextP4RGBA");
void SetupDraw(CFont *pfont, CTextBox *ptb, GIFS *pgifs) asm("SetupDraw__8CFontBrxP8CTextBoxP4GIFS");
void SwitchTex0(CFont *pfont, GIFS *pgifs) asm("SwitchTex0__8CFontBrxP4GIFS");
float DxDrawCh(CFont *pfont, int ch, float x, float y, unsigned int rgba, GIFS *pgifs) asm("DxDrawCh__8CFontBrxcffUiP4GIFS");
void func_0015F000(CFont *pfont, CTextBox *ptb, GIFS *pgifs);
}
/* CRichText::Draw (Sly 1 font.c): draw the text in a text box: measure each line (up to 64), place the block by the
 * box's vertical justification and each line by its horizontal one, then draw glyph by glyph, setting up the font
 * once and switching its texture when the markup changes font. */
void CRichText::Draw(CTextBox *ptbx, CTextBox *ptbxClip, GIFS *pgifs)
{
    float adx[64];
    int fNewLine = 1;
    int iline = 0;
    int ch;
    float x, y;
    CFont *pfontSetup;
    float *pdx;
    RGBA rgba;
    s1_memset(adx, 0, sizeof(adx));
    Reset(this);
    {
        int chT;
        while ((chT = ChNext(this)) != 0) {
            if (chT == '\n')
                iline++;
            else
                adx[iline] += DxFromCh(m_pfontCur, chT);
        }
    }
    if (ptbx->jv == 0) {
        y = ptbx->y;
    } else {
        float dy = (float)(iline + 1) * ((float)m_pfontBase->m_dyUnscaled * m_pfontBase->m_ryScale);
        if (ptbx->jv == 2)
            y = ptbx->y + ptbx->dy - dy;
        else
            y = ptbx->y + (ptbx->dy - dy) * 0.5f;
    }
    rgba = ptbx->rgba;
    SetBaseColor(this, &rgba);
    pfontSetup = 0;
    Reset(this);
    pdx = adx;
    while ((ch = ChNext(this)) != 0) {
        if (ch == '\n') {
            fNewLine = 1;
            pdx++;
            y += (float)m_pfontBase->m_dyUnscaled * m_pfontBase->m_ryScale;
            continue;
        }
        if (fNewLine) {
            if (ptbx->jh == 0)
                x = ptbx->x;
            else {
                float dxLine = *pdx;
                if (ptbx->jh == 2)
                    x = ptbx->x + ptbx->dx - dxLine;
                else
                    x = ptbx->x + (ptbx->dx - dxLine) * 0.5f;
            }
            fNewLine = 0;
        }
        if (!pfontSetup) {
            SetupDraw(m_pfontCur, ptbxClip, pgifs);
            pfontSetup = m_pfontCur;
        } else if (m_fDirty) {
            SwitchTex0(m_pfontCur, pgifs);
            m_fDirty = 0;
        }
        x += DxDrawCh(m_pfontCur, ch, x, y, m_rgbaCur, pgifs);
    }
    func_0015F000(m_pfontCur, ptbxClip, pgifs);
}
