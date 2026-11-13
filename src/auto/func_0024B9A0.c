#include "m2c_prelude.h"
M2C_UNK sceIpuStopDMA(s32);                         /* extern */

s32 func_0024B9A0(void *arg0) {
    sceIpuStopDMA(M2C_FIELD(arg0, s32 *, 0x40) + 0x68);
    return 1;
}
