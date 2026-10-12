#include "m2c_prelude.h"
M2C_UNK func_00199298(void *);                      /* extern */
M2C_UNK func_00204768();                            /* extern */

void func_00140D70(void *arg0) {
    func_00204768();
    if (M2C_FIELD(arg0, s32 *, 0x2DC) != -1) {
        func_00199298(arg0 + 0x2C0);
    }
}
