#include "m2c_prelude.h"
M2C_UNK func_0019FD30(s32, void *, void *, f32);    /* extern */

void func_0019EA60(void *arg0) {
    void *temp_a2;

    temp_a2 = M2C_FIELD(arg0, void **, 0xC);
    if (M2C_FIELD(temp_a2, s32 *, 0x19C) == 0) {
        func_0019FD30(M2C_FIELD(arg0, s32 *, 0) + 0x9E0, (temp_a2 == NULL) ? NULL : (temp_a2 + 0x190), temp_a2, M2C_FIELD(arg0, f32 *, 0x10));
    }
}
