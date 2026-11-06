#include "m2c_prelude.h"
M2C_UNK Init__7JOBMOVE();                            /* extern */

// name: SafeHouse port (JOBSLEEP::Init)
void Init__8JOBSLEEP(void *arg0) {
    Init__7JOBMOVE();
    M2C_FIELD(arg0, s32 *, 0x3C) = 0x10;
    M2C_FIELD(arg0, s32 *, 0x50) = -1;
}
