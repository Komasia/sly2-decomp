#include "vifs.h"
extern "C" void *func_002333B4(void *pv, int n, int cb);
extern char D_00003AB0[];
extern "C" void func_0016E228(VIFS *pvifs)
{
    uint *pun;
    pvifs->AddDmaCnt();
    pvifs->UnpackHelper(UPK_V4_16, 11, 10, 0, &pun);
    func_002333B4(pun, 0, 0x58);
    pvifs->AddVifMscal(D_00003AB0);
    pvifs->AddVifFlusha();
    pvifs->EndDmaCnt();
}
