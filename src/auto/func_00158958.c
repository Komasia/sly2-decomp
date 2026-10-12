#include "m2c_prelude.h"
s32 func_00158958(void *arg0, s32 arg1) {
    return M2C_FIELD(arg0, s32 *, 0x60) + (((s32) ((arg1 - M2C_FIELD(arg0, s32 *, 8)) * 0xCCCCCCCD) >> 3) * 0x60);
}
