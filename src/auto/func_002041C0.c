#include "m2c_prelude.h"
s128 func_001A6F00(void *, M2C_UNK, s128);          /* extern */
M2C_UNK func_001F40A0();                            /* extern */

void func_002041C0(void *arg0) {
    func_001F40A0();
    M2C_FIELD(arg0, s128 *, 0x230) = func_001A6F00(arg0, 0, M2C_FIELD(arg0, s128 *, 0x240));
}
