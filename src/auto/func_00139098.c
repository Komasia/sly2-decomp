#include "m2c_prelude.h"
M2C_UNK func_0011A220(M2C_UNK *, void *);           /* extern */
M2C_UNK func_0011A2E8(s32, void *);                 /* extern */
extern M2C_UNK D_002DEB00;

void func_00139098(void *arg0) {
    func_0011A2E8(M2C_FIELD(arg0, s32 *, 0x108C) + 0x448, arg0);
    func_0011A220(&D_002DEB00, arg0);
}
