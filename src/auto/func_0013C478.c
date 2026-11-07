#include "m2c_prelude.h"
// name: SafeHouse port (IdBooty)
s32 IdBooty__FP2LO(void *arg0) {
    s32 *temp_v1;
    s32 var_v0;

    temp_v1 = M2C_FIELD(arg0, s32 **, 0x158);
    var_v0 = -1;
    if (temp_v1 != NULL) {
        var_v0 = *temp_v1;
    }
    return var_v0;
}
