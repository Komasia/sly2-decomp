#include "m2c_prelude.h"
M2C_UNK InitXfm__FP3XFM();                            /* extern */

void func_001BEA40(void *arg0) {
    InitXfm__FP3XFM();
    M2C_FIELD(arg0, f32 *, 0x11C) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x120) = 4.0f;
    M2C_FIELD(arg0, f32 *, 0x124) = 1000.0f;
}
