// OpenFrame (Sly 1 frm.c): open the next of the two frames for building (waiting until the render thread is done
// with it): its pending releases cleared, fonts not yet uploaded, and the main GIF / VIF packets started in its
// buffers (the GIF one with the frame's 12 setup qwords D_002DF740).
#include "vifs.h"
#include "gifs.h"
struct FRM {
    int cqwGifs;     /* 0x00 */
    QW *aqwGifs;     /* 0x04 */
    QW *aqwGifsBuf;  /* 0x08 */
    int cqwGifsBuf;  /* 0x0c */
    int cqwVifs;     /* 0x10 */
    QW *aqwVifs;     /* 0x14 */
    QW *aqwVifsBuf;  /* 0x18 */
    int cqwVifsBuf;  /* 0x1c */
    int cqwVifsRender;   /* 0x20: the VIF chain sent from aqwVifsRender */
    QW *aqwVifsRender;   /* 0x24 */
    int n28;             /* 0x28 */
    int grfFontLoaded;   /* 0x2c: the fonts uploaded this frame (CFontBrx::FEnsureLoaded) */
    int grf;             /* 0x30: bit 0 blend the previous frame (func_00160F98) */
    int adl[6];          /* 0x34: two DLs of pending releases (func_00160CE0) */
    int n4C;             /* 0x4c */
};
extern FRM *g_pfrmOpen;
extern FRM D_002DEA50[2];        /* the two frames */
extern unsigned int D_002DEB10;   /* the next frame to open */
extern VIFS D_002DEA28;           /* the main VIF packet */
extern GIFS D_002DEA00;           /* the main GIF packet */
extern int D_003D3980;
extern int D_002DEB1C;            /* semaphore: frames free to build */
extern int D_002DDF54;
extern QW D_002DF740[];
extern "C" void func_001C2A78(int phase);
extern "C" void WaitSema(int sid) asm("WaitSema");
extern "C" void func_00160CE0(FRM *pfrm);   /* ClearPendingFrame */
void OpenFrame()
{
    if (!D_003D3980)
        func_001C2A78(3);
    WaitSema(D_002DEB1C);
    g_pfrmOpen = &D_002DEA50[D_002DEB10++];
    if (D_002DEB10 >= 2)
        D_002DEB10 = 0;
    func_00160CE0(g_pfrmOpen);
    g_pfrmOpen->n4C = D_002DDF54;
    g_pfrmOpen->grf = 1;
    g_pfrmOpen->grfFontLoaded = 0;
    g_pfrmOpen->aqwVifsRender = 0;
    D_002DEA00.AllocStatic(g_pfrmOpen->cqwGifsBuf, g_pfrmOpen->aqwGifsBuf);
    D_002DEA28.AllocStatic(g_pfrmOpen->cqwVifsBuf, g_pfrmOpen->aqwVifsBuf);
    D_002DEA00.AddDmaRefs(12, D_002DF740);
    D_002DEA00.AddDmaCnt();
}
