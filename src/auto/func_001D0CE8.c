#include "m2c_prelude.h"
/*
Decompilation failure in function func_001CE6D0:

Found jr instruction at chunk.s line 21, but the corresponding jump table is not provided.

Please include it in the input .s file(s), or in an additional file.

*/

s32 func_001D0CE8(s32 arg0, s32 arg1) {
    void *temp_v0;

    func_001CE9B8();
    temp_v0 = M2C_FIELD(arg1, void **, 8);
    M2C_FIELD(arg0, s32 *, 0xF4) = (s32) M2C_FIELD(temp_v0, s32 *, 0xC);
    return (s32) temp_v0;
}
