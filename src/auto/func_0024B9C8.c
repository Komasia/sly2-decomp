#include "m2c_prelude.h"
M2C_UNK sceIpuRestartDMA(s32);                         /* extern */

s32 func_0024B9C8(void *arg0) {
    sceIpuRestartDMA(M2C_FIELD(arg0, s32 *, 0x40) + 0x68);
    return 1;
}
