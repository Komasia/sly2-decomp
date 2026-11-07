#include "m2c_prelude.h"
// name: SafeHouse port (FScreenObjDone)
s32 FScreenObjDone__FP2LO(void *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x58) < 2) {
        var_v1 = M2C_FIELD(arg0, s32 *, 0x64) < 2;
    }
    return var_v1;
}
