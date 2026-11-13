#include "m2c_prelude.h"
/*
Decompilation failure in function RunItems__FP2LOP3BRK:

Found jr instruction at chunk.s line 67, but the corresponding jump table is not provided.

Please include it in the input .s file(s), or in an additional file.

*/

s32 func_001BB918(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 var_v0;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x150);
    var_v0 = temp_a0 < 8;
    if (var_v0 != 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x154) + (temp_a0 * 8);
        M2C_FIELD(arg0, s32 *, 0x150) = (s32) (temp_a0 + 1);
        M2C_FIELD(var_v0, s32 *, 4) = arg2;
        M2C_FIELD(var_v0, s32 *, 0) = arg1;
    }
    return var_v0;
}
