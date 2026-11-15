// CloseFrame (Sly 1 frm.c CloseFrame): close the open frame: finalize its VIF and GIF packets into it, hand it
// the pending-release lists, and signal the render thread.
#include "vifs.h"
#include "gifs.h"
#include "dl.h"
struct FRM {
    int cqwGifs;     /* 0x00 */
    QW *aqwGifs;     /* 0x04 */
    int pad8[2];
    int cqwVifs;     /* 0x10 */
    QW *aqwVifs;     /* 0x14 */
    int pad18[2];
    int cqwVifsRender;   /* 0x20 */
    QW *aqwVifsRender;   /* 0x24 */
    int pad28[3];
    DL dlRelease;        /* 0x34: objects to release */
    DL dlFree;           /* 0x40: buffers to free */
};
extern FRM *g_pfrmOpen;
extern VIFS D_002DEA28;
extern GIFS D_002DEA00;
extern DL D_002DEAF0;
extern DL D_002DEB00;
extern int D_002DEB18;   /* frames to render */
void FinalizeFrameVifs(VIFS *pvifs, int *pcqw, QW **paqw);
void FinalizeFrameGifs(GIFS *pgifs, int *pcqw, QW **paqw);
extern "C" void ClearDl(DL *pdl) asm("ClearDl__FP2DL");
extern "C" void SignalSema(int sid) asm("SignalSema");
// name: Sly 1 frm.c CloseFrame (after FinalizeFrameGifs in both games; suggested by h2)
extern "C" void CloseFrame__Fv()
{
    FinalizeFrameVifs(&D_002DEA28, &g_pfrmOpen->cqwVifs, &g_pfrmOpen->aqwVifs);
    FinalizeFrameGifs(&D_002DEA00, &g_pfrmOpen->cqwGifs, &g_pfrmOpen->aqwGifs);
    g_pfrmOpen->cqwVifsRender = g_pfrmOpen->aqwVifs + g_pfrmOpen->cqwVifs - g_pfrmOpen->aqwVifsRender;
    g_pfrmOpen->dlRelease = D_002DEAF0;
    ClearDl(&D_002DEAF0);
    g_pfrmOpen->dlFree = D_002DEB00;
    ClearDl(&D_002DEB00);
    g_pfrmOpen = 0;
    SignalSema(D_002DEB18);
}
