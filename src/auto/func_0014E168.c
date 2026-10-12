#include "m2c_prelude.h"
M2C_UNK func_0014DC58(void *);                      /* extern */

void func_0014E168(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s128 *, 0x60) = (s128) M2C_FIELD(arg1, s128 *, 0);
    M2C_FIELD(arg0, s128 *, 0x70) = (s128) M2C_FIELD(arg1, s128 *, 0x10);
    M2C_FIELD(arg0, s128 *, 0x80) = (s128) M2C_FIELD(arg1, s128 *, 0x20);
    M2C_FIELD(arg0, s128 *, 0x90) = (s128) M2C_FIELD(arg1, s128 *, 0x30);
    func_0014DC58(arg0);
}
