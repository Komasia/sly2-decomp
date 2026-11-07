#include "m2c_prelude.h"
s32 PloFindSwNearest__FP2LO3OIDii(M2C_UNK *, M2C_UNK, s32, M2C_UNK); /* extern */
extern M2C_UNK g_sw;

void func_001DA770(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x24) = PloFindSwNearest__FP2LO3OIDii(&g_sw, 5, M2C_FIELD(arg0, s32 *, 0x20), 0);
}
