#include "m2c_prelude.h"
void MatchStepguardAnimationPhase__FP9STEPGUARD3OIDN31(void *arg0, s32 arg1, s32 arg2) {
    u32 temp_v1;
    void *temp_v0;

    temp_v1 = M2C_FIELD(arg0, u32 *, 0x148);
    if (temp_v1 < 4U) {
        M2C_FIELD(arg0, u32 *, 0x148) = (u32) (temp_v1 + 1);
        temp_v0 = arg0 + ((temp_v1 * 8) + 0x14C);
        M2C_FIELD(temp_v0, s32 *, 0) = arg1;
        M2C_FIELD(temp_v0, s32 *, 4) = arg2;
    }
}
