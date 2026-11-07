#include "m2c_prelude.h"
M2C_UNK func_001C1968(s32, void *);                 /* extern */

// name: SafeHouse port (RemovePolyFromRegion)
void RemovePolyFromRegion__FP7NAVPOLY(void *arg0) {
    s32 temp_a0;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x1DC);
    if (temp_a0 != 0) {
        func_001C1968(temp_a0, arg0);
        M2C_FIELD(arg0, s32 *, 0x1DC) = 0;
    }
}
