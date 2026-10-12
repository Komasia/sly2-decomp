#include "m2c_prelude.h"
s32 FCheckLm__FP2LMf(void *arg0, f32 fparg0) {
    s32 var_v0;

    var_v0 = 0;
    if ((M2C_FIELD(arg0, f32 *, 0) < fparg0) && (fparg0 < M2C_FIELD(arg0, f32 *, 4))) {
        var_v0 = 1;
    }
    return var_v0;
}
