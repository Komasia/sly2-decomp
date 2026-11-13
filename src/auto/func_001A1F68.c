#include "m2c_prelude.h"
void func_001A1F68(s32 arg0, s32 arg1) {
    if (*M2C_FIELD(arg0, s32 **, 0x10) > 0) {
        SetDamageState__FP5ACTORi(arg0, 0);
        return;
    }
    SetDamageState__FP5ACTORi(arg0, 8);
}
