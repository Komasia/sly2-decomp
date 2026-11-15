// FinalizeFrameVifs (Sly 1 frm.c): close the frame's VIF packet: a GIF packet with the GS FINISH write (after a VIF
// flush), the VU1 microcode (D_0025E680..D_00262320), the end of the chain; the packet goes to the caller.
#include "vifs.h"
#include "h2_gs.h"
#include "gifs.h"
extern "C" void EnsureVu1Code(VIFS *pvifs, void *pvStart, void *pvEnd) asm("EnsureVu1Code__FP4VIFSPvT1");
extern char D_0025E680[];
extern char D_00262320[];
void FinalizeFrameVifs(VIFS *pvifs, int *pcqw, QW **paqw)
{
    QW aqw[8];
    GIFS gifs;
    gifs.AllocStatic(8, aqw);
    gifs.AddPrimPack(0, 1, GIF_REG_AD);
    gifs.PackAD(GS_REG_FINISH, 0);
    gifs.AddPrimEnd();
    pvifs->AddDmaCnt();
    pvifs->AddVifFlush();
    pvifs->AddVifGifs(&gifs);
    pvifs->EndDmaCnt();
    EnsureVu1Code(pvifs, D_0025E680, D_00262320);
    pvifs->AddDmaEnd();
    pvifs->Detach(pcqw, paqw);
}
