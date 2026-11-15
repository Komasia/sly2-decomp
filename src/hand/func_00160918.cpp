// EnsureVu1Code (Sly 1 frm.c): reference the VU1 microcode between pqwStart and pqwEnd in the DMA chain.
#include "dmas.h"
extern "C" void EnsureVu1Code__FP4VIFSPvT1(DMAS *pdmas, QW *pqwStart, QW *pqwEnd)
{
    pdmas->AddDmaRefs((uint)((char *)pqwEnd - (char *)pqwStart + 15) >> 4, pqwStart);
}
