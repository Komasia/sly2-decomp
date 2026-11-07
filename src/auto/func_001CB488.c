#include "m2c_prelude.h"
void *IrowOfObject__FP2SWi();                              /* extern */

// name: SafeHouse port (LockProxyRowOf)
void LockProxyRowOf__Fv(void) {
    void *temp_v0;

    temp_v0 = IrowOfObject__FP2SWi();
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 8) = 1;
    }
}
