#include "m2c_prelude.h"
M2C_UNK func_001306A8(void *);                      /* extern */
s32 FAsegaRetracted(s32) asm("FAsegaRetracted__FP5ASEGA");                             /* extern */
M2C_UNK func_00147410(void *, M2C_UNK);             /* extern */
s32 FDialogPlaying__FP8SOUNDMGRi(M2C_UNK *, s32);                  /* extern */
extern M2C_UNK D_003DD040;

// name: SafeHouse port (UpdateOverlay)
void UpdateOverlay__FP2LO(void *arg0) {
    s32 temp_a0;
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x150);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_00147410(arg0, 1);
        return;
    case 3:
        if (FDialogPlaying__FP8SOUNDMGRi(&D_003DD040, M2C_FIELD(arg0, s32 *, 0x170)) == 0) {
            func_00147410(arg0, 2);
            return;
        }
        return;
    case 2:
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x160);
        if ((temp_a0 == 0) || (FAsegaRetracted(temp_a0) != 0)) {
            func_001306A8(arg0 + 0x160);
            func_00147410(arg0, -1);
        }
        break;
    }
}
