#include "m2c_prelude.h"
M2C_UNK SetAbilityCarried__FP7BENTLEYP7ABILITYP2LO(void *, void *, void *);      /* extern */
M2C_UNK func_001CB4B8(s32, void *);                 /* extern */
s32 func_00224610(void *);                          /* extern */

// name: SafeHouse port (ReleaseBentleyCarried)
void ReleaseBentleyCarried__FP7BENTLEY(void *arg0) {
    if (func_00224610(M2C_FIELD(arg0, void **, 0x186C)) != 0) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x186C), void **, 0x16C) = arg0;
        SetAbilityCarried__FP7BENTLEYP7ABILITYP2LO(arg0, M2C_FIELD(arg0, void **, 0x16B4), M2C_FIELD(arg0, void **, 0x186C));
    }
    func_001CB4B8(M2C_FIELD(M2C_FIELD(arg0, void **, 0x16B4), s32 *, 4), M2C_FIELD(arg0, void **, 0x186C));
    M2C_FIELD(arg0, void **, 0x186C) = NULL;
    M2C_FIELD(arg0, void **, 0x16B4) = NULL;
}
