#include "m2c_prelude.h"
M2C_UNK SetStepPhysHeading__FP3ALOf(s32);                         /* extern */

// name: SafeHouse port (SetMoveHeading)
void SetMoveHeading__FP7MOVEREF(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 4) == 0) {
        SetStepPhysHeading__FP3ALOf(M2C_FIELD(arg0, s32 *, 0xC));
    }
}
