#include "m2c_prelude.h"
M2C_UNK UpdateReach__FP5REACH(void *);                      /* extern */

// name: SafeHouse port (UpdateSlyReach)
void UpdateSlyReach__FP3SLY(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x18D8) == 0) {
        UpdateReach__FP5REACH(arg0 + 0x17D0);
    }
}
