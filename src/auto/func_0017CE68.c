#include "m2c_prelude.h"
M2C_UNK func_001EEF68();                            /* extern */
M2C_UNK AddGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBLADDER::Init)
void Init__9JOBLADDER(void *arg0) {
    func_001EEF68();
    M2C_FIELD(arg0, s32 *, 0x30) = -1;
    AddGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x27);
}
