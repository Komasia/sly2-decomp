#include "m2c_prelude.h"
void AddStepguardEffect__FP9STEPGUARD3OID3ZPK(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 temp_t0;
    void *temp_v0;

    temp_t0 = M2C_FIELD(arg0, u32 *, 0x18C);
    if (temp_t0 < 0xCU) {
        M2C_FIELD(arg0, u32 *, 0x18C) = (u32) (temp_t0 + 1);
        temp_v0 = arg0 + ((temp_t0 * 0xC) + 0x190);
        M2C_FIELD(temp_v0, s32 *, 0) = arg1;
        M2C_FIELD(temp_v0, s32 *, 4) = arg2;
        M2C_FIELD(temp_v0, s32 *, 8) = arg3;
    }
}
