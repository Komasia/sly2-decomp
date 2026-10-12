#include "m2c_prelude.h"
void *func_001FCFA0();                              /* extern */

f32 func_001FCFD0(void) {
    f32 var_f0;
    void *temp_v0;

    temp_v0 = func_001FCFA0();
    var_f0 = 0.0f;
    if (temp_v0 != NULL) {
        var_f0 = M2C_FIELD(temp_v0, f32 *, 0x50);
    }
    return var_f0;
}
