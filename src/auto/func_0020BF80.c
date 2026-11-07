#include "m2c_prelude.h"
M2C_UNK func_0020C058(void *);                      /* extern */
M2C_UNK SetK2State__FP6K2PLAYi(void *, M2C_UNK);             /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

// name: SafeHouse port (StartK2)
void StartK2__FP5KIND2P3ALOiP6K2PLAY(void *arg0, s32 arg1, s32 arg2, void *arg3) {
    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
        memset(arg3, 0, 0x70);
        memset(arg3, 0, 0x70);
        func_0020C058(arg3);
        M2C_FIELD(arg3, void **, 0x30) = arg0;
        M2C_FIELD(arg3, s32 *, 0x34) = arg1;
        M2C_FIELD(arg3, s32 *, 0x3C) = arg2;
        SetK2State__FP6K2PLAYi(arg3, 0);
    }
}
