#include "m2c_prelude.h"
M2C_UNK func_001A53A0(void *);                      /* extern */
M2C_UNK func_001A53E0();                            /* extern */

void func_001A5B80(void *arg0, s32 arg1, s32 arg2) {
    if (M2C_FIELD(arg0, void **, 0x10) != NULL) {
        if ((arg1 == arg0) && (arg2 == 0)) {
            func_001A53E0();
        }
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x14);
        return;
    }
    if (arg2 != 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = 0;
        func_001A53A0(arg0);
    }
}
