#include "m2c_prelude.h"
f32 UCompleteLoop__FP4LOOP(void *arg0) {
    f32 temp_f2;

    temp_f2 = M2C_FIELD(arg0, f32 *, 0x60);
    return (M2C_FIELD(arg0, f32 *, 0x64) / temp_f2) / (((f32) M2C_FIELD(arg0, s32 *, 0x1C) / temp_f2) + M2C_FIELD(arg0, f32 *, 0x68));
}
