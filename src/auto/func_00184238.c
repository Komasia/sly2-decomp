#include "m2c_prelude.h"
extern f32 D_002BF660;

void func_00184238(void *arg0, f32 *arg1) {
    *arg1 -= M2C_FIELD(arg0, f32 *, 0x110) - (D_002BF660 - 150.0f);
}
