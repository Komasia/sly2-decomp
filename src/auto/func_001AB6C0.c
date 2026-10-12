#include "m2c_prelude.h"
s32 FUN_0018bc90(s32, s32, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK func_001ACC38(M2C_UNK *, M2C_UNK);          /* extern */
s32 func_00244848(s32, s32);                        /* extern */
extern M2C_UNK D_002E6550;

s32 func_001AB6C0(void *arg0) {
    s32 temp_v0;

    temp_v0 = FUN_0018bc90(arg0 + 0xFD5C, func_00244848(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4)), 0x10, 0);
    if (temp_v0 != 0) {
        M2C_FIELD(arg0, s32 *, 0xC) = 2;
        func_001ACC38(&D_002E6550, 3);
    } else {
        M2C_FIELD(arg0, s32 *, 0xC) = 3;
    }
    return temp_v0;
}
