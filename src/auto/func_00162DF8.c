#include "m2c_prelude.h"
M2C_UNK RestartTask__FP4TASK(s32);                         /* extern */
extern s32 D_003E0FA4;

// name: SafeHouse port (RestartJobAtCheckpoint)
void RestartJobAtCheckpoint__FP2SW(void *arg0) {
    if (D_003E0FA4 != 0) {
        RestartTask__FP4TASK(D_003E0FA4);
        return;
    }
    RestartTask__FP4TASK(M2C_FIELD(arg0, s32 *, 0x64));
}
