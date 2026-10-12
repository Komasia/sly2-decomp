#include "m2c_prelude.h"
extern f32 D_002BF900;

f32 FUN_001cf138(void *arg0, s32 arg1, f32 fparg0, f32 fparg1) {
    f32 var_f12;

    var_f12 = fparg0 + fparg1;
    if (arg1 == M2C_FIELD(arg0, s32 *, 0xBC)) {
        var_f12 += D_002BF900;
    }
    return var_f12;
}
