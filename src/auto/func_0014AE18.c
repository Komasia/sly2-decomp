#include "m2c_prelude.h"
// name: SafeHouse port (JOBCHASE::PloEntry)
s32 PloEntry__8JOBCHASE(void *arg0) {
    return M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x3C) * 0xC) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 *, 0x58)), s32 *, 8);
}
