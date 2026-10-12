#include "m2c_prelude.h"
M2C_UNK __4CRef(void *);                            /* extern */
extern M2C_UNK D_002D2E98;
extern M2C_UNK D_002D9978;

void *func_002563E8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &D_002D9978;
    __4CRef(arg0 + 0x80);
    M2C_FIELD(arg0, s32 *, 0x174) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &D_002D2E98;
    M2C_FIELD(arg0, s32 *, 0x2044) = 0;
    M2C_FIELD(arg0, s32 *, 0x2048) = 0;
    return arg0;
}
