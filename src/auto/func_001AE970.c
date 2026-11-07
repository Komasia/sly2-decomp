#include "m2c_prelude.h"
M2C_UNK SetMenuState__FP4MENUi(void *, M2C_UNK);             /* extern */
M2C_UNK CloseMenu__Fii();                            /* extern */

void func_001AE970(void *arg0) {
    CloseMenu__Fii();
    SetMenuState__FP4MENUi(arg0, 0);
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
}
