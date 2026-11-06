#include "m2c_prelude.h"
M2C_UNK func_00232250(s32);                         /* extern */

// name: SafeHouse port (SetSoundPlaybackMode)
void SetSoundPlaybackMode__FP8SOUNDMGRi(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x104) != arg1) {
        M2C_FIELD(arg0, s32 *, 0x104) = arg1;
        func_00232250(arg1);
    }
}
