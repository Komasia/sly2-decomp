// FinalizeFrameGifs: close the frame's GIF packet - one last A+D register write (register 0x61, FINISH, so the GS
// signals the end of drawing), the end of the primitive and of the DMA chain - and hand the packet to the caller.
#include "gifs.h"

void FinalizeFrameGifs(GIFS *pgifs, int *pcqw, QW **paqw)
{
    pgifs->AddPrimPack(0, 1, 0xE);
    pgifs->PackAD(0x61, 0);
    pgifs->AddPrimEnd();
    pgifs->AddDmaEnd();
    pgifs->Detach(pcqw, paqw);
}
