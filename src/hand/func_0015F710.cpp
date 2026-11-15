#include "gifs.h"
struct FONTHDR { char pad[4]; uchar dxChar, dxSpace, dy, ifont; float rScale; ushort cglyff; };   /* the font file's header */
struct BMP { char pad[0xE]; ushort ibmp; char pad2[4]; QW *aqwImage; int cqwImage; char pad3[4]; ulong tex0; };
struct CLUT { char pad[0xA]; ushort iclut; QW *aqwImage; int cqwImage; int pad14; ulong tex0; };
struct FONTDATA { FONTHDR *phdr; void *aglyff; BMP *pbmp; CLUT *pclut; };
/* Sly 1 CFontBrx (Sly 2 offsets) */
struct CFontBrx {
    int ifont, m_dxCharUnscaled, m_dxSpaceUnscaled, m_dyUnscaled; float m_rxScale, m_ryScale; char pad[0x50 - 0x18];
    ulong m_tex0; int m_cqwBmpGifs; QW *m_aqwBmpGifs; QW aqwBmpGifs[6]; int cqwBmpImage; QW *aqwBmpImage;
    int m_cqwClutGifs; QW *m_aqwClutGifs; QW aqwClutGifs[6]; int cqwClutImage; QW *aqwClutImage;
    int m_cglyff; void *m_aglyff;
};
extern "C" {
void func_0015F888(CFontBrx *pfont);
int func_00170548(void *pzpr, int i);   /* the VRAM address of a bitmap / CLUT */
void BuildBmpTex0__FP3BMPi(BMP *pbmp, int gsb);
void func_001ECBF0(BMP *pbmp, int gsb, GIFS *pgifs);
void func_001EC9D0(CLUT *pclut, int gsb);
void BuildClutGifs__FP4CLUTiP4GIFS(CLUT *pclut, int gsb, GIFS *pgifs);
/* func_0015F710: set up a built-in font from its data: metrics and glyphs from the header, registered in the font
 * table; its bitmap (and CLUT) placed in VRAM (pzpr) with their upload packets built into the font's own storage. */
void func_0015F710(CFontBrx *pfont, FONTDATA *pfontdata, void *pzpr)
{
    FONTHDR *phdr = pfontdata->phdr;
    pfont->ifont = phdr->ifont;
    func_0015F888(pfont);
    pfont->m_dxCharUnscaled = phdr->dxChar;
    pfont->m_dxSpaceUnscaled = phdr->dxSpace;
    pfont->m_dyUnscaled = phdr->dy;
    pfont->m_rxScale = phdr->rScale;
    pfont->m_ryScale = phdr->rScale;
    pfont->m_cglyff = phdr->cglyff;
    pfont->m_aglyff = pfontdata->aglyff;
    GIFS gifs;
    BMP *pbmp = pfontdata->pbmp;
    CLUT *pclut = pfontdata->pclut;
    int gsb = func_00170548(pzpr, pbmp->ibmp);
    BuildBmpTex0__FP3BMPi(pbmp, gsb);
    pfont->m_tex0 = pbmp->tex0;
    gifs.AllocStatic(6, pfont->aqwBmpGifs);
    func_001ECBF0(pbmp, gsb, &gifs);
    gifs.Detach(&pfont->m_cqwBmpGifs, &pfont->m_aqwBmpGifs);
    pfont->cqwBmpImage = pbmp->cqwImage;
    pfont->aqwBmpImage = pbmp->aqwImage;
    if (pclut) {
        gsb = func_00170548(pzpr, pclut->iclut);
        func_001EC9D0(pclut, gsb);
        pfont->m_tex0 |= pclut->tex0;
        gifs.AllocStatic(6, pfont->aqwClutGifs);
        BuildClutGifs__FP4CLUTiP4GIFS(pclut, gsb, &gifs);
        gifs.Detach(&pfont->m_cqwClutGifs, &pfont->m_aqwClutGifs);
        pfont->cqwClutImage = pclut->cqwImage;
        pfont->aqwClutImage = pclut->aqwImage;
    }
}
}
