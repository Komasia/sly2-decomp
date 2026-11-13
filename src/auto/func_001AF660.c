#include "m2c_prelude.h"
// name: SafeHouse port (CloseMenu)
void CloseMenu__Fii(s32 arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x1E8) == 7) {
        if (M2C_FIELD(arg0, s32 *, 0x24) >= 2) {
            M2C_FIELD(arg0, s32 *, 0x24) = 1;
        }
        SetMenuState__FP4MENUi(arg0, 8);
    }
}
