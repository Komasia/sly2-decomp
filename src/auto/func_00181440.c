#include "m2c_prelude.h"
M2C_UNK PostLoadHackSoBase__FP2LO();                            /* extern */
M2C_UNK BindHackSegs__FP2LOP6HACKSOPv(s32, M2C_UNK, s32);           /* extern */

// name: SafeHouse port (PostLoadDock)
void PostLoadDock__FP2LO(s32 arg0) {
    PostLoadHackSoBase__FP2LO();
    BindHackSegs__FP2LOP6HACKSOPv(arg0, 3, arg0 + 0x1D0);
}
