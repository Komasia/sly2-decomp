#include "m2c_prelude.h"
M2C_UNK func_00129DF8(void *);                      /* extern */
M2C_UNK func_00129EC8(void *);                      /* extern */

void *__as__4CRefRC4CRef(void *arg0, void *arg1) {
    func_00129DF8(arg1);
    func_00129EC8(arg0);
    M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
    return arg0;
}
