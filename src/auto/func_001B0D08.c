#include "m2c_prelude.h"
M2C_UNK PlaceBird__FP2LO(void *);                      /* extern */
M2C_UNK func_001B1A38(void *, s32, void *);         /* extern */
M2C_UNK func_001B1BF0(void *);                      /* extern */
M2C_UNK func_001F36A8();                            /* extern */

// name: SafeHouse port (StartBird)
void StartBird__FP2LO(void *arg0) {
    func_001F36A8();
    func_001B1BF0(arg0);
    func_001B1A38(arg0, M2C_FIELD(arg0, s32 *, 0x18C), arg0 + 0x1CC);
    func_001B1A38(arg0, M2C_FIELD(arg0, s32 *, 0x1B0), arg0 + 0x1D0);
    PlaceBird__FP2LO(arg0);
}
