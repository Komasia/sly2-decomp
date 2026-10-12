#include "m2c_prelude.h"
f32 UBias__Fff(f32 fparg0, f32 fparg1) {
    return fparg0 / ((((1.0f / fparg1) - 2.0f) * (1.0f - fparg0)) + 1.0f);
}
