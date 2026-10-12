#include "m2c_prelude.h"
/* Warning: missing "jr $ra" in last block of func_00259D80 (initial). */

/* Warning: missing "jr $ra" in last block of func_00259DD8 (initial). */

extern M2C_UNK D_002DD2AC;
extern u32 D_002DD2D4;
extern M2C_UNK D_002DD598;
extern s32 D_003E0EA4;
extern M2C_UNK D_00452160;
extern M2C_UNK D_00452170;

s32 func_00259A88(s32 arg0) {
    s32 temp_v0;

    func_00255770(arg0);
    func_00255588(arg0, (s32) &D_002DD2AC);
    temp_v0 = M2C_FIELD(arg0, s32 *, 4) | 0x8000;
    M2C_FIELD(arg0, s32 *, 4) = temp_v0;
    return temp_v0;
}
