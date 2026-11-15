// func_0016E228: a render pass's common finish: 11 cleared qwords unpacked at VU1 address 10, the microprogram at
// 0x3AB0 started, then wait for VU1 and the GIF (FLUSHA).
#include "vifs.h"
extern "C" void *s1_memset(void *pv, int n, int cb) asm("memset");
extern char D_00003AB0[];
extern "C" void func_0016E228(VIFS *pvifs)
{
    uint *pun;
    pvifs->AddDmaCnt();
    pvifs->UnpackHelper(UPK_V4_16, 11, 10, 0, &pun);
    s1_memset(pun, 0, 0x58);
    pvifs->AddVifMscal(D_00003AB0);
    pvifs->AddVifFlusha();
    pvifs->EndDmaCnt();
}
