#include "m2c_prelude.h"
s32 func_001C4840(M2C_UNK *);                       /* extern */
M2C_UNK SetGadgetMenu__FPvi(s32, M2C_UNK);                /* extern */
extern s32 D_002DD5BC;
extern s32 D_002E1E40;
extern s32 D_002F7900;
extern M2C_UNK g_sw;

// name: SafeHouse port (OpenGadgetMenu)
void OpenGadgetMenu__FP2SW(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001C4840(&g_sw);
    if (temp_v0 != 0) {
        if (temp_v0 == D_002E1E40) {
            SetGadgetMenu__FPvi(arg0, 0);
            return;
        }
        if (temp_v0 == D_002DD5BC) {
            SetGadgetMenu__FPvi(arg0, 1);
            return;
        }
        if (temp_v0 == D_002F7900) {
            SetGadgetMenu__FPvi(arg0, 2);
        }
    }
}
