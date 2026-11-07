#include "m2c_prelude.h"
M2C_UNK SetBootyState__FP2LOi(void *, M2C_UNK);             /* extern */
s32 FAbsorbSoWkr__FP2SOP3WKR();                                /* extern */

// name: SafeHouse port (FAcceptBootyContact)
s32 FAcceptBootyContact__FP3ALO(void *arg0) {
    if ((FAbsorbSoWkr__FP2SOP3WKR() == 0) || (M2C_FIELD(arg0, s32 *, 0x184) != 5)) {
        return 0;
    }
    SetBootyState__FP2LOi(arg0, 0);
    return 1;
}
