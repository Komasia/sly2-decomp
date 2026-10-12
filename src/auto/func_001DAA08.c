#include "m2c_prelude.h"
M2C_UNK func_001DA728();                            /* extern */
M2C_UNK func_001DAA78(void *);                      /* extern */
extern M2C_UNK D_002D8568;

void *func_001DAA08(void *arg0) {
    func_001DA728();
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &D_002D8568;
    func_001DAA78(arg0);
    return arg0;
}
