#include "m2c_prelude.h"
s32 FUN_0018d2e8(void *, s32);                      /* extern */
s32 func_001AC598();                                /* extern */
M2C_UNK func_001ACB58(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_001ACC38(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_001ADE70(M2C_UNK *);                   /* extern */
extern M2C_UNK D_002E6550;
extern M2C_UNK D_002E65A0;

s32 func_001ABBE0(void *arg0) {
    s32 var_s1;

    var_s1 = func_001AC598();
    if ((var_s1 != 0) || (var_s1 = FUN_0018d2e8(arg0, M2C_FIELD(arg0, s32 *, 0xFD50)), (var_s1 != 0))) {
        func_001ACC38(&D_002E6550, 3);
        func_001ACB58(&D_002E6550, 0x23);
        func_001ADE70(&D_002E65A0);
    }
    return var_s1;
}
