#include "m2c_prelude.h"
extern f32 D_002DDED0;

s32 FUpdatableSaa__FP3SAA(void *arg0) {
    if (M2C_FIELD(arg0, f32 *, 0x10) != D_002DDED0) {
        M2C_FIELD(arg0, f32 *, 0x10) = (f32) D_002DDED0;
        return 1;
    }
    return 0;
}
