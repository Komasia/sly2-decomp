#include "m2c_prelude.h"
s32 func_001BBE18();                                /* extern */

s32 func_001BBE68(void *arg0) {
    if (func_001BBE18() == 0) {
        return 0;
    }
    return M2C_FIELD(arg0, s32 *, 0x164) + (M2C_FIELD(arg0, s32 *, 0x15C) * 0x10);
}
