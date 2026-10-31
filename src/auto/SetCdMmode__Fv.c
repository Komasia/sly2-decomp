#include "m2c_prelude.h"
M2C_UNK sceCdMmode(M2C_UNK);                        /* extern */
extern s32 g_scecd;

void SetCdMmode__Fv(void) {
    if (g_scecd == 0x14) {
        sceCdMmode(2);
    }
}
