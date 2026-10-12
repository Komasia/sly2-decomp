#include "m2c_prelude.h"
s32 sceCdSync(s32);                                 /* extern */

s32 FCdCompleted__Fi(s32 arg0) {
    return sceCdSync(arg0 == 0) == 0;
}
