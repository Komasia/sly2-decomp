#include "m2c_prelude.h"
M2C_UNK SetDirty__4CSndUiUi(void *, M2C_UNK, M2C_UNK);    /* extern */

// name: SafeHouse port (CSnd::SetPan)
void SetPan__4CSndi(void *arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_hi;

    temp_hi = arg1 % 360;
    temp_a1 = (temp_hi > -1) ? temp_hi : (temp_hi + 0x168);
    if (temp_a1 != M2C_FIELD(arg0, s32 *, 0x14)) {
        M2C_FIELD(arg0, s32 *, 0x14) = temp_a1;
        SetDirty__4CSndUiUi(arg0, 0x20, 0x20);
    }
}
