#include "m2c_prelude.h"
M2C_UNK func_002046F0(void *, s32);                 /* extern */

// name: SafeHouse port (UpdateSlyDodgeInput)
void UpdateSlyDodgeInput__FP3SLY(void **arg0) {
    s32 temp_a1;
    void *temp_a0;

    temp_a0 = *arg0;
    temp_a1 = M2C_FIELD(temp_a0, s32 *, 0x10DC);
    if (temp_a1 != 0) {
        func_002046F0(temp_a0, temp_a1);
    }
}
