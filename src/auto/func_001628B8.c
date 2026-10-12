#include "m2c_prelude.h"
M2C_UNK func_00162908(s32);                         /* extern */
M2C_UNK func_001629A0(s32);                         /* extern */
s32 func_001633E8();                                /* extern */
extern s32 D_003E0F9C;

void func_001628B8(s32 arg0) {
    if (func_001633E8() == 0) {
        if (D_003E0F9C != 0) {
            func_00162908(D_003E0F9C);
        }
        func_001629A0(arg0);
    }
}
