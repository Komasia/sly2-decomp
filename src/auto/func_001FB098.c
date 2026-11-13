#include "m2c_prelude.h"
// name: SafeHouse port (CSnd::Stop)
void Stop__4CSndf(s32 arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x48) = fparg0;
    SetDirty__4CSndUiUi(arg0, 0x1FFF, 8);
}
