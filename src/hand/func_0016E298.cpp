// func_0016E298: a render pass's setup: the common setup, then a DMA call of each of the D_003DCFA0 queued packets.
#include "vifs.h"
extern int D_003DCFA0;
extern QW *D_003DCFA8[];
extern "C" void func_0016E1A8(VIFS *pvifs);
extern "C" void func_0016E298(VIFS *pvifs)
{
    int i;
    func_0016E1A8(pvifs);
    for (i = 0; i < D_003DCFA0; i++)
        pvifs->AddDmaCall(D_003DCFA8[i]);
}
