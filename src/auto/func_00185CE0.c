#include "m2c_prelude.h"
M2C_UNK PostLoLoad__FP2LO();                            /* extern */
M2C_UNK UpdateZoneCamera__FP2LOi(s32, M2C_UNK);                /* extern */

void func_00185CE0(void *arg0) {
    s32 temp_a0;

    PostLoLoad__FP2LO();
    temp_a0 = M2C_FIELD(arg0, s32 *, 0x110);
    if (temp_a0 != 0) {
        UpdateZoneCamera__FP2LOi(temp_a0, 0);
    }
}
