#include "m2c_prelude.h"
M2C_UNK SignalSema(s32);                            /* extern */
M2C_UNK WaitSema(s32);                              /* extern */
extern s32 D_002DD314;
extern s32 D_003D3A40;
extern s32 D_003D3A44;

void func_001C9098(void) {
    SignalSema(D_003D3A40);
    WaitSema(D_003D3A44);
    D_002DD314 = 0;
}
