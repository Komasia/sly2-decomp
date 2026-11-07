#include "m2c_prelude.h"
M2C_UNK Exit__7JOBMOVE();                            /* extern */
M2C_UNK UnlockJob__FP5AIJOB(s32);                         /* extern */

// name: SafeHouse port (JOBUSE::Exit)
void Exit__6JOBUSE(s32 arg0) {
    Exit__7JOBMOVE();
    UnlockJob__FP5AIJOB(arg0);
}
