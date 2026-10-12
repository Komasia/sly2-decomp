#include "m2c_prelude.h"
extern M2C_UNK D_002BE870;

void func_001813C0(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x378) = (f32) (M2C_FIELD(&D_002BE870, f32 *, 0) * fparg0);
    M2C_FIELD(arg0, f32 *, 0x37C) = (f32) (M2C_FIELD(&D_002BE870, f32 *, 4) * fparg0);
    M2C_FIELD(arg0, f32 *, 0x380) = (f32) M2C_FIELD(&D_002BE870, f32 *, 8);
}
