#include "m2c_prelude.h"
// name: SafeHouse port (AddRefAsega)
void AddRefAsega__FP5ASEGA(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (M2C_FIELD(arg0, s32 *, 0x10) + 1);
}
