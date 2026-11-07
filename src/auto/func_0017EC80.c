#include "m2c_prelude.h"
M2C_UNK func_001EEF78();                            /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBPATHSTEP::Exit)
void Exit__11JOBPATHSTEP(void *arg0) {
    func_001EEF78();
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x2E);
}
