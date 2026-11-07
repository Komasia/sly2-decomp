#include "m2c_prelude.h"
M2C_UNK SetActState__6JOBACTi(void *, M2C_UNK);             /* extern */
M2C_UNK func_001EEF78();                            /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBACT::Exit)
void Exit__6JOBACT(void *arg0) {
    func_001EEF78();
    SetActState__6JOBACTi(arg0, -1);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x18);
}
