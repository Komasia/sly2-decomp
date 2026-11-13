#include "m2c_prelude.h"
// name: SafeHouse port (OverlapKindHide)
s32 OverlapKindHide__FP3ALOT0(s32 arg0, s32 arg1) {
    s32 var_s1;
    s32 var_v0;

    var_s1 = OverlapKindAlo__FP3ALOT0(arg0, arg1);
    if (FIsBasicDerivedFrom__FP5BASIC3CID(arg1, 0x34) != 0) {
        if ((M2C_FIELD(arg1, s32 *, 0x4C8) == 1) && (arg0 == M2C_FIELD(arg1, s32 *, 0x4D4))) {
            var_s1 = func_00134310(var_s1, 1);
        }
        var_v0 = var_s1;
        if ((u32) (M2C_FIELD(arg1, s32 *, 0x2DC) - 6) < 2U) {
            var_v0 = var_s1;
            if (arg0 == M2C_FIELD(arg1, s32 *, 0x2CC)) {
                var_s1 = func_00134310(var_s1, 1);
                goto block_7;
            }
        }
    } else {
block_7:
        var_v0 = var_s1;
    }
    return var_v0;
}
