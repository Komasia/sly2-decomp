#include "m2c_prelude.h"
// name: SafeHouse port (JOBWAIT::Exit)
void Exit__7JOBWAIT(s32 arg0) {
    SetWaitState__7JOBWAITi(arg0, -1);
    Exit__5AIJOB(arg0);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x1E);
}
