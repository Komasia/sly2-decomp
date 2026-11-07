#include "m2c_prelude.h"
// name: SafeHouse port (PentFromDz)
s32 PentFromDz__FP3DZGP2DZ(void *arg0, s32 arg1) {
    return M2C_FIELD(arg0, s32 *, 0x60) + (((s32) ((arg1 - M2C_FIELD(arg0, s32 *, 8)) * 0xCCCCCCCD) >> 3) * 0x60);
}
