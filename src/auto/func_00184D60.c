#include "m2c_prelude.h"
s32 scePadGetState(s32, s32);                        /* extern */
s32 scePadGetState(s32, s32);                       /* extern */

s32 func_00184D60(s32 arg0, s32 arg1) {
    s32 var_a2;

    var_a2 = 0;
    if (M2C_FIELD(arg1, s32 *, 8) == 2) {
        var_a2 = FOpenSector__18CBinaryInputStreamUiUi(arg0, M2C_FIELD(arg1, s32 *, 0), M2C_FIELD(arg1, s32 *, 4));
    }
    return var_a2;
}
