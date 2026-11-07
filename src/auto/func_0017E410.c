#include "m2c_prelude.h"
M2C_UNK SetState__7JOBLINKi(void *, M2C_UNK);             /* extern */
M2C_UNK Exit__5AIJOB();                            /* extern */
M2C_UNK UnlockJob__FP5AIJOB(void *);                      /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBLINK::Exit)
void Exit__7JOBLINK(void *arg0) {
    Exit__5AIJOB();
    SetState__7JOBLINKi(arg0, -1);
    UnlockJob__FP5AIJOB(arg0);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x2C);
}
