#include "m2c_prelude.h"
void func_001F7D10(s32 arg0, s32 arg1, f32 fparg0) {
    void *temp_v0;
    void *temp_v0_2;

    if (fparg0 <= 0.0f) {
        if (FIsBasicDerivedFrom__FP5BASIC3CID(arg0, 0x69) == 0) {
            temp_v0 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_v0, void (**)(s32), 0x4C)(arg0 + M2C_FIELD(temp_v0, s16 *, 0x48));
        }
    } else {
        temp_v0_2 = M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_v0_2, void (**)(s32), 0x44)(arg0 + M2C_FIELD(temp_v0_2, s16 *, 0x40));
    }
    M2C_FIELD(arg0, f32 *, 0x12C) = fparg0;
}
