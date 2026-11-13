#include "m2c_prelude.h"
// name: SafeHouse port (OverlapKindProjectile)
s32 OverlapKindProjectile__FP3ALOT0(s32 arg0, s32 arg1) {
    s32 var_a3;

    var_a3 = OverlapKindAlo__FP3ALOT0(arg0, arg1);
    if (*M2C_FIELD(arg1, s32 **, 0x14) == *M2C_FIELD(M2C_FIELD(arg0, void **, 0x200), s32 **, 0x14)) {
        var_a3 = func_00134310(var_a3, 1);
    }
    return var_a3;
}
