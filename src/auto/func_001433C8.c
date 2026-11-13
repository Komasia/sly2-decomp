#include "m2c_prelude.h"
// name: SafeHouse port (ReturnActorBooty)
void ReturnActorBooty__FP5ACTORii(s32 arg0, s32 arg1, s32 arg2) {
    if (M2C_FIELD(arg0, s32 *, 0x11A8) != 0) {
        SaveBootyMove__FP5ACTORiP2LO(arg0, 1, 0);
        SetBootyState__FP2LOi(M2C_FIELD(arg0, s32 *, 0x11A8), 0);
    }
}
