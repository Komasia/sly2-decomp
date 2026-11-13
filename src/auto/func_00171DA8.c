#include "m2c_prelude.h"
// name: SafeHouse port (FGuardRunsCommands)
s32 FGuardRunsCommands__FP2LOT0(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_a1;

    temp_v0 = func_00205458(arg0, 0x9C);
    var_a1 = 0;
    if ((temp_v0 != 0) && (M2C_FIELD(temp_v0, s32 *, 0x30) == 5)) {
        var_a1 = M2C_FIELD(temp_v0, s32 *, 0x40) == arg1;
    }
    return var_a1;
}
