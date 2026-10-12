#include "m2c_prelude.h"
void SetAsegaSpeed__FP5ASEGAf(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x44) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x40) = (f32) (fparg0 * M2C_FIELD(arg0, f32 *, 0x48) * M2C_FIELD(arg0, f32 *, 0x4C));
}
