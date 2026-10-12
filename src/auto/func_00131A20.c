#include "m2c_prelude.h"
void func_00131A20(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x48) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x40) = (f32) (M2C_FIELD(arg0, f32 *, 0x44) * fparg0 * M2C_FIELD(arg0, f32 *, 0x4C));
}
