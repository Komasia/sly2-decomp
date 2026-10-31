#include "m2c_prelude.h"
s32 func_00242AB8();                                /* extern */
extern s32 g_scecd;

s32 func_0014B9C0(void) {
    s32 temp_v0;

    temp_v0 = func_00242AB8();
    if (g_scecd != temp_v0) {
        g_scecd = temp_v0;
    }
    return g_scecd == 0x14;
}
