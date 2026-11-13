#include "common.h"
struct G { ulong a; ulong b; ulong c; };
extern char D_002DEA00[];
extern struct G D_002DECD0;
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
    void *g = D_002DEA00;
    struct G *pg = &D_002DECD0;
    AddPrimPack(g, 0, 1, 0xE);
    PackAD(g, 0x4D, (pg->c & 0x1FF) | (pg->a & 0x3F0000));
    PackAD(g, 0x48, 0x31001);
    EndDmaCnt(g);
    AddDmaRefs(g, 2, D_002DFB00);
    AddDmaCnt(g);
    AddPrimPack(g, 0x316, 7, 0x53531EE);
    PackAD(g, 0x15, 0x61);
    PackAD(g, 0x3F, 0);
    PackRGBA(g, 0x80808080);
    PackUV(g, 8, 8);
    PackXYZ(g, 0x7000, 0x7900, 0);
    PackUV(g, 0x2008, 0xE08);
    PackXYZ(g, 0x8000, 0x8700, 0);
    EndDmaCnt(g);
    AddDmaRefs(g, 2, D_002DFB20);
    AddDmaCnt(g);
    AddPrimPack(g, 0x316, 7, 0x53531EE);
    PackAD(g, 0x15, 0x61);
    PackAD(g, 0x3F, 0);
    PackRGBA(g, 0x80808080);
    PackUV(g, 8, 8);
    PackXYZ(g, 0x8000, 0x7900, 0);
    PackUV(g, 0x2008, 0xE08);
    PackXYZ(g, 0x9000, 0x8700, 0);
}
