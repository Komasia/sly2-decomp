#include "vifs.h"
#include "gifs.h"
extern "C" void func_00160918(VIFS *pvifs, void *pvStart, void *pvEnd);
extern char D_0025E680[];
extern char D_00262320[];
void FinalizeFrameVifs(VIFS *pvifs, int *pcqw, QW **paqw)
{
    QW aqw[8];
    GIFS gifs;
    gifs.AllocStatic(8, aqw);
    gifs.AddPrimPack(0, 1, 0xE);
    gifs.PackAD(0x61, 0);
    gifs.AddPrimEnd();
    pvifs->AddDmaCnt();
    pvifs->AddVifFlush();
    pvifs->AddVifGifs(&gifs);
    pvifs->EndDmaCnt();
    func_00160918(pvifs, D_0025E680, D_00262320);
    pvifs->AddDmaEnd();
    pvifs->Detach(pcqw, paqw);
}
