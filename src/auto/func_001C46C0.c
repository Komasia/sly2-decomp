#include "m2c_prelude.h"
s32 GrfPadctlPressedWithin__FP6PADCTLUif();                                /* extern */
M2C_UNK ForgetPadctlPresses__FP6PADCTLUi(s32, s32);                    /* extern */

// name: SafeHouse port (GrfPadctlTakePressed)
s32 GrfPadctlTakePressed__FP6PADCTL(s32 arg0) {
    s32 temp_v0;

    temp_v0 = GrfPadctlPressedWithin__FP6PADCTLUif();
    ForgetPadctlPresses__FP6PADCTLUi(arg0, temp_v0);
    return temp_v0;
}
