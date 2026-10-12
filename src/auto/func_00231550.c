#include "m2c_prelude.h"
extern M2C_UNK D_002C44F0;

M2C_UNK *func_00231550(void *arg0, void *arg1) {
    M2C_UNK *var_v0;

    if (arg1 != NULL) {
        M2C_FIELD(arg1, s128 *, 0) = (s128) M2C_FIELD(arg0, s128 *, 0x60);
        M2C_FIELD(arg1, s128 *, 0x10) = (s128) M2C_FIELD(arg0, s128 *, 0x70);
        M2C_FIELD(arg1, s128 *, 0x20) = (s128) M2C_FIELD(arg0, s128 *, 0x80);
        M2C_FIELD(arg1, s128 *, 0x30) = (s128) M2C_FIELD(arg0, s128 *, 0x90);
    }
    var_v0 = M2C_FIELD(arg0, M2C_UNK **, 0x50);
    if (var_v0 == NULL) {
        var_v0 = &D_002C44F0;
    }
    return var_v0;
}
