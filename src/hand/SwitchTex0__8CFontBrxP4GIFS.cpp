// CFontBrx::SwitchTex0 (Sly 1 font.c): switch the sprite list to this font's texture (uploading it first if needed:
// FEnsureLoaded, 0x15F148, then a texture flush).
#include "gifs.h"
#include "h2_gs.h"
class CFontBrx {
public:
    char pad[0x50];
    ulong m_tex0;
    int FUN_15F148(GIFS *pgifs);
    void SwitchTex0(GIFS *pgifs);
};
void CFontBrx::SwitchTex0(GIFS *pgifs)
{
    int fLoaded = FUN_15F148(pgifs);
    pgifs->AddPrimPack(GS_PRIM_SPRITE, 1, GIF_REG_AD);
    if (fLoaded)
        pgifs->PackAD(GS_REG_TEXFLUSH, 0);
    pgifs->PackAD(GS_REG_TEX0_1, m_tex0);
    pgifs->PackAD(GS_REG_PRIM, 0x1d6);
    pgifs->AddPrimList(5, 0x43431);
}
