#include "m2c_prelude.h"
M2C_UNK func_001B6078(void *, M2C_UNK);             /* extern */
M2C_UNK SetMurrayBerserk__FP6MURRAYi(void *, M2C_UNK);             /* extern */
M2C_UNK Enter__5AIJOB();                            /* extern */

// name: SafeHouse port (JOBMURRAYRAGE::Enter)
void Enter__13JOBMURRAYRAGE(void *arg0) {
    Enter__5AIJOB();
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x1AC0) = 1;
    func_001B6078(M2C_FIELD(arg0, void **, 0x10), 0xC);
    SetMurrayBerserk__FP6MURRAYi(M2C_FIELD(arg0, void **, 0x10), 0);
}
