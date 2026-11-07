#include "m2c_prelude.h"
M2C_UNK SetActState__6JOBACTi(s32, M2C_UNK);                /* extern */
M2C_UNK Enter__5AIJOB();                            /* extern */
M2C_UNK LockJob__FP5AIJOB(s32);                         /* extern */

// name: SafeHouse port (JOBACT::Enter)
void Enter__6JOBACT(s32 arg0) {
    Enter__5AIJOB();
    SetActState__6JOBACTi(arg0, 0);
    LockJob__FP5AIJOB(arg0);
}
