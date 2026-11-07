#include "m2c_prelude.h"
f32 *PeventLaunch__FP5KINDEi();                               /* extern */

// name: SafeHouse port (GEventAseg11)
f32 GEventAseg11__Fv(void) {
    f32 *temp_v0;
    f32 var_f0;

    temp_v0 = PeventLaunch__FP5KINDEi();
    var_f0 = 0.0f;
    if (temp_v0 != NULL) {
        var_f0 = *temp_v0;
    }
    return var_f0;
}
