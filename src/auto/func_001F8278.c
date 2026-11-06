#include "m2c_prelude.h"
s32 __builtin_new(M2C_UNK);                         /* extern */
s32 func_001F8240();                                /* extern */
M2C_UNK func_0020A5F8(s32, s32);                    /* extern */

// name: SafeHouse port (PtargetrecOf)
void PtargetrecOf__FP2LO(s32 arg0) {
    if (func_001F8240() == 0) {
        func_0020A5F8(__builtin_new(0xAC), arg0);
    }
}
