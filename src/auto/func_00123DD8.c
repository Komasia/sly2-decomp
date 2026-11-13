#include "m2c_prelude.h"
void InitTag(M2C_UNK *, M2C_UNK) asm("InitTag__4CRef");          /* extern */
extern M2C_UNK g_sw;

s32 func_00123DD8(s32 arg0, s32 arg1, s32 arg2) {
    func_00133130((s32) &g_sw, M2C_FIELD(arg2, s32 *, 4));
    InitTag((M2C_UNK *) arg0, 0x24);
    return arg0;
}
