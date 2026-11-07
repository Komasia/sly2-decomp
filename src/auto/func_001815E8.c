#include "m2c_prelude.h"
M2C_UNK BroadcastTaskEvent__FP2SWiP2LO(M2C_UNK *, M2C_UNK, void *);  /* extern */
M2C_UNK PlayHackSeg__FP2LOP6HACKSO(void *, void *);              /* extern */
M2C_UNK SetShipState__FP2LOi(void *, M2C_UNK);             /* extern */
M2C_UNK func_00181728();                            /* extern */
extern f32 g_clock;
extern M2C_UNK g_game;

// name: SafeHouse port (SetDockState)
void SetDockState__FP2LOi(void *arg0, s32 arg1) {
    s32 temp_v1;
    void *var_a1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x1C0);
    if (temp_v1 != arg1) {
        if ((temp_v1 == 1) && (M2C_FIELD(arg0, void **, 0x1C8) != NULL)) {
            func_00181728();
        }
        M2C_FIELD(arg0, s32 *, 0x1C0) = arg1;
        M2C_FIELD(arg0, f32 *, 0x1C4) = (f32) g_clock;
        switch (arg1) {                             /* irregular */
        case 1:
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C8), s32 *, 0x294) = (s32) M2C_FIELD(arg0, s32 *, 0x1CC);
            SetShipState__FP2LOi(M2C_FIELD(arg0, void **, 0x1C8), 3);
            break;
        case 2:
            BroadcastTaskEvent__FP2SWiP2LO(&g_game, 0x39, arg0);
            break;
        }
        if (arg1 != -1) {
            var_a1 = arg0 + ((arg1 * 0x10) + 0x1D0);
        } else {
            var_a1 = NULL;
        }
        PlayHackSeg__FP2LOP6HACKSO(arg0, var_a1);
    }
}
