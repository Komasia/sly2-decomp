#include "m2c_prelude.h"
s32 SemaCreate__Fii(M2C_UNK, M2C_UNK);              /* extern */

void InitCritSect__FP8CRITSECT(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = -1;
    M2C_FIELD(arg0, s32 *, 8) = SemaCreate__Fii(1, 1);
}
