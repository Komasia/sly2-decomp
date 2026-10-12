#include "m2c_prelude.h"
M2C_UNK SetRumbleRums__FP6RUMBLE4RUMS(void *, M2C_UNK); /* extern */
s32 func_001D55B8();                                /* extern */

void TriggerRumbleRumpat__FP6RUMBLEP6RUMPATf(void *arg0, void *arg1, f32 fparg0) {
    if ((M2C_FIELD(arg0, s32 *, 8) != 0) && (M2C_FIELD(arg1, s32 *, 0) > 0) && (func_001D55B8() != 0)) {
        M2C_FIELD(arg0, f32 *, 0x14) = fparg0;
        M2C_FIELD(arg0, void **, 0xC) = arg1;
        M2C_FIELD(arg0, s32 *, 0x10) = 0;
        M2C_FIELD(arg0, f32 *, 0x18) = (f32) M2C_FIELD(arg1, f32 *, 8);
        M2C_FIELD(arg0, s32 *, 8) = -1;
        SetRumbleRums__FP6RUMBLE4RUMS(arg0, 2);
    }
}
