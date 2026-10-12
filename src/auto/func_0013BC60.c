#include "m2c_prelude.h"
M2C_UNK func_00134320(M2C_UNK *, void *);           /* extern */
extern M2C_UNK D_003DD490;

void func_0013BC60(void *arg0, s32 arg1) {
    if (arg1 != M2C_FIELD(arg0, s32 *, 0x200)) {
        M2C_FIELD(arg0, s32 *, 0x200) = arg1;
        func_00134320(&D_003DD490, arg0);
    }
}
