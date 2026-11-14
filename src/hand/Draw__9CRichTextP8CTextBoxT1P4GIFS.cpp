struct RGBA { unsigned char r, g, b, a; };
struct GIFS;
struct FONT { char pad[0xC]; int dy; char pad10[4]; float ry; };
struct CFont;
class CTextBox {
public:
    float x, y, dx, dy;
    RGBA rgba;
    int jh;
    int jv;
};
class CRichText {
public:
    unsigned char *m_achz;
    unsigned char *m_pchCur;
    CFont *m_pfontCur;
    FONT *m_pfontBase;
    char pad[0x150 - 0x10];
    int m_fDirty;
    unsigned int m_rgbaCur;
    void Draw(CTextBox *ptb, CTextBox *ptbClip, GIFS *pgifs);
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
void CRichText::Draw(CTextBox *ptb, CTextBox *ptbClip, GIFS *pgifs)
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
    if (ptb->jv == 0) {
        y = ptb->y;
    } else {
        float dy = (float)(iline + 1) * ((float)m_pfontBase->dy * m_pfontBase->ry);
        if (ptb->jv == 2)
            y = ptb->y + ptb->dy - dy;
        else
            y = ptb->y + (ptb->dy - dy) * 0.5f;
    }
    rgba = ptb->rgba;
    SetBaseColor(this, &rgba);
    pfontSetup = 0;
    Reset(this);
    pdx = adx;
    while ((ch = ChNext(this)) != 0) {
        if (ch == '\n') {
            fNewLine = 1;
            pdx++;
            y += (float)m_pfontBase->dy * m_pfontBase->ry;
            continue;
        }
        if (fNewLine) {
            if (ptb->jh == 0)
                x = ptb->x;
            else {
                float dxLine = *pdx;
                if (ptb->jh == 2)
                    x = ptb->x + ptb->dx - dxLine;
                else
                    x = ptb->x + (ptb->dx - dxLine) * 0.5f;
            }
            fNewLine = 0;
        }
        if (!pfontSetup) {
            SetupDraw(m_pfontCur, ptbClip, pgifs);
            pfontSetup = m_pfontCur;
        } else if (m_fDirty) {
            SwitchTex0(m_pfontCur, pgifs);
            m_fDirty = 0;
        }
        x += DxDrawCh(m_pfontCur, ch, x, y, m_rgbaCur, pgifs);
    }
    func_0015F000(m_pfontCur, ptbClip, pgifs);
}
