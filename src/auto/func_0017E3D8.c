#include "m2c_prelude.h"
M2C_UNK NextRecord__7JOBLINK(s32);                         /* extern */
M2C_UNK Enter__5AIJOB();                            /* extern */
M2C_UNK LockJob__FP5AIJOB(s32);                         /* extern */

// name: SafeHouse port (JOBLINK::Enter)
void Enter__7JOBLINK(s32 arg0) {
    Enter__5AIJOB();
    LockJob__FP5AIJOB(arg0);
    NextRecord__7JOBLINK(arg0);
}
