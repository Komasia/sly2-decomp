#include "m2c_prelude.h"
M2C_UNK func_001425B0(void *);                      /* extern */
M2C_UNK func_00190D10();                            /* extern */

void func_0018A238(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x18C8) == 3) {
        func_00190D10();
    }
    func_001425B0(arg0);
}
