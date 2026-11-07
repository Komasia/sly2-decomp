#include "m2c_prelude.h"
M2C_UNK Exit__5AIJOB();                            /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBHOLD::Exit)
void Exit__7JOBHOLD(void *arg0) {
    Exit__5AIJOB();
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x28);
}
