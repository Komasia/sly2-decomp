#include "m2c_prelude.h"
M2C_UNK func_00165538(s32);                         /* extern */
extern s32 D_003E0FA4;

void func_00162DF8(void *arg0) {
    if (D_003E0FA4 != 0) {
        func_00165538(D_003E0FA4);
        return;
    }
    func_00165538(M2C_FIELD(arg0, s32 *, 0x64));
}
