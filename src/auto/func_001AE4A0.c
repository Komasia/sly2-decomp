#include "m2c_prelude.h"
M2C_UNK FreeStackImpl__Fv();                        /* extern */
M2C_UNK __builtin_delete(s32);                      /* extern */

void func_001AE4A0(s32 arg0, s32 arg1) {
    FreeStackImpl__Fv();
    if (arg1 & 1) {
        __builtin_delete(arg0);
    }
}
