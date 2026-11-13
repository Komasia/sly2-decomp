#include "m2c_prelude.h"
extern s32 D_002DD2CC;

s32 func_00258178(s32 arg0) {
    s32 temp_v0;

    func_00255DE8(arg0);
    func_00255C00(arg0, (s32) &D_002DD2CC);
    temp_v0 = M2C_FIELD(arg0, s32 *, 4) | 0x8000;
    M2C_FIELD(arg0, s32 *, 4) = temp_v0;
    return temp_v0;
}
