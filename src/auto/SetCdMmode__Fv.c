#include "m2c_prelude.h"
M2C_UNK sceCdMmode(M2C_UNK);                        /* extern */
extern s32 D_002BD4C4;

void SetCdMmode__Fv(void) {
    if (D_002BD4C4 == 0x14) {
        sceCdMmode(2);
    }
}
