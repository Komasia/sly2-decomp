#include "m2c_prelude.h"
M2C_UNK Init__5AIJOB();                            /* extern */
M2C_UNK AddGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBPROX::Init)
void Init__7JOBPROX(void *arg0) {
    Init__5AIJOB();
    M2C_FIELD(arg0, s32 *, 0x30) = -1;
    AddGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x25);
}
