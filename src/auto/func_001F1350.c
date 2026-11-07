#include "m2c_prelude.h"
M2C_UNK FinishSmaTransition__FP3SMA();                            /* extern */
M2C_UNK ChooseSmaTransition__FP3SMAi(void *, M2C_UNK);             /* extern */

// name: SafeHouse port (SetSmaMask)
void SetSmaMask__FP3SMAUi(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
    if ((M2C_FIELD(arg0, s32 *, 0x30) != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0x10) & arg1)) {
        FinishSmaTransition__FP3SMA();
        ChooseSmaTransition__FP3SMAi(arg0, 0);
    }
}
