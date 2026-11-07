#include "m2c_prelude.h"
void *PstreamFindDialog__FP8SOUNDMGRi();                              /* extern */

f32 func_001FCFD0(void) {
    f32 var_f0;
    void *temp_v0;

    temp_v0 = PstreamFindDialog__FP8SOUNDMGRi();
    var_f0 = 0.0f;
    if (temp_v0 != NULL) {
        var_f0 = M2C_FIELD(temp_v0, f32 *, 0x50);
    }
    return var_f0;
}
