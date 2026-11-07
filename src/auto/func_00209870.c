#include "m2c_prelude.h"
M2C_UNK func_001F1900();                            /* extern */

// name: SafeHouse port (SetGuardStateMask)
void SetGuardStateMask__FP5GUARDUl(void *arg0, s64 arg1) {
    M2C_FIELD(arg0, s64 *, 0x2C0) = arg1;
    func_001F1900();
}
