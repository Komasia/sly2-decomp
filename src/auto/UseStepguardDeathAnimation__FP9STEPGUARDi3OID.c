#include "m2c_prelude.h"
void UseStepguardDeathAnimation__FP9STEPGUARDi3OID(void *arg0, s32 arg1, s32 arg2) {
    u32 temp_a3;
    void *temp_v0;

    temp_a3 = M2C_FIELD(arg0, u32 *, 0x230);
    if (temp_a3 < 4U) {
        M2C_FIELD(arg0, u32 *, 0x230) = (u32) (temp_a3 + 1);
        temp_v0 = arg0 + ((temp_a3 * 0x18) + 0x234);
        M2C_FIELD(temp_v0, s32 *, 0) = arg1;
        M2C_FIELD(temp_v0, s32 *, 4) = arg2;
    }
}
