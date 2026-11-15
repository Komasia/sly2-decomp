/* CFontBrx::SetupDraw (Sly 1 font.c): start drawing text with the font: the scissor of the clip box (if any), the
 * font's upload, then the sprite state: texture flush when uploaded, its GS test (or the default), alpha blend,
 * TEX0 / TEX1 / CLAMP and the sprite prim; then the RGBAQ / UV / XYZF2 list for the glyphs. */
#include "h2_gs.h"
typedef unsigned long ulong __attribute__((mode(DI)));
struct GIFS;
struct CFontBrx { char pad[0x3C]; int m_fGstest; ulong m_gstest; int m_z; int pad4C; ulong m_tex0; };
struct CTextBox { float x, y, dx, dy; };
void AddPrimPack(struct GIFS *, int, int, int) asm("AddPrimPack__4GIFSiiUl");
void PackAD(struct GIFS *, int, ulong) asm("PackAD__4GIFSll");
void AddPrimList(struct GIFS *, int, ulong) asm("AddPrimList__4GIFSiUl");
int FEnsureLoaded__8CFontBrxP4GIFS(struct CFontBrx *, struct GIFS *);
void SetupDraw__8CFontBrxP8CTextBoxP4GIFS(struct CFontBrx *pfont, struct CTextBox *ptbxClip, struct GIFS *pgifs)
{
    int fFlush;
    if (ptbxClip) {
        int xRight, yBottom, xLeft, yTop;
        xRight = (int)((ptbxClip->x + ptbxClip->dx * 512.0f) * 0.0015625f) - 1;
        yBottom = (int)((ptbxClip->y + ptbxClip->dy) * 0.45454547f) - 1;
        xLeft = (int)(ptbxClip->x * 0.8f);
        yTop = (int)(ptbxClip->y * 0.45454547f);
        AddPrimPack(pgifs, 0, 1, GIF_REG_AD);
        PackAD(pgifs, GS_REG_SCISSOR_1, (ulong)xLeft | ((ulong)xRight << 16) | ((ulong)yTop << 32) | ((ulong)yBottom << 48));
    }
    fFlush = FEnsureLoaded__8CFontBrxP4GIFS(pfont, pgifs);
    AddPrimPack(pgifs, GS_PRIM_SPRITE, 1, GIF_REG_AD);
    if (fFlush)
        PackAD(pgifs, GS_REG_TEXFLUSH, 0);
    PackAD(pgifs, GS_REG_TEST_1, pfont->m_fGstest ? pfont->m_gstest : 0x31001);
    PackAD(pgifs, GS_REG_ALPHA_1, 0x44);
    PackAD(pgifs, GS_REG_TEX0_1, pfont->m_tex0);
    PackAD(pgifs, GS_REG_TEX1_1, 0x60);
    PackAD(pgifs, GS_REG_CLAMP_1, 5);
    PackAD(pgifs, GS_REG_PRIM, 0x1D6);
    AddPrimList(pgifs, 5, 0x43431);
}
