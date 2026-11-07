#include "m2c_prelude.h"
M2C_UNK EnablePo__FP2POi();                            /* extern */
M2C_UNK SetSafeHouseState__FP2SWi(s32, M2C_UNK);                /* extern */

void func_001D7418(s32 arg0, s32 arg1) {
    EnablePo__FP2POi();
    switch (arg1) {                                 /* irregular */
    case 0:
        SetSafeHouseState__FP2SWi(arg0, 0);
        return;
    case 1:
        SetSafeHouseState__FP2SWi(arg0, 1);
        break;
    }
}
