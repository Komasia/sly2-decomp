#include "m2c_prelude.h"
M2C_UNK SetCmFocusObject__FP2LOi();                            /* extern */
M2C_UNK SetVehicleMode__FP7VEHICLEi(void *, M2C_UNK);             /* extern */

void func_001D1940(void *arg0, s32 arg1) {
    SetCmFocusObject__FP2LOi();
    if (arg1 != 0) {
        SetVehicleMode__FP7VEHICLEi(arg0, 2);
    } else if (M2C_FIELD(arg0, s32 *, 0x180) == 2) {
        SetVehicleMode__FP7VEHICLEi(arg0, 0);
    }
}
