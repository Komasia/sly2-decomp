#include "m2c_prelude.h"
extern s32 D_003DCFEC;

// name: SafeHouse port (PshdFromIndex)
s32 PshdFromIndex__Fi(s32 arg0) {
    return D_003DCFEC + (arg0 * 0x2C);
}
