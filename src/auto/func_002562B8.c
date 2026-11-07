#include "m2c_prelude.h"
M2C_UNK MarkAloDirty__FP3ALO(s32);                         /* extern */

void func_002562B8(void *arg0, f32 fparg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), f32 *, 8) = fparg0;
    MarkAloDirty__FP3ALO(M2C_FIELD(arg0, s32 *, 0x20));
}
