#include "m2c_prelude.h"
void func_0018DE18(s32 arg0, s32 arg1) {
    void *temp_v0;

    if (arg1 != 0) {
        M2C_FIELD(arg0, s32 *, 0x9C0) = 1;
        StartInteract__FP5ACTORii3JTL(arg0 + 0x4C0, 6, arg1, 0);
    } else if (M2C_FIELD(arg0, s32 *, 0x4C8) == 6) {
        temp_v0 = M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_v0, void (**)(s32, M2C_UNK), 0x2C4)(arg0 + M2C_FIELD(temp_v0, s16 *, 0x2C0), 0);
    }
}
