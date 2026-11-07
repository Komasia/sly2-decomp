#include "m2c_prelude.h"
s32 func_0015E938(M2C_UNK *, M2C_UNK, s32, M2C_UNK); /* extern */
M2C_UNK SetWipeState__FPv5WIPES(void *, M2C_UNK);             /* extern */
extern M2C_UNK g_sw;

void func_0022B420(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_0015E938(&g_sw, 0x405, M2C_FIELD(arg0, s32 *, 0x58), 0);
    M2C_FIELD(arg0, s32 *, 0x54) = temp_v0;
    if ((temp_v0 == 0) || (M2C_FIELD(arg0, s32 *, 0) != 3)) {
        SetWipeState__FPv5WIPES(arg0, 0);
        return;
    }
    SetWipeState__FPv5WIPES(arg0, 2);
}
