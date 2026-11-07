#include "m2c_prelude.h"
M2C_UNK func_0022C840(s32, s32);                    /* extern */
M2C_UNK SetXfMode__FP3ALOP2XFi(s32, s32, s32);               /* extern */

// name: SafeHouse port (CTRL::Start)
void Start__4CTRL(void *arg0) {
    SetXfMode__FP3ALOP2XFi(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 0x14));
    func_0022C840(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
}
