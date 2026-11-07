#include "m2c_prelude.h"
M2C_UNK SetTarget__9JOBSCRIPTP7CMDLISTiP11SAVEDSCRIPT(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK Exit__5AIJOB();                            /* extern */
M2C_UNK UnlockJob__FP5AIJOB(void *);                      /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBSCRIPT::Exit)
void Exit__9JOBSCRIPT(void *arg0) {
    Exit__5AIJOB();
    UnlockJob__FP5AIJOB(arg0);
    SetTarget__9JOBSCRIPTP7CMDLISTiP11SAVEDSCRIPT(arg0, 0, 0, 0);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x21);
}
