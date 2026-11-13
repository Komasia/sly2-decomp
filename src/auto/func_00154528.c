#include "m2c_prelude.h"
void DetachCopySw__4DMASPiPP2QWT2i(M2C_UNK *arg0, s32 arg1, u32 *arg2, s32 *arg3); /* static */
void Flush__4DMAS(s32, s32 *);                     /* static */

s32 func_00154528(s32 arg0, s32 arg1) {
    if (func_0020FA10(arg0, arg1) == 0) {
        return 0;
    }
    return func_00132EA0(M2C_FIELD(arg1, s32 *, 4)) == 0x31;
}
