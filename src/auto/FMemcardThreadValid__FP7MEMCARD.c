#include "m2c_prelude.h"
s32 FMemcardThreadValid__FP7MEMCARD(void *arg0) {
    return ~M2C_FIELD(arg0, s32 *, 4) != 0;
}
