#include "m2c_prelude.h"
M2C_UNK DeleteCtrl__FPP4CTRL(void *);                      /* extern */

void func_001CD2C0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xA0) != 0) {
        DeleteCtrl__FPP4CTRL(arg0 + 0x94);
        DeleteCtrl__FPP4CTRL(arg0 + 0x98);
        DeleteCtrl__FPP4CTRL(arg0 + 0x9C);
        M2C_FIELD(arg0, s32 *, 0xA0) = 0;
    }
}
