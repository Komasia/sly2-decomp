#include "m2c_prelude.h"
// name: SafeHouse port (JOBPROX::Exit)
void Exit__7JOBPROX(s32 arg0) {
    SetProxState__7JOBPROXi(arg0, -1);
    Exit__5AIJOB(arg0);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x25);
}
