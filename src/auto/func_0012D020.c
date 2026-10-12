#include "m2c_prelude.h"
s32 func_0012D058();                                /* extern */
M2C_UNK func_00230100(s32, s32, void *);            /* extern */

void func_0012D020(void *arg0) {
    if (func_0012D058() != 0) {
        func_00230100(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), arg0);
    }
}
