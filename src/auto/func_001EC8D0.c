#include "m2c_prelude.h"
s32 func_001EC880();                                /* extern */
extern s32 D_003E1590;

s32 func_001EC8D0(void) {
    s32 var_v0;

    var_v0 = func_001EC880();
    if (var_v0 == 0) {
        var_v0 = D_003E1590;
    }
    return var_v0;
}
