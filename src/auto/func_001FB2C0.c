#include "m2c_prelude.h"
// name: SafeHouse port (CSnd::SetPitch)
void SetPitch__4CSndiif(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    if (fparg0 != M2C_FIELD(arg0, f32 *, 0x18)) {
        M2C_FIELD(arg0, f32 *, 0x18) = fparg0;
        SetDirty__4CSndUiUi(arg0, 0x40, 0x40);
    }
}
