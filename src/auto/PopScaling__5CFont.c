#include "m2c_prelude.h"
void PopScaling__5CFont(void *arg0) {
    s32 temp_v0;
    void *temp_v1;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x18) - 1;
    M2C_FIELD(arg0, s32 *, 0x18) = temp_v0;
    temp_v1 = arg0 + ((temp_v0 * 8) + 0x1C);
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) M2C_FIELD(temp_v1, f32 *, 0);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) M2C_FIELD(temp_v1, f32 *, 4);
}
