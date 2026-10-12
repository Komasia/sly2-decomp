#include "m2c_prelude.h"
void FreeDrain__10CByteQueuei(void *arg0, s32 arg1) {
    s32 var_a1;

    var_a1 = arg1;
    if ((var_a1 != 0) || (var_a1 = M2C_FIELD(arg0, s32 *, 0x18), (var_a1 != 0))) {
        M2C_FIELD(arg0, s32 *, 0x10) = (s32) (M2C_FIELD(arg0, s32 *, 0x10) + var_a1);
        M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) - var_a1);
    }
}
