#include "m2c_prelude.h"
M2C_UNK ResetHackSoBase__FP2LO();                            /* extern */
M2C_UNK SetEnemyState__FP2LOi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (ResetEnemy)
void ResetEnemy__FP2LO(s32 arg0) {
    ResetHackSoBase__FP2LO();
    SetEnemyState__FP2LOi(arg0, 0);
}
