/* CaptureOverlayFrame: the GIF packet that copies the frame on screen into the overlay's texture: a register set-up
 * from the texture's base / width (D_002DECD0), then two sprites (DMA refs to the packets D_002DFB00 / D_002DFB20)
 * drawing the screen's two halves into it. Layout: SafeHouse port (overlay.cpp; "orig0x1475C0"). */
#include "common.h"
struct TEX { ulong ul0; ulong ul8; ulong ul10; };   /* the overlay's texture: +0x0 its base (bits 16..21), +0x10 its width */
extern char D_002DEA00[];   /* the GIF packet being built */
extern struct TEX D_002DECD0;   /* the overlay's texture */
extern char D_002DFB00[];
extern char D_002DFB20[];
void AddPrimPack(void *g, int a, int b, ulong c) asm("AddPrimPack__4GIFSiiUl");
void PackAD(void *g, int reg, ulong v) asm("PackAD__4GIFSll");
void EndDmaCnt(void *g) asm("EndDmaCnt__4DMAS");
void AddDmaRefs(void *g, int n, void *pv) asm("AddDmaRefs__4DMASiP2QW");
void AddDmaCnt(void *g) asm("AddDmaCnt__4DMAS");
void PackRGBA(void *g, int rgba) asm("PackRGBA__4GIFSUi");
void PackUV(void *g, int a, int b) asm("PackUV__4GIFSii");
void PackXYZ(void *g, int a, int b, int c) asm("PackXYZ__4GIFSiii");
// name: SafeHouse port (CaptureOverlayFrame)
void CaptureOverlayFrame__Fv(void)
{
    void *pgifs = D_002DEA00;
    struct TEX *ptex = &D_002DECD0;
    AddPrimPack(pgifs, 0, 1, 0xE);
    PackAD(pgifs, 0x4D, (ptex->ul10 & 0x1FF) | (ptex->ul0 & 0x3F0000));
    PackAD(pgifs, 0x48, 0x31001);
    EndDmaCnt(pgifs);
    AddDmaRefs(pgifs, 2, D_002DFB00);
    AddDmaCnt(pgifs);
    AddPrimPack(pgifs, 0x316, 7, 0x53531EE);
    PackAD(pgifs, 0x15, 0x61);
    PackAD(pgifs, 0x3F, 0);
    PackRGBA(pgifs, 0x80808080);
    PackUV(pgifs, 8, 8);
    PackXYZ(pgifs, 0x7000, 0x7900, 0);
    PackUV(pgifs, 0x2008, 0xE08);
    PackXYZ(pgifs, 0x8000, 0x8700, 0);
    EndDmaCnt(pgifs);
    AddDmaRefs(pgifs, 2, D_002DFB20);
    AddDmaCnt(pgifs);
    AddPrimPack(pgifs, 0x316, 7, 0x53531EE);
    PackAD(pgifs, 0x15, 0x61);
    PackAD(pgifs, 0x3F, 0);
    PackRGBA(pgifs, 0x80808080);
    PackUV(pgifs, 8, 8);
    PackXYZ(pgifs, 0x8000, 0x7900, 0);
    PackUV(pgifs, 0x2008, 0xE08);
    PackXYZ(pgifs, 0x9000, 0x8700, 0);
}
